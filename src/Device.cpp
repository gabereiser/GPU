#include "Device.h"

#include <new>

#include "Internal/Error.h"
#include "PhysicalDevice.h"
#include "Queue.h"

void gpuDeviceRetain(GPUDevice device) {
    if (device != nullptr) {
        ++device->refCount;
    }
}

void gpuDeviceDrop(GPUDevice device) {
    if (device == nullptr) {
        return;
    }

    if (device->refCount > 0) {
        --device->refCount;
    }

    if (device->refCount == 0) {
        if (device->handle != VK_NULL_HANDLE) {
            vkDestroyDevice(device->handle, device->allocator);
        }
        gpuPhysicalDeviceDrop(device->physicalDevice);
        delete device;
    }
}

extern "C" {

GPU_API VkResult GPU_CALL gpuDeviceCreate(
    GPUPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDevice* device) {
    gpu::internal::clearLastError();

    if (physicalDevice == nullptr || createInfo == nullptr || device == nullptr) {
        gpu::internal::setLastError("Physical device, create info, and device output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (physicalDevice->destroyRequested) {
        gpu::internal::setLastError("Physical device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *device = nullptr;

    VkDevice handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateDevice(physicalDevice->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create Vulkan device.");
        return result;
    }

    GPUDevice wrapper = new (std::nothrow) GPUDevice_T{physicalDevice, handle, allocator, 1, false};
    if (wrapper == nullptr) {
        vkDestroyDevice(handle, allocator);
        gpu::internal::setLastError("Failed to allocate Device.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuPhysicalDeviceRetain(physicalDevice);

    *device = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDeviceDestroy(GPUDevice device) {
    if (device == nullptr) {
        return;
    }

    if (device->destroyRequested) {
        return;
    }

    device->destroyRequested = true;
    gpuDeviceDrop(device);
}

GPU_API VkDevice GPU_CALL gpuDeviceGetVkHandle(GPUDevice device) {
    return device != nullptr && !device->destroyRequested ? device->handle : VK_NULL_HANDLE;
}

GPU_API GPUPhysicalDevice GPU_CALL gpuDeviceGetPhysicalDevice(GPUDevice device) {
    return device != nullptr && !device->destroyRequested ? device->physicalDevice : nullptr;
}

GPU_API VkResult GPU_CALL gpuDeviceGetQueue(
    GPUDevice device,
    uint32_t familyIndex,
    uint32_t queueIndex,
    GPUQueue* queue) {
    gpu::internal::clearLastError();

    if (device == nullptr || queue == nullptr) {
        gpu::internal::setLastError("Device and queue output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *queue = nullptr;

    VkQueue handle = VK_NULL_HANDLE;
    vkGetDeviceQueue(device->handle, familyIndex, queueIndex, &handle);
    if (handle == VK_NULL_HANDLE) {
        gpu::internal::setLastError("Failed to get Vulkan queue.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    GPUQueue wrapper = new (std::nothrow) GPUQueue_T{device, handle, familyIndex, queueIndex, 1, false};
    if (wrapper == nullptr) {
        gpu::internal::setLastError("Failed to allocate Queue.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);

    *queue = wrapper;
    return VK_SUCCESS;
}

}  // extern "C"

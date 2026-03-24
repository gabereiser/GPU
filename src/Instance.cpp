#include "Instance.h"

#include <new>
#include <vector>

#include "Internal/Error.h"
#include "PhysicalDevice.h"

void gpuInstanceRetain(GPUInstance instance) {
    if (instance != nullptr) {
        ++instance->refCount;
    }
}

void gpuInstanceDrop(GPUInstance instance) {
    if (instance == nullptr) {
        return;
    }

    if (instance->refCount > 0) {
        --instance->refCount;
    }

    if (instance->refCount == 0) {
        if (instance->handle != VK_NULL_HANDLE) {
            vkDestroyInstance(instance->handle, instance->allocator);
        }
        delete instance;
    }
}

extern "C" {

GPU_API VkResult GPU_CALL gpuInstanceCreate(
    const VkInstanceCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUInstance* instance) {
    gpu::internal::clearLastError();

    if (createInfo == nullptr || instance == nullptr) {
        gpu::internal::setLastError("Create info and instance output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *instance = nullptr;

    VkInstance handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateInstance(createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create Vulkan instance.");
        return result;
    }

    GPUInstance wrapper = new (std::nothrow) GPUInstance_T{handle, allocator, 1, false};
    if (wrapper == nullptr) {
        vkDestroyInstance(handle, allocator);
        gpu::internal::setLastError("Failed to allocate Instance.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *instance = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuInstanceDestroy(GPUInstance instance) {
    if (instance == nullptr) {
        return;
    }

    if (instance->destroyRequested) {
        return;
    }

    instance->destroyRequested = true;
    gpuInstanceDrop(instance);
}

GPU_API VkInstance GPU_CALL gpuInstanceGetVkHandle(GPUInstance instance) {
    return instance != nullptr && !instance->destroyRequested ? instance->handle : VK_NULL_HANDLE;
}

GPU_API uint32_t GPU_CALL gpuInstanceGetPhysicalDeviceCount(GPUInstance instance) {
    gpu::internal::clearLastError();

    if (instance == nullptr) {
        gpu::internal::setLastError("Instance must not be null.");
        return 0;
    }

    if (instance->destroyRequested) {
        gpu::internal::setLastError("Instance is being destroyed.");
        return 0;
    }

    uint32_t count = 0;
    const VkResult result = vkEnumeratePhysicalDevices(instance->handle, &count, nullptr);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to enumerate physical devices.");
        return 0;
    }

    return count;
}

GPU_API VkResult GPU_CALL gpuInstanceGetPhysicalDevice(
    GPUInstance instance,
    uint32_t index,
    GPUPhysicalDevice* physicalDevice) {
    gpu::internal::clearLastError();

    if (instance == nullptr || physicalDevice == nullptr) {
        gpu::internal::setLastError("Instance and physical device output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (instance->destroyRequested) {
        gpu::internal::setLastError("Instance is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *physicalDevice = nullptr;

    uint32_t count = 0;
    VkResult result = vkEnumeratePhysicalDevices(instance->handle, &count, nullptr);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to enumerate physical devices.");
        return result;
    }

    if (index >= count) {
        gpu::internal::setLastError("Physical device index is out of range.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    std::vector<VkPhysicalDevice> devices(count);
    result = vkEnumeratePhysicalDevices(instance->handle, &count, devices.data());
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to fetch physical devices.");
        return result;
    }

    GPUPhysicalDevice wrapper = new (std::nothrow) GPUPhysicalDevice_T{instance, devices[index], 1, false};
    if (wrapper == nullptr) {
        gpu::internal::setLastError("Failed to allocate PhysicalDevice.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuInstanceRetain(instance);

    *physicalDevice = wrapper;
    return VK_SUCCESS;
}

}  // extern "C"

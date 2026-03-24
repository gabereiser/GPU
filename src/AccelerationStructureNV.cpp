#include "AccelerationStructureNV.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuAccelerationStructureNVCreate(
    GPUDevice device,
    const VkAccelerationStructureCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUAccelerationStructureNV* accelerationStructure) {
    gpu::internal::clearLastError();
    if (device == nullptr || createInfo == nullptr || accelerationStructure == nullptr) {
        gpu::internal::setLastError("Device, create info, and acceleration structure output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    *accelerationStructure = nullptr;
    VkAccelerationStructureNV handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateAccelerationStructureNV(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create acceleration structure NV.");
        return result;
    }
    GPUAccelerationStructureNV wrapper = new (std::nothrow) GPUAccelerationStructureNV_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyAccelerationStructureNV(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate AccelerationStructureNV.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    gpuDeviceRetain(device);
    *accelerationStructure = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuAccelerationStructureNVDestroy(GPUAccelerationStructureNV accelerationStructure) {
    if (accelerationStructure == nullptr || accelerationStructure->destroyRequested) {
        return;
    }
    accelerationStructure->destroyRequested = true;
    vkDestroyAccelerationStructureNV(accelerationStructure->device->handle, accelerationStructure->handle, accelerationStructure->allocator);
    gpuDeviceDrop(accelerationStructure->device);
    delete accelerationStructure;
}

GPU_API VkAccelerationStructureNV GPU_CALL gpuAccelerationStructureNVGetVkHandle(GPUAccelerationStructureNV accelerationStructure) {
    return accelerationStructure != nullptr && !accelerationStructure->destroyRequested ? accelerationStructure->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuAccelerationStructureNVGetDevice(GPUAccelerationStructureNV accelerationStructure) {
    return accelerationStructure != nullptr && !accelerationStructure->destroyRequested ? accelerationStructure->device : nullptr;
}

}  // extern "C"

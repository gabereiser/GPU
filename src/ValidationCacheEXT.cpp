#include "ValidationCacheEXT.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuValidationCacheEXTCreate(
    GPUDevice device,
    const VkValidationCacheCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUValidationCacheEXT* validationCache) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || validationCache == nullptr) {
        gpu::internal::setLastError("Device, create info, and validation cache output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *validationCache = nullptr;

    VkValidationCacheEXT handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateValidationCacheEXT(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create validation cache.");
        return result;
    }

    GPUValidationCacheEXT wrapper =
        new (std::nothrow) GPUValidationCacheEXT_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        gpuDestroyValidationCacheEXT(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate ValidationCacheEXT.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *validationCache = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuValidationCacheEXTDestroy(GPUValidationCacheEXT validationCache) {
    if (validationCache == nullptr || validationCache->destroyRequested) {
        return;
    }

    validationCache->destroyRequested = true;
    gpuDestroyValidationCacheEXT(validationCache->device->handle, validationCache->handle, validationCache->allocator);
    gpuDeviceDrop(validationCache->device);
    delete validationCache;
}

GPU_API VkValidationCacheEXT GPU_CALL gpuValidationCacheEXTGetVkHandle(GPUValidationCacheEXT validationCache) {
    return validationCache != nullptr && !validationCache->destroyRequested ? validationCache->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuValidationCacheEXTGetDevice(GPUValidationCacheEXT validationCache) {
    return validationCache != nullptr && !validationCache->destroyRequested ? validationCache->device : nullptr;
}

}  // extern "C"

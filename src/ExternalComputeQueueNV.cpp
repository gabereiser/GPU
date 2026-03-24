#include "ExternalComputeQueueNV.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuExternalComputeQueueNVCreate(
    GPUDevice device,
    const VkExternalComputeQueueCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUExternalComputeQueueNV* externalQueue) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || externalQueue == nullptr) {
        gpu::internal::setLastError("Device, create info, and external compute queue output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *externalQueue = nullptr;

    VkExternalComputeQueueNV handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateExternalComputeQueueNV(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create external compute queue NV.");
        return result;
    }

    GPUExternalComputeQueueNV wrapper =
        new (std::nothrow) GPUExternalComputeQueueNV_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyExternalComputeQueueNV(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate ExternalComputeQueueNV.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *externalQueue = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuExternalComputeQueueNVDestroy(GPUExternalComputeQueueNV externalQueue) {
    if (externalQueue == nullptr || externalQueue->destroyRequested) {
        return;
    }

    externalQueue->destroyRequested = true;
    vkDestroyExternalComputeQueueNV(externalQueue->device->handle, externalQueue->handle, externalQueue->allocator);
    gpuDeviceDrop(externalQueue->device);
    delete externalQueue;
}

GPU_API VkExternalComputeQueueNV GPU_CALL gpuExternalComputeQueueNVGetVkHandle(GPUExternalComputeQueueNV externalQueue) {
    return externalQueue != nullptr && !externalQueue->destroyRequested ? externalQueue->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuExternalComputeQueueNVGetDevice(GPUExternalComputeQueueNV externalQueue) {
    return externalQueue != nullptr && !externalQueue->destroyRequested ? externalQueue->device : nullptr;
}

}  // extern "C"

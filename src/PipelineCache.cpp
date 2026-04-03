#include "PipelineCache.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuPipelineCacheCreate(
    GPUDevice device,
    const VkPipelineCacheCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipelineCache* pipelineCache) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || pipelineCache == nullptr) {
        gpu::internal::setLastError("Device, create info, and pipeline cache output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *pipelineCache = nullptr;

    VkPipelineCache handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreatePipelineCache(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create pipeline cache.");
        return result;
    }

    GPUPipelineCache wrapper = new (std::nothrow) GPUPipelineCache_T{device, handle, allocator};
    if (wrapper == nullptr) {
        gpuDestroyPipelineCache(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate PipelineCache.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *pipelineCache = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuPipelineCacheDestroy(GPUPipelineCache pipelineCache) {
    if (pipelineCache == nullptr) {
        return;
    }

    gpuDestroyPipelineCache(pipelineCache->device->handle, pipelineCache->handle, pipelineCache->allocator);
    delete pipelineCache;
}

GPU_API VkPipelineCache GPU_CALL gpuPipelineCacheGetVkHandle(GPUPipelineCache pipelineCache) {
    return pipelineCache != nullptr ? pipelineCache->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuPipelineCacheGetDevice(GPUPipelineCache pipelineCache) {
    return pipelineCache != nullptr ? pipelineCache->device : nullptr;
}

}  // extern "C"

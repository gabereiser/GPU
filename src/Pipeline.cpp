#include "Pipeline.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"
#include "PipelineCache.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuPipelineCreateGraphics(
    GPUDevice device,
    GPUPipelineCache pipelineCache,
    const VkGraphicsPipelineCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipeline* pipeline) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || pipeline == nullptr) {
        gpu::internal::setLastError("Device, create info, and pipeline output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *pipeline = nullptr;

    VkPipeline handle = VK_NULL_HANDLE;
    const VkPipelineCache cacheHandle = pipelineCache != nullptr ? pipelineCache->handle : VK_NULL_HANDLE;
    const VkResult result = vkCreateGraphicsPipelines(
        device->handle,
        cacheHandle,
        1,
        createInfo,
        allocator,
        &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create graphics pipeline.");
        return result;
    }

    GPUPipeline wrapper = new (std::nothrow) GPUPipeline_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyPipeline(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Pipeline.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *pipeline = wrapper;
    return VK_SUCCESS;
}

GPU_API VkResult GPU_CALL gpuPipelineCreateCompute(
    GPUDevice device,
    GPUPipelineCache pipelineCache,
    const VkComputePipelineCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipeline* pipeline) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || pipeline == nullptr) {
        gpu::internal::setLastError("Device, create info, and pipeline output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *pipeline = nullptr;

    VkPipeline handle = VK_NULL_HANDLE;
    const VkPipelineCache cacheHandle = pipelineCache != nullptr ? pipelineCache->handle : VK_NULL_HANDLE;
    const VkResult result = vkCreateComputePipelines(
        device->handle,
        cacheHandle,
        1,
        createInfo,
        allocator,
        &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create compute pipeline.");
        return result;
    }

    GPUPipeline wrapper = new (std::nothrow) GPUPipeline_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyPipeline(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Pipeline.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *pipeline = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuPipelineDestroy(GPUPipeline pipeline) {
    if (pipeline == nullptr) {
        return;
    }

    vkDestroyPipeline(pipeline->device->handle, pipeline->handle, pipeline->allocator);
    delete pipeline;
}

GPU_API VkPipeline GPU_CALL gpuPipelineGetVkHandle(GPUPipeline pipeline) {
    return pipeline != nullptr ? pipeline->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuPipelineGetDevice(GPUPipeline pipeline) {
    return pipeline != nullptr ? pipeline->device : nullptr;
}

}  // extern "C"

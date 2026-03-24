#include "PipelineLayout.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuPipelineLayoutCreate(
    GPUDevice device,
    const VkPipelineLayoutCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipelineLayout* pipelineLayout) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || pipelineLayout == nullptr) {
        gpu::internal::setLastError("Device, create info, and pipeline layout output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *pipelineLayout = nullptr;

    VkPipelineLayout handle = VK_NULL_HANDLE;
    const VkResult result = vkCreatePipelineLayout(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create pipeline layout.");
        return result;
    }

    GPUPipelineLayout wrapper = new (std::nothrow) GPUPipelineLayout_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyPipelineLayout(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate PipelineLayout.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *pipelineLayout = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuPipelineLayoutDestroy(GPUPipelineLayout pipelineLayout) {
    if (pipelineLayout == nullptr) {
        return;
    }

    vkDestroyPipelineLayout(pipelineLayout->device->handle, pipelineLayout->handle, pipelineLayout->allocator);
    delete pipelineLayout;
}

GPU_API VkPipelineLayout GPU_CALL gpuPipelineLayoutGetVkHandle(GPUPipelineLayout pipelineLayout) {
    return pipelineLayout != nullptr ? pipelineLayout->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuPipelineLayoutGetDevice(GPUPipelineLayout pipelineLayout) {
    return pipelineLayout != nullptr ? pipelineLayout->device : nullptr;
}

}  // extern "C"

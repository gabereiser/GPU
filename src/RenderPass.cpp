#include "RenderPass.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuRenderPassCreate(
    GPUDevice device,
    const VkRenderPassCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPURenderPass* renderPass) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || renderPass == nullptr) {
        gpu::internal::setLastError("Device, create info, and render pass output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *renderPass = nullptr;

    VkRenderPass handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateRenderPass(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create render pass.");
        return result;
    }

    GPURenderPass wrapper = new (std::nothrow) GPURenderPass_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyRenderPass(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate RenderPass.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *renderPass = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuRenderPassDestroy(GPURenderPass renderPass) {
    if (renderPass == nullptr) {
        return;
    }

    vkDestroyRenderPass(renderPass->device->handle, renderPass->handle, renderPass->allocator);
    delete renderPass;
}

GPU_API VkRenderPass GPU_CALL gpuRenderPassGetVkHandle(GPURenderPass renderPass) {
    return renderPass != nullptr ? renderPass->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuRenderPassGetDevice(GPURenderPass renderPass) {
    return renderPass != nullptr ? renderPass->device : nullptr;
}

}  // extern "C"

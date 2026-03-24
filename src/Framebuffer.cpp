#include "Framebuffer.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuFramebufferCreate(
    GPUDevice device,
    const VkFramebufferCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUFramebuffer* framebuffer) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || framebuffer == nullptr) {
        gpu::internal::setLastError("Device, create info, and framebuffer output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *framebuffer = nullptr;

    VkFramebuffer handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateFramebuffer(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create framebuffer.");
        return result;
    }

    GPUFramebuffer wrapper = new (std::nothrow) GPUFramebuffer_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyFramebuffer(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Framebuffer.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *framebuffer = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuFramebufferDestroy(GPUFramebuffer framebuffer) {
    if (framebuffer == nullptr) {
        return;
    }

    vkDestroyFramebuffer(framebuffer->device->handle, framebuffer->handle, framebuffer->allocator);
    delete framebuffer;
}

GPU_API VkFramebuffer GPU_CALL gpuFramebufferGetVkHandle(GPUFramebuffer framebuffer) {
    return framebuffer != nullptr ? framebuffer->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuFramebufferGetDevice(GPUFramebuffer framebuffer) {
    return framebuffer != nullptr ? framebuffer->device : nullptr;
}

}  // extern "C"

#include "Buffer.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuBufferCreate(
    GPUDevice device,
    const VkBufferCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUBuffer* buffer) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || buffer == nullptr) {
        gpu::internal::setLastError("Device, create info, and buffer output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *buffer = nullptr;

    VkBuffer handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateBuffer(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create buffer.");
        return result;
    }

    GPUBuffer wrapper = new (std::nothrow) GPUBuffer_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyBuffer(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Buffer.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *buffer = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuBufferDestroy(GPUBuffer buffer) {
    if (buffer == nullptr) {
        return;
    }

    vkDestroyBuffer(buffer->deviceHandle, buffer->handle, buffer->allocator);
    delete buffer;
}

GPU_API VkBuffer GPU_CALL gpuBufferGetVkHandle(GPUBuffer buffer) {
    return buffer != nullptr ? buffer->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuBufferGetDevice(GPUBuffer buffer) {
    return buffer != nullptr ? buffer->device : nullptr;
}

}  // extern "C"

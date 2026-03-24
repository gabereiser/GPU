#include "CommandPool.h"
#include "CommandBuffer.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuCommandPoolCreate(
    GPUDevice device,
    const VkCommandPoolCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCommandPool* commandPool) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || commandPool == nullptr) {
        gpu::internal::setLastError("Device, create info, and command pool output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *commandPool = nullptr;

    VkCommandPool handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateCommandPool(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create command pool.");
        return result;
    }

    GPUCommandPool wrapper = new (std::nothrow) GPUCommandPool_T{device, device->handle, handle, allocator, nullptr};
    if (wrapper == nullptr) {
        vkDestroyCommandPool(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate CommandPool.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *commandPool = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuCommandPoolDestroy(GPUCommandPool commandPool) {
    if (commandPool == nullptr) {
        return;
    }

    GPUCommandBuffer buffer = commandPool->firstCommandBuffer;
    while (buffer != nullptr) {
        GPUCommandBuffer next = buffer->next;
        vkFreeCommandBuffers(commandPool->deviceHandle, commandPool->handle, 1, &buffer->handle);
        delete buffer;
        buffer = next;
    }

    vkDestroyCommandPool(commandPool->deviceHandle, commandPool->handle, commandPool->allocator);
    delete commandPool;
}

GPU_API VkCommandPool GPU_CALL gpuCommandPoolGetVkHandle(GPUCommandPool commandPool) {
    return commandPool != nullptr ? commandPool->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuCommandPoolGetDevice(GPUCommandPool commandPool) {
    return commandPool != nullptr ? commandPool->device : nullptr;
}

}  // extern "C"

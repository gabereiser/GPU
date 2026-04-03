#include "CommandBuffer.h"

#include <new>

#include "CommandPool.h"
#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuCommandBufferCreate(
    GPUCommandPool commandPool,
    VkCommandBufferLevel level,
    GPUCommandBuffer* commandBuffer) {
    gpu::internal::clearLastError();

    if (commandPool == nullptr || commandBuffer == nullptr) {
        gpu::internal::setLastError("Command pool and command buffer output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *commandBuffer = nullptr;

    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.commandPool = commandPool->handle;
    allocateInfo.level = level;
    allocateInfo.commandBufferCount = 1;

    VkCommandBuffer handle = VK_NULL_HANDLE;
    const VkResult result = gpuAllocateCommandBuffers(commandPool->device->handle, &allocateInfo, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to allocate command buffer.");
        return result;
    }

    GPUCommandBuffer wrapper = new (std::nothrow) GPUCommandBuffer_T{
        commandPool,
        commandPool->deviceHandle,
        commandPool->handle,
        handle,
        level,
        nullptr,
        nullptr};
    if (wrapper == nullptr) {
        gpuFreeCommandBuffers(commandPool->device->handle, commandPool->handle, 1, &handle);
        gpu::internal::setLastError("Failed to allocate CommandBuffer.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    wrapper->next = commandPool->firstCommandBuffer;
    if (wrapper->next != nullptr) {
        wrapper->next->previous = wrapper;
    }
    commandPool->firstCommandBuffer = wrapper;

    *commandBuffer = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuCommandBufferDestroy(GPUCommandBuffer commandBuffer) {
    if (commandBuffer == nullptr) {
        return;
    }

    if (commandBuffer->previous != nullptr) {
        commandBuffer->previous->next = commandBuffer->next;
    } else if (commandBuffer->commandPool != nullptr) {
        commandBuffer->commandPool->firstCommandBuffer = commandBuffer->next;
    }

    if (commandBuffer->next != nullptr) {
        commandBuffer->next->previous = commandBuffer->previous;
    }

    gpuFreeCommandBuffers(
        commandBuffer->deviceHandle,
        commandBuffer->commandPoolHandle,
        1,
        &commandBuffer->handle);
    delete commandBuffer;
}

GPU_API VkCommandBuffer GPU_CALL gpuCommandBufferGetVkHandle(GPUCommandBuffer commandBuffer) {
    return commandBuffer != nullptr ? commandBuffer->handle : VK_NULL_HANDLE;
}

GPU_API GPUCommandPool GPU_CALL gpuCommandBufferGetCommandPool(GPUCommandBuffer commandBuffer) {
    return commandBuffer != nullptr ? commandBuffer->commandPool : nullptr;
}

}  // extern "C"

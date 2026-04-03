#include "Fence.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuFenceCreate(
    GPUDevice device,
    const VkFenceCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUFence* fence) {
    gpu::internal::clearLastError();

    if (device == nullptr || fence == nullptr) {
        gpu::internal::setLastError("Device and fence output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *fence = nullptr;

    VkFenceCreateInfo defaultCreateInfo{};
    defaultCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    defaultCreateInfo.flags = 0;

    const VkFenceCreateInfo* actualCreateInfo = createInfo != nullptr ? createInfo : &defaultCreateInfo;

    VkFence handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateFence(device->handle, actualCreateInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create fence.");
        return result;
    }

    GPUFence wrapper = new (std::nothrow) GPUFence_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        gpuDestroyFence(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Fence.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *fence = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuFenceDestroy(GPUFence fence) {
    if (fence == nullptr) {
        return;
    }

    gpuDestroyFence(fence->deviceHandle, fence->handle, fence->allocator);
    delete fence;
}

GPU_API VkFence GPU_CALL gpuFenceGetVkHandle(GPUFence fence) {
    return fence != nullptr ? fence->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuFenceGetDevice(GPUFence fence) {
    return fence != nullptr ? fence->device : nullptr;
}

}  // extern "C"

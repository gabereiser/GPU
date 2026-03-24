#include "QueryPool.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuQueryPoolCreate(
    GPUDevice device,
    const VkQueryPoolCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUQueryPool* queryPool) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || queryPool == nullptr) {
        gpu::internal::setLastError("Device, create info, and query pool output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *queryPool = nullptr;

    VkQueryPool handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateQueryPool(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create query pool.");
        return result;
    }

    GPUQueryPool wrapper = new (std::nothrow) GPUQueryPool_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyQueryPool(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate QueryPool.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *queryPool = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuQueryPoolDestroy(GPUQueryPool queryPool) {
    if (queryPool == nullptr) {
        return;
    }

    vkDestroyQueryPool(queryPool->deviceHandle, queryPool->handle, queryPool->allocator);
    delete queryPool;
}

GPU_API VkQueryPool GPU_CALL gpuQueryPoolGetVkHandle(GPUQueryPool queryPool) {
    return queryPool != nullptr ? queryPool->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuQueryPoolGetDevice(GPUQueryPool queryPool) {
    return queryPool != nullptr ? queryPool->device : nullptr;
}

}  // extern "C"

#include "DescriptorPool.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDescriptorPoolCreate(
    GPUDevice device,
    const VkDescriptorPoolCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDescriptorPool* descriptorPool) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || descriptorPool == nullptr) {
        gpu::internal::setLastError("Device, create info, and descriptor pool output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *descriptorPool = nullptr;

    VkDescriptorPool handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateDescriptorPool(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create descriptor pool.");
        return result;
    }

    GPUDescriptorPool wrapper = new (std::nothrow) GPUDescriptorPool_T{device, handle, allocator};
    if (wrapper == nullptr) {
        gpuDestroyDescriptorPool(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate DescriptorPool.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *descriptorPool = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDescriptorPoolDestroy(GPUDescriptorPool descriptorPool) {
    if (descriptorPool == nullptr) {
        return;
    }

    gpuDestroyDescriptorPool(
        descriptorPool->device->handle,
        descriptorPool->handle,
        descriptorPool->allocator);
    delete descriptorPool;
}

GPU_API VkDescriptorPool GPU_CALL gpuDescriptorPoolGetVkHandle(GPUDescriptorPool descriptorPool) {
    return descriptorPool != nullptr ? descriptorPool->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuDescriptorPoolGetDevice(GPUDescriptorPool descriptorPool) {
    return descriptorPool != nullptr ? descriptorPool->device : nullptr;
}

}  // extern "C"

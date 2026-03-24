#include "Sampler.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuSamplerCreate(
    GPUDevice device,
    const VkSamplerCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSampler* sampler) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || sampler == nullptr) {
        gpu::internal::setLastError("Device, create info, and sampler output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *sampler = nullptr;

    VkSampler handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateSampler(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create sampler.");
        return result;
    }

    GPUSampler wrapper = new (std::nothrow) GPUSampler_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroySampler(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Sampler.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *sampler = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuSamplerDestroy(GPUSampler sampler) {
    if (sampler == nullptr) {
        return;
    }

    vkDestroySampler(sampler->device->handle, sampler->handle, sampler->allocator);
    delete sampler;
}

GPU_API VkSampler GPU_CALL gpuSamplerGetVkHandle(GPUSampler sampler) {
    return sampler != nullptr ? sampler->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuSamplerGetDevice(GPUSampler sampler) {
    return sampler != nullptr ? sampler->device : nullptr;
}

}  // extern "C"

#include "SamplerYcbcrConversion.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuSamplerYcbcrConversionCreate(
    GPUDevice device,
    const VkSamplerYcbcrConversionCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSamplerYcbcrConversion* samplerYcbcrConversion) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || samplerYcbcrConversion == nullptr) {
        gpu::internal::setLastError("Device, create info, and sampler YCbCr conversion output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *samplerYcbcrConversion = nullptr;

    VkSamplerYcbcrConversion handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateSamplerYcbcrConversion(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create sampler YCbCr conversion.");
        return result;
    }

    GPUSamplerYcbcrConversion wrapper = new (std::nothrow) GPUSamplerYcbcrConversion_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroySamplerYcbcrConversion(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate SamplerYcbcrConversion.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *samplerYcbcrConversion = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuSamplerYcbcrConversionDestroy(GPUSamplerYcbcrConversion samplerYcbcrConversion) {
    if (samplerYcbcrConversion == nullptr) {
        return;
    }

    vkDestroySamplerYcbcrConversion(
        samplerYcbcrConversion->device->handle,
        samplerYcbcrConversion->handle,
        samplerYcbcrConversion->allocator);
    delete samplerYcbcrConversion;
}

GPU_API VkSamplerYcbcrConversion GPU_CALL gpuSamplerYcbcrConversionGetVkHandle(
    GPUSamplerYcbcrConversion samplerYcbcrConversion) {
    return samplerYcbcrConversion != nullptr ? samplerYcbcrConversion->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuSamplerYcbcrConversionGetDevice(
    GPUSamplerYcbcrConversion samplerYcbcrConversion) {
    return samplerYcbcrConversion != nullptr ? samplerYcbcrConversion->device : nullptr;
}

GPU_API VkSamplerYcbcrConversion GPU_CALL gpuSamplerYcbcrConversionKHRGetVkHandle(
    GPUSamplerYcbcrConversion samplerYcbcrConversion) {
    return gpuSamplerYcbcrConversionGetVkHandle(samplerYcbcrConversion);
}

GPU_API GPUDevice GPU_CALL gpuSamplerYcbcrConversionKHRGetDevice(
    GPUSamplerYcbcrConversion samplerYcbcrConversion) {
    return gpuSamplerYcbcrConversionGetDevice(samplerYcbcrConversion);
}

}  // extern "C"

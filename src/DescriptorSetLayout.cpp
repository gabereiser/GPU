#include "DescriptorSetLayout.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDescriptorSetLayoutCreate(
    GPUDevice device,
    const VkDescriptorSetLayoutCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDescriptorSetLayout* descriptorSetLayout) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || descriptorSetLayout == nullptr) {
        gpu::internal::setLastError("Device, create info, and descriptor set layout output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *descriptorSetLayout = nullptr;

    VkDescriptorSetLayout handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateDescriptorSetLayout(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create descriptor set layout.");
        return result;
    }

    GPUDescriptorSetLayout wrapper = new (std::nothrow) GPUDescriptorSetLayout_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyDescriptorSetLayout(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate DescriptorSetLayout.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *descriptorSetLayout = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDescriptorSetLayoutDestroy(GPUDescriptorSetLayout descriptorSetLayout) {
    if (descriptorSetLayout == nullptr) {
        return;
    }

    vkDestroyDescriptorSetLayout(
        descriptorSetLayout->device->handle,
        descriptorSetLayout->handle,
        descriptorSetLayout->allocator);
    delete descriptorSetLayout;
}

GPU_API VkDescriptorSetLayout GPU_CALL gpuDescriptorSetLayoutGetVkHandle(GPUDescriptorSetLayout descriptorSetLayout) {
    return descriptorSetLayout != nullptr ? descriptorSetLayout->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuDescriptorSetLayoutGetDevice(GPUDescriptorSetLayout descriptorSetLayout) {
    return descriptorSetLayout != nullptr ? descriptorSetLayout->device : nullptr;
}

}  // extern "C"

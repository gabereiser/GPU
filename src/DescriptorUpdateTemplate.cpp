#include "DescriptorUpdateTemplate.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDescriptorUpdateTemplateCreate(
    GPUDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDescriptorUpdateTemplate* descriptorUpdateTemplate) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || descriptorUpdateTemplate == nullptr) {
        gpu::internal::setLastError("Device, create info, and descriptor update template output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *descriptorUpdateTemplate = nullptr;

    VkDescriptorUpdateTemplate handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateDescriptorUpdateTemplate(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create descriptor update template.");
        return result;
    }

    GPUDescriptorUpdateTemplate wrapper = new (std::nothrow) GPUDescriptorUpdateTemplate_T{device, handle, allocator};
    if (wrapper == nullptr) {
        gpuDestroyDescriptorUpdateTemplate(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate DescriptorUpdateTemplate.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *descriptorUpdateTemplate = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDescriptorUpdateTemplateDestroy(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate) {
    if (descriptorUpdateTemplate == nullptr) {
        return;
    }

    gpuDestroyDescriptorUpdateTemplate(
        descriptorUpdateTemplate->device->handle,
        descriptorUpdateTemplate->handle,
        descriptorUpdateTemplate->allocator);
    delete descriptorUpdateTemplate;
}

GPU_API VkDescriptorUpdateTemplate GPU_CALL gpuDescriptorUpdateTemplateGetVkHandle(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate) {
    return descriptorUpdateTemplate != nullptr ? descriptorUpdateTemplate->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuDescriptorUpdateTemplateGetDevice(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate) {
    return descriptorUpdateTemplate != nullptr ? descriptorUpdateTemplate->device : nullptr;
}

GPU_API VkDescriptorUpdateTemplate GPU_CALL gpuDescriptorUpdateTemplateKHRGetVkHandle(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate) {
    return gpuDescriptorUpdateTemplateGetVkHandle(descriptorUpdateTemplate);
}

GPU_API GPUDevice GPU_CALL gpuDescriptorUpdateTemplateKHRGetDevice(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate) {
    return gpuDescriptorUpdateTemplateGetDevice(descriptorUpdateTemplate);
}

}  // extern "C"

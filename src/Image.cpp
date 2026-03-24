#include "Image.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuImageCreate(
    GPUDevice device,
    const VkImageCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUImage* image) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || image == nullptr) {
        gpu::internal::setLastError("Device, create info, and image output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *image = nullptr;

    VkImage handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateImage(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create image.");
        return result;
    }

    GPUImage wrapper = new (std::nothrow) GPUImage_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyImage(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Image.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *image = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuImageDestroy(GPUImage image) {
    if (image == nullptr) {
        return;
    }

    vkDestroyImage(image->deviceHandle, image->handle, image->allocator);
    delete image;
}

GPU_API VkImage GPU_CALL gpuImageGetVkHandle(GPUImage image) {
    return image != nullptr ? image->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuImageGetDevice(GPUImage image) {
    return image != nullptr ? image->device : nullptr;
}

}  // extern "C"

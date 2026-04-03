#include "ImageView.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuImageViewCreate(
    GPUDevice device,
    const VkImageViewCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUImageView* imageView) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || imageView == nullptr) {
        gpu::internal::setLastError("Device, create info, and image view output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *imageView = nullptr;

    VkImageView handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateImageView(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create image view.");
        return result;
    }

    GPUImageView wrapper = new (std::nothrow) GPUImageView_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        gpuDestroyImageView(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate ImageView.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *imageView = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuImageViewDestroy(GPUImageView imageView) {
    if (imageView == nullptr) {
        return;
    }

    gpuDestroyImageView(imageView->deviceHandle, imageView->handle, imageView->allocator);
    delete imageView;
}

GPU_API VkImageView GPU_CALL gpuImageViewGetVkHandle(GPUImageView imageView) {
    return imageView != nullptr ? imageView->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuImageViewGetDevice(GPUImageView imageView) {
    return imageView != nullptr ? imageView->device : nullptr;
}

}  // extern "C"

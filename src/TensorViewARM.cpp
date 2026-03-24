#include "TensorViewARM.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuTensorViewARMCreate(
    GPUDevice device,
    const VkTensorViewCreateInfoARM* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUTensorViewARM* tensorView) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || tensorView == nullptr) {
        gpu::internal::setLastError("Device, create info, and tensor view output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *tensorView = nullptr;

    VkTensorViewARM handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateTensorViewARM(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create tensor view ARM.");
        return result;
    }

    GPUTensorViewARM wrapper = new (std::nothrow) GPUTensorViewARM_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyTensorViewARM(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate TensorViewARM.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *tensorView = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuTensorViewARMDestroy(GPUTensorViewARM tensorView) {
    if (tensorView == nullptr || tensorView->destroyRequested) {
        return;
    }

    tensorView->destroyRequested = true;
    vkDestroyTensorViewARM(tensorView->device->handle, tensorView->handle, tensorView->allocator);
    gpuDeviceDrop(tensorView->device);
    delete tensorView;
}

GPU_API VkTensorViewARM GPU_CALL gpuTensorViewARMGetVkHandle(GPUTensorViewARM tensorView) {
    return tensorView != nullptr && !tensorView->destroyRequested ? tensorView->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuTensorViewARMGetDevice(GPUTensorViewARM tensorView) {
    return tensorView != nullptr && !tensorView->destroyRequested ? tensorView->device : nullptr;
}

}  // extern "C"

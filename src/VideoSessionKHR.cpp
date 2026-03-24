#include "VideoSessionKHR.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuVideoSessionKHRCreate(
    GPUDevice device,
    const VkVideoSessionCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUVideoSessionKHR* videoSession) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || videoSession == nullptr) {
        gpu::internal::setLastError("Device, create info, and video session output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *videoSession = nullptr;

    VkVideoSessionKHR handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateVideoSessionKHR(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create video session KHR.");
        return result;
    }

    GPUVideoSessionKHR wrapper = new (std::nothrow) GPUVideoSessionKHR_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyVideoSessionKHR(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate VideoSessionKHR.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *videoSession = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuVideoSessionKHRDestroy(GPUVideoSessionKHR videoSession) {
    if (videoSession == nullptr || videoSession->destroyRequested) {
        return;
    }

    videoSession->destroyRequested = true;
    vkDestroyVideoSessionKHR(videoSession->device->handle, videoSession->handle, videoSession->allocator);
    gpuDeviceDrop(videoSession->device);
    delete videoSession;
}

GPU_API VkVideoSessionKHR GPU_CALL gpuVideoSessionKHRGetVkHandle(GPUVideoSessionKHR videoSession) {
    return videoSession != nullptr && !videoSession->destroyRequested ? videoSession->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuVideoSessionKHRGetDevice(GPUVideoSessionKHR videoSession) {
    return videoSession != nullptr && !videoSession->destroyRequested ? videoSession->device : nullptr;
}

}  // extern "C"

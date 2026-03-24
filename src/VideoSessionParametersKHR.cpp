#include "VideoSessionParametersKHR.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuVideoSessionParametersKHRCreate(
    GPUDevice device,
    const VkVideoSessionParametersCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUVideoSessionParametersKHR* videoSessionParameters) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || videoSessionParameters == nullptr) {
        gpu::internal::setLastError("Device, create info, and video session parameters output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *videoSessionParameters = nullptr;

    VkVideoSessionParametersKHR handle = VK_NULL_HANDLE;
    const VkResult result =
        vkCreateVideoSessionParametersKHR(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create video session parameters KHR.");
        return result;
    }

    GPUVideoSessionParametersKHR wrapper =
        new (std::nothrow) GPUVideoSessionParametersKHR_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyVideoSessionParametersKHR(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate VideoSessionParametersKHR.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *videoSessionParameters = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuVideoSessionParametersKHRDestroy(GPUVideoSessionParametersKHR videoSessionParameters) {
    if (videoSessionParameters == nullptr || videoSessionParameters->destroyRequested) {
        return;
    }

    videoSessionParameters->destroyRequested = true;
    vkDestroyVideoSessionParametersKHR(
        videoSessionParameters->device->handle,
        videoSessionParameters->handle,
        videoSessionParameters->allocator);
    gpuDeviceDrop(videoSessionParameters->device);
    delete videoSessionParameters;
}

GPU_API VkVideoSessionParametersKHR GPU_CALL gpuVideoSessionParametersKHRGetVkHandle(
    GPUVideoSessionParametersKHR videoSessionParameters) {
    return videoSessionParameters != nullptr && !videoSessionParameters->destroyRequested
        ? videoSessionParameters->handle
        : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuVideoSessionParametersKHRGetDevice(
    GPUVideoSessionParametersKHR videoSessionParameters) {
    return videoSessionParameters != nullptr && !videoSessionParameters->destroyRequested
        ? videoSessionParameters->device
        : nullptr;
}

}  // extern "C"

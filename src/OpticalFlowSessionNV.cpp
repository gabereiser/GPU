#include "OpticalFlowSessionNV.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuOpticalFlowSessionNVCreate(
    GPUDevice device,
    const VkOpticalFlowSessionCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUOpticalFlowSessionNV* opticalFlowSession) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || opticalFlowSession == nullptr) {
        gpu::internal::setLastError("Device, create info, and optical flow session output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *opticalFlowSession = nullptr;

    VkOpticalFlowSessionNV handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateOpticalFlowSessionNV(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create optical flow session NV.");
        return result;
    }

    GPUOpticalFlowSessionNV wrapper =
        new (std::nothrow) GPUOpticalFlowSessionNV_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyOpticalFlowSessionNV(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate OpticalFlowSessionNV.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *opticalFlowSession = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuOpticalFlowSessionNVDestroy(GPUOpticalFlowSessionNV opticalFlowSession) {
    if (opticalFlowSession == nullptr || opticalFlowSession->destroyRequested) {
        return;
    }

    opticalFlowSession->destroyRequested = true;
    vkDestroyOpticalFlowSessionNV(
        opticalFlowSession->device->handle,
        opticalFlowSession->handle,
        opticalFlowSession->allocator);
    gpuDeviceDrop(opticalFlowSession->device);
    delete opticalFlowSession;
}

GPU_API VkOpticalFlowSessionNV GPU_CALL gpuOpticalFlowSessionNVGetVkHandle(
    GPUOpticalFlowSessionNV opticalFlowSession) {
    return opticalFlowSession != nullptr && !opticalFlowSession->destroyRequested
        ? opticalFlowSession->handle
        : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuOpticalFlowSessionNVGetDevice(GPUOpticalFlowSessionNV opticalFlowSession) {
    return opticalFlowSession != nullptr && !opticalFlowSession->destroyRequested
        ? opticalFlowSession->device
        : nullptr;
}

}  // extern "C"

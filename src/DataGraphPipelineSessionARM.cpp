#include "DataGraphPipelineSessionARM.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDataGraphPipelineSessionARMCreate(
    GPUDevice device,
    const VkDataGraphPipelineSessionCreateInfoARM* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDataGraphPipelineSessionARM* session) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || session == nullptr) {
        gpu::internal::setLastError("Device, create info, and data graph pipeline session output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *session = nullptr;

    VkDataGraphPipelineSessionARM handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateDataGraphPipelineSessionARM(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create data graph pipeline session ARM.");
        return result;
    }

    GPUDataGraphPipelineSessionARM wrapper =
        new (std::nothrow) GPUDataGraphPipelineSessionARM_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        gpuDestroyDataGraphPipelineSessionARM(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate DataGraphPipelineSessionARM.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *session = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDataGraphPipelineSessionARMDestroy(GPUDataGraphPipelineSessionARM session) {
    if (session == nullptr || session->destroyRequested) {
        return;
    }

    session->destroyRequested = true;
    gpuDestroyDataGraphPipelineSessionARM(session->device->handle, session->handle, session->allocator);
    gpuDeviceDrop(session->device);
    delete session;
}

GPU_API VkDataGraphPipelineSessionARM GPU_CALL gpuDataGraphPipelineSessionARMGetVkHandle(
    GPUDataGraphPipelineSessionARM session) {
    return session != nullptr && !session->destroyRequested ? session->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuDataGraphPipelineSessionARMGetDevice(GPUDataGraphPipelineSessionARM session) {
    return session != nullptr && !session->destroyRequested ? session->device : nullptr;
}

}  // extern "C"

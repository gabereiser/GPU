#include "PipelineBinaryKHR.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuPipelineBinaryKHRCreate(
    GPUDevice device,
    const VkPipelineBinaryCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipelineBinaryKHR* pipelineBinary) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || pipelineBinary == nullptr) {
        gpu::internal::setLastError("Device, create info, and pipeline binary output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *pipelineBinary = nullptr;

    VkPipelineBinaryKHR handle = VK_NULL_HANDLE;
    VkPipelineBinaryHandlesInfoKHR handlesInfo{};
    handlesInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_BINARY_HANDLES_INFO_KHR;
    handlesInfo.pipelineBinaryCount = 1;
    handlesInfo.pPipelineBinaries = &handle;

    const VkResult result = vkCreatePipelineBinariesKHR(device->handle, createInfo, allocator, &handlesInfo);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create pipeline binary KHR.");
        return result;
    }

    GPUPipelineBinaryKHR wrapper =
        new (std::nothrow) GPUPipelineBinaryKHR_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyPipelineBinaryKHR(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate PipelineBinaryKHR.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *pipelineBinary = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuPipelineBinaryKHRDestroy(GPUPipelineBinaryKHR pipelineBinary) {
    if (pipelineBinary == nullptr || pipelineBinary->destroyRequested) {
        return;
    }

    pipelineBinary->destroyRequested = true;
    vkDestroyPipelineBinaryKHR(pipelineBinary->device->handle, pipelineBinary->handle, pipelineBinary->allocator);
    gpuDeviceDrop(pipelineBinary->device);
    delete pipelineBinary;
}

GPU_API VkPipelineBinaryKHR GPU_CALL gpuPipelineBinaryKHRGetVkHandle(GPUPipelineBinaryKHR pipelineBinary) {
    return pipelineBinary != nullptr && !pipelineBinary->destroyRequested ? pipelineBinary->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuPipelineBinaryKHRGetDevice(GPUPipelineBinaryKHR pipelineBinary) {
    return pipelineBinary != nullptr && !pipelineBinary->destroyRequested ? pipelineBinary->device : nullptr;
}

}  // extern "C"

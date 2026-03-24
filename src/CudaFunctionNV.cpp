#include "CudaFunctionNV.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuCudaFunctionNVCreate(
    GPUDevice device,
    const VkCudaFunctionCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCudaFunctionNV* function) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || function == nullptr) {
        gpu::internal::setLastError("Device, create info, and CUDA function output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *function = nullptr;

    VkCudaFunctionNV handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateCudaFunctionNV(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create CUDA function NV.");
        return result;
    }

    GPUCudaFunctionNV wrapper = new (std::nothrow) GPUCudaFunctionNV_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyCudaFunctionNV(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate CudaFunctionNV.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *function = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuCudaFunctionNVDestroy(GPUCudaFunctionNV function) {
    if (function == nullptr || function->destroyRequested) {
        return;
    }

    function->destroyRequested = true;
    vkDestroyCudaFunctionNV(function->device->handle, function->handle, function->allocator);
    gpuDeviceDrop(function->device);
    delete function;
}

GPU_API VkCudaFunctionNV GPU_CALL gpuCudaFunctionNVGetVkHandle(GPUCudaFunctionNV function) {
    return function != nullptr && !function->destroyRequested ? function->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuCudaFunctionNVGetDevice(GPUCudaFunctionNV function) {
    return function != nullptr && !function->destroyRequested ? function->device : nullptr;
}

}  // extern "C"

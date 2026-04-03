#include "CuFunctionNVX.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuCuFunctionNVXCreate(
    GPUDevice device,
    const VkCuFunctionCreateInfoNVX* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCuFunctionNVX* cuFunction) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || cuFunction == nullptr) {
        gpu::internal::setLastError("Device, create info, and CUDA function output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *cuFunction = nullptr;

    VkCuFunctionNVX handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateCuFunctionNVX(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create CUDA function NVX.");
        return result;
    }

    GPUCuFunctionNVX wrapper = new (std::nothrow) GPUCuFunctionNVX_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        gpuDestroyCuFunctionNVX(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate CuFunctionNVX.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *cuFunction = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuCuFunctionNVXDestroy(GPUCuFunctionNVX cuFunction) {
    if (cuFunction == nullptr || cuFunction->destroyRequested) {
        return;
    }

    cuFunction->destroyRequested = true;
    gpuDestroyCuFunctionNVX(cuFunction->device->handle, cuFunction->handle, cuFunction->allocator);
    gpuDeviceDrop(cuFunction->device);
    delete cuFunction;
}

GPU_API VkCuFunctionNVX GPU_CALL gpuCuFunctionNVXGetVkHandle(GPUCuFunctionNVX cuFunction) {
    return cuFunction != nullptr && !cuFunction->destroyRequested ? cuFunction->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuCuFunctionNVXGetDevice(GPUCuFunctionNVX cuFunction) {
    return cuFunction != nullptr && !cuFunction->destroyRequested ? cuFunction->device : nullptr;
}

}  // extern "C"

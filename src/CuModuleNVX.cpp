#include "CuModuleNVX.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuCuModuleNVXCreate(
    GPUDevice device,
    const VkCuModuleCreateInfoNVX* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCuModuleNVX* cuModule) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || cuModule == nullptr) {
        gpu::internal::setLastError("Device, create info, and CUDA module output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *cuModule = nullptr;

    VkCuModuleNVX handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateCuModuleNVX(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create CUDA module NVX.");
        return result;
    }

    GPUCuModuleNVX wrapper = new (std::nothrow) GPUCuModuleNVX_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        gpuDestroyCuModuleNVX(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate CuModuleNVX.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *cuModule = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuCuModuleNVXDestroy(GPUCuModuleNVX cuModule) {
    if (cuModule == nullptr || cuModule->destroyRequested) {
        return;
    }

    cuModule->destroyRequested = true;
    gpuDestroyCuModuleNVX(cuModule->device->handle, cuModule->handle, cuModule->allocator);
    gpuDeviceDrop(cuModule->device);
    delete cuModule;
}

GPU_API VkCuModuleNVX GPU_CALL gpuCuModuleNVXGetVkHandle(GPUCuModuleNVX cuModule) {
    return cuModule != nullptr && !cuModule->destroyRequested ? cuModule->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuCuModuleNVXGetDevice(GPUCuModuleNVX cuModule) {
    return cuModule != nullptr && !cuModule->destroyRequested ? cuModule->device : nullptr;
}

}  // extern "C"

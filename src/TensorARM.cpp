#include "TensorARM.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuTensorARMCreate(
    GPUDevice device,
    const VkTensorCreateInfoARM* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUTensorARM* tensor) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || tensor == nullptr) {
        gpu::internal::setLastError("Device, create info, and tensor output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *tensor = nullptr;

    VkTensorARM handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateTensorARM(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create tensor ARM.");
        return result;
    }

    GPUTensorARM wrapper = new (std::nothrow) GPUTensorARM_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        gpuDestroyTensorARM(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate TensorARM.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *tensor = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuTensorARMDestroy(GPUTensorARM tensor) {
    if (tensor == nullptr || tensor->destroyRequested) {
        return;
    }

    tensor->destroyRequested = true;
    gpuDestroyTensorARM(tensor->device->handle, tensor->handle, tensor->allocator);
    gpuDeviceDrop(tensor->device);
    delete tensor;
}

GPU_API VkTensorARM GPU_CALL gpuTensorARMGetVkHandle(GPUTensorARM tensor) {
    return tensor != nullptr && !tensor->destroyRequested ? tensor->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuTensorARMGetDevice(GPUTensorARM tensor) {
    return tensor != nullptr && !tensor->destroyRequested ? tensor->device : nullptr;
}

}  // extern "C"

#include "DeferredOperationKHR.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDeferredOperationKHRCreate(
    GPUDevice device,
    const VkAllocationCallbacks* allocator,
    GPUDeferredOperationKHR* deferredOperation) {
    gpu::internal::clearLastError();

    if (device == nullptr || deferredOperation == nullptr) {
        gpu::internal::setLastError("Device and deferred operation output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *deferredOperation = nullptr;

    VkDeferredOperationKHR handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateDeferredOperationKHR(device->handle, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create deferred operation.");
        return result;
    }

    GPUDeferredOperationKHR wrapper =
        new (std::nothrow) GPUDeferredOperationKHR_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyDeferredOperationKHR(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate DeferredOperationKHR.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *deferredOperation = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDeferredOperationKHRDestroy(GPUDeferredOperationKHR deferredOperation) {
    if (deferredOperation == nullptr || deferredOperation->destroyRequested) {
        return;
    }

    deferredOperation->destroyRequested = true;
    vkDestroyDeferredOperationKHR(deferredOperation->device->handle, deferredOperation->handle, deferredOperation->allocator);
    gpuDeviceDrop(deferredOperation->device);
    delete deferredOperation;
}

GPU_API VkDeferredOperationKHR GPU_CALL gpuDeferredOperationKHRGetVkHandle(GPUDeferredOperationKHR deferredOperation) {
    return deferredOperation != nullptr && !deferredOperation->destroyRequested ? deferredOperation->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuDeferredOperationKHRGetDevice(GPUDeferredOperationKHR deferredOperation) {
    return deferredOperation != nullptr && !deferredOperation->destroyRequested ? deferredOperation->device : nullptr;
}

}  // extern "C"

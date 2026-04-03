#include "AccelerationStructureKHR.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuAccelerationStructureKHRCreate(
    GPUDevice device,
    const VkAccelerationStructureCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUAccelerationStructureKHR* accelerationStructure) {
    gpu::internal::clearLastError();
    if (device == nullptr || createInfo == nullptr || accelerationStructure == nullptr) {
        gpu::internal::setLastError("Device, create info, and acceleration structure output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    *accelerationStructure = nullptr;
    VkAccelerationStructureKHR handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateAccelerationStructureKHR(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create acceleration structure KHR.");
        return result;
    }
    GPUAccelerationStructureKHR wrapper = new (std::nothrow) GPUAccelerationStructureKHR_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        gpuDestroyAccelerationStructureKHR(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate AccelerationStructureKHR.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    gpuDeviceRetain(device);
    *accelerationStructure = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuAccelerationStructureKHRDestroy(GPUAccelerationStructureKHR accelerationStructure) {
    if (accelerationStructure == nullptr || accelerationStructure->destroyRequested) {
        return;
    }
    accelerationStructure->destroyRequested = true;
    gpuDestroyAccelerationStructureKHR(accelerationStructure->device->handle, accelerationStructure->handle, accelerationStructure->allocator);
    gpuDeviceDrop(accelerationStructure->device);
    delete accelerationStructure;
}

GPU_API VkAccelerationStructureKHR GPU_CALL gpuAccelerationStructureKHRGetVkHandle(GPUAccelerationStructureKHR accelerationStructure) {
    return accelerationStructure != nullptr && !accelerationStructure->destroyRequested ? accelerationStructure->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuAccelerationStructureKHRGetDevice(GPUAccelerationStructureKHR accelerationStructure) {
    return accelerationStructure != nullptr && !accelerationStructure->destroyRequested ? accelerationStructure->device : nullptr;
}

}  // extern "C"

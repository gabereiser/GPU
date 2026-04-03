#include "DeviceMemory.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDeviceMemoryCreate(
    GPUDevice device,
    const VkMemoryAllocateInfo* allocateInfo,
    const VkAllocationCallbacks* allocator,
    GPUDeviceMemory* memory) {
    gpu::internal::clearLastError();

    if (device == nullptr || allocateInfo == nullptr || memory == nullptr) {
        gpu::internal::setLastError("Device, allocate info, and memory output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *memory = nullptr;

    VkDeviceMemory handle = VK_NULL_HANDLE;
    const VkResult result = gpuAllocateMemory(device->handle, allocateInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to allocate device memory.");
        return result;
    }

    GPUDeviceMemory wrapper = new (std::nothrow) GPUDeviceMemory_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        gpuFreeMemory(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate DeviceMemory.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *memory = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDeviceMemoryDestroy(GPUDeviceMemory memory) {
    if (memory == nullptr) {
        return;
    }

    gpuFreeMemory(memory->deviceHandle, memory->handle, memory->allocator);
    delete memory;
}

GPU_API VkDeviceMemory GPU_CALL gpuDeviceMemoryGetVkHandle(GPUDeviceMemory memory) {
    return memory != nullptr ? memory->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuDeviceMemoryGetDevice(GPUDeviceMemory memory) {
    return memory != nullptr ? memory->device : nullptr;
}

}  // extern "C"

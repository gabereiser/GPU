#include "PrivateDataSlot.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuPrivateDataSlotCreate(
    GPUDevice device,
    const VkPrivateDataSlotCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPrivateDataSlot* privateDataSlot) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || privateDataSlot == nullptr) {
        gpu::internal::setLastError("Device, create info, and private data slot output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *privateDataSlot = nullptr;

    VkPrivateDataSlot handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreatePrivateDataSlot(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create private data slot.");
        return result;
    }

    GPUPrivateDataSlot wrapper = new (std::nothrow) GPUPrivateDataSlot_T{device, handle, allocator};
    if (wrapper == nullptr) {
        gpuDestroyPrivateDataSlot(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate PrivateDataSlot.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *privateDataSlot = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuPrivateDataSlotDestroy(GPUPrivateDataSlot privateDataSlot) {
    if (privateDataSlot == nullptr) {
        return;
    }

    gpuDestroyPrivateDataSlot(
        privateDataSlot->device->handle,
        privateDataSlot->handle,
        privateDataSlot->allocator);
    delete privateDataSlot;
}

GPU_API VkPrivateDataSlot GPU_CALL gpuPrivateDataSlotGetVkHandle(GPUPrivateDataSlot privateDataSlot) {
    return privateDataSlot != nullptr ? privateDataSlot->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuPrivateDataSlotGetDevice(GPUPrivateDataSlot privateDataSlot) {
    return privateDataSlot != nullptr ? privateDataSlot->device : nullptr;
}

GPU_API VkPrivateDataSlot GPU_CALL gpuPrivateDataSlotEXTGetVkHandle(GPUPrivateDataSlot privateDataSlot) {
    return gpuPrivateDataSlotGetVkHandle(privateDataSlot);
}

GPU_API GPUDevice GPU_CALL gpuPrivateDataSlotEXTGetDevice(GPUPrivateDataSlot privateDataSlot) {
    return gpuPrivateDataSlotGetDevice(privateDataSlot);
}

}  // extern "C"

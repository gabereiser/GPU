#include "IndirectCommandsLayoutNV.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuIndirectCommandsLayoutNVCreate(
    GPUDevice device,
    const VkIndirectCommandsLayoutCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUIndirectCommandsLayoutNV* indirectCommandsLayout) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || indirectCommandsLayout == nullptr) {
        gpu::internal::setLastError("Device, create info, and indirect commands layout output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *indirectCommandsLayout = nullptr;

    VkIndirectCommandsLayoutNV handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateIndirectCommandsLayoutNV(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create indirect commands layout NV.");
        return result;
    }

    GPUIndirectCommandsLayoutNV wrapper =
        new (std::nothrow) GPUIndirectCommandsLayoutNV_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyIndirectCommandsLayoutNV(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate IndirectCommandsLayoutNV.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *indirectCommandsLayout = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuIndirectCommandsLayoutNVDestroy(GPUIndirectCommandsLayoutNV indirectCommandsLayout) {
    if (indirectCommandsLayout == nullptr || indirectCommandsLayout->destroyRequested) {
        return;
    }

    indirectCommandsLayout->destroyRequested = true;
    vkDestroyIndirectCommandsLayoutNV(indirectCommandsLayout->device->handle, indirectCommandsLayout->handle, indirectCommandsLayout->allocator);
    gpuDeviceDrop(indirectCommandsLayout->device);
    delete indirectCommandsLayout;
}

GPU_API VkIndirectCommandsLayoutNV GPU_CALL gpuIndirectCommandsLayoutNVGetVkHandle(
    GPUIndirectCommandsLayoutNV indirectCommandsLayout) {
    return indirectCommandsLayout != nullptr && !indirectCommandsLayout->destroyRequested
        ? indirectCommandsLayout->handle
        : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuIndirectCommandsLayoutNVGetDevice(GPUIndirectCommandsLayoutNV indirectCommandsLayout) {
    return indirectCommandsLayout != nullptr && !indirectCommandsLayout->destroyRequested
        ? indirectCommandsLayout->device
        : nullptr;
}

}  // extern "C"

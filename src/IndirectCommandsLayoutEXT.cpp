#include "IndirectCommandsLayoutEXT.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuIndirectCommandsLayoutEXTCreate(
    GPUDevice device,
    const VkIndirectCommandsLayoutCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUIndirectCommandsLayoutEXT* indirectCommandsLayout) {
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

    VkIndirectCommandsLayoutEXT handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateIndirectCommandsLayoutEXT(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create indirect commands layout EXT.");
        return result;
    }

    GPUIndirectCommandsLayoutEXT wrapper =
        new (std::nothrow) GPUIndirectCommandsLayoutEXT_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyIndirectCommandsLayoutEXT(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate IndirectCommandsLayoutEXT.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *indirectCommandsLayout = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuIndirectCommandsLayoutEXTDestroy(GPUIndirectCommandsLayoutEXT indirectCommandsLayout) {
    if (indirectCommandsLayout == nullptr || indirectCommandsLayout->destroyRequested) {
        return;
    }

    indirectCommandsLayout->destroyRequested = true;
    vkDestroyIndirectCommandsLayoutEXT(indirectCommandsLayout->device->handle, indirectCommandsLayout->handle, indirectCommandsLayout->allocator);
    gpuDeviceDrop(indirectCommandsLayout->device);
    delete indirectCommandsLayout;
}

GPU_API VkIndirectCommandsLayoutEXT GPU_CALL gpuIndirectCommandsLayoutEXTGetVkHandle(
    GPUIndirectCommandsLayoutEXT indirectCommandsLayout) {
    return indirectCommandsLayout != nullptr && !indirectCommandsLayout->destroyRequested
        ? indirectCommandsLayout->handle
        : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuIndirectCommandsLayoutEXTGetDevice(GPUIndirectCommandsLayoutEXT indirectCommandsLayout) {
    return indirectCommandsLayout != nullptr && !indirectCommandsLayout->destroyRequested
        ? indirectCommandsLayout->device
        : nullptr;
}

}  // extern "C"

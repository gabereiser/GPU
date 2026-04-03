#include "IndirectExecutionSetEXT.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuIndirectExecutionSetEXTCreate(
    GPUDevice device,
    const VkIndirectExecutionSetCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUIndirectExecutionSetEXT* indirectExecutionSet) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || indirectExecutionSet == nullptr) {
        gpu::internal::setLastError("Device, create info, and indirect execution set output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *indirectExecutionSet = nullptr;

    VkIndirectExecutionSetEXT handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateIndirectExecutionSetEXT(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create indirect execution set EXT.");
        return result;
    }

    GPUIndirectExecutionSetEXT wrapper =
        new (std::nothrow) GPUIndirectExecutionSetEXT_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        gpuDestroyIndirectExecutionSetEXT(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate IndirectExecutionSetEXT.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *indirectExecutionSet = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuIndirectExecutionSetEXTDestroy(GPUIndirectExecutionSetEXT indirectExecutionSet) {
    if (indirectExecutionSet == nullptr || indirectExecutionSet->destroyRequested) {
        return;
    }

    indirectExecutionSet->destroyRequested = true;
    gpuDestroyIndirectExecutionSetEXT(indirectExecutionSet->device->handle, indirectExecutionSet->handle, indirectExecutionSet->allocator);
    gpuDeviceDrop(indirectExecutionSet->device);
    delete indirectExecutionSet;
}

GPU_API VkIndirectExecutionSetEXT GPU_CALL gpuIndirectExecutionSetEXTGetVkHandle(
    GPUIndirectExecutionSetEXT indirectExecutionSet) {
    return indirectExecutionSet != nullptr && !indirectExecutionSet->destroyRequested
        ? indirectExecutionSet->handle
        : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuIndirectExecutionSetEXTGetDevice(GPUIndirectExecutionSetEXT indirectExecutionSet) {
    return indirectExecutionSet != nullptr && !indirectExecutionSet->destroyRequested
        ? indirectExecutionSet->device
        : nullptr;
}

}  // extern "C"

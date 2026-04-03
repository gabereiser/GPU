#include "MicromapEXT.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuMicromapEXTCreate(
    GPUDevice device,
    const VkMicromapCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUMicromapEXT* micromap) {
    gpu::internal::clearLastError();
    if (device == nullptr || createInfo == nullptr || micromap == nullptr) {
        gpu::internal::setLastError("Device, create info, and micromap output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    *micromap = nullptr;
    VkMicromapEXT handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateMicromapEXT(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create micromap EXT.");
        return result;
    }
    GPUMicromapEXT wrapper = new (std::nothrow) GPUMicromapEXT_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        gpuDestroyMicromapEXT(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate MicromapEXT.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    gpuDeviceRetain(device);
    *micromap = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuMicromapEXTDestroy(GPUMicromapEXT micromap) {
    if (micromap == nullptr || micromap->destroyRequested) {
        return;
    }
    micromap->destroyRequested = true;
    gpuDestroyMicromapEXT(micromap->device->handle, micromap->handle, micromap->allocator);
    gpuDeviceDrop(micromap->device);
    delete micromap;
}

GPU_API VkMicromapEXT GPU_CALL gpuMicromapEXTGetVkHandle(GPUMicromapEXT micromap) {
    return micromap != nullptr && !micromap->destroyRequested ? micromap->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuMicromapEXTGetDevice(GPUMicromapEXT micromap) {
    return micromap != nullptr && !micromap->destroyRequested ? micromap->device : nullptr;
}

}  // extern "C"

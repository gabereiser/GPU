#include "BufferCollectionFUCHSIA.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuBufferCollectionFUCHSIACreate(
    GPUDevice device,
    const VkBufferCollectionCreateInfoFUCHSIA* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUBufferCollectionFUCHSIA* collection) {
    gpu::internal::clearLastError();
    if (device == nullptr || createInfo == nullptr || collection == nullptr) {
        gpu::internal::setLastError("Device, create info, and collection output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    *collection = nullptr;
    VkBufferCollectionFUCHSIA handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateBufferCollectionFUCHSIA(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create buffer collection FUCHSIA.");
        return result;
    }
    GPUBufferCollectionFUCHSIA wrapper = new (std::nothrow) GPUBufferCollectionFUCHSIA_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyBufferCollectionFUCHSIA(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate BufferCollectionFUCHSIA.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    gpuDeviceRetain(device);
    *collection = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuBufferCollectionFUCHSIADestroy(GPUBufferCollectionFUCHSIA collection) {
    if (collection == nullptr || collection->destroyRequested) {
        return;
    }
    collection->destroyRequested = true;
    vkDestroyBufferCollectionFUCHSIA(collection->device->handle, collection->handle, collection->allocator);
    gpuDeviceDrop(collection->device);
    delete collection;
}

GPU_API VkBufferCollectionFUCHSIA GPU_CALL gpuBufferCollectionFUCHSIAGetVkHandle(GPUBufferCollectionFUCHSIA collection) {
    return collection != nullptr && !collection->destroyRequested ? collection->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuBufferCollectionFUCHSIAGetDevice(GPUBufferCollectionFUCHSIA collection) {
    return collection != nullptr && !collection->destroyRequested ? collection->device : nullptr;
}

}  // extern "C"

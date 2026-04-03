#include "BufferView.h"

#include <new>

#include "Buffer.h"
#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuBufferViewCreate(
    GPUDevice device,
    const VkBufferViewCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUBufferView* bufferView) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || bufferView == nullptr) {
        gpu::internal::setLastError("Device, create info, and buffer view output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *bufferView = nullptr;

    VkBufferView handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateBufferView(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create buffer view.");
        return result;
    }

    GPUBufferView wrapper = new (std::nothrow) GPUBufferView_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        gpuDestroyBufferView(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate BufferView.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *bufferView = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuBufferViewDestroy(GPUBufferView bufferView) {
    if (bufferView == nullptr) {
        return;
    }

    gpuDestroyBufferView(bufferView->deviceHandle, bufferView->handle, bufferView->allocator);
    delete bufferView;
}

GPU_API VkBufferView GPU_CALL gpuBufferViewGetVkHandle(GPUBufferView bufferView) {
    return bufferView != nullptr ? bufferView->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuBufferViewGetDevice(GPUBufferView bufferView) {
    return bufferView != nullptr ? bufferView->device : nullptr;
}

}  // extern "C"

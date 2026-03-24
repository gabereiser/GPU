#include "Semaphore.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuSemaphoreCreate(
    GPUDevice device,
    const VkSemaphoreCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSemaphore* semaphore) {
    gpu::internal::clearLastError();

    if (device == nullptr || semaphore == nullptr) {
        gpu::internal::setLastError("Device and semaphore output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *semaphore = nullptr;

    VkSemaphoreCreateInfo defaultCreateInfo{};
    defaultCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    const VkSemaphoreCreateInfo* actualCreateInfo = createInfo != nullptr ? createInfo : &defaultCreateInfo;

    VkSemaphore handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateSemaphore(device->handle, actualCreateInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create semaphore.");
        return result;
    }

    GPUSemaphore wrapper = new (std::nothrow) GPUSemaphore_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroySemaphore(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Semaphore.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *semaphore = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuSemaphoreDestroy(GPUSemaphore semaphore) {
    if (semaphore == nullptr) {
        return;
    }

    vkDestroySemaphore(semaphore->deviceHandle, semaphore->handle, semaphore->allocator);
    delete semaphore;
}

GPU_API VkSemaphore GPU_CALL gpuSemaphoreGetVkHandle(GPUSemaphore semaphore) {
    return semaphore != nullptr ? semaphore->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuSemaphoreGetDevice(GPUSemaphore semaphore) {
    return semaphore != nullptr ? semaphore->device : nullptr;
}

}  // extern "C"

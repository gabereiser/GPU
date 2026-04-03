#include "Event.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuEventCreate(
    GPUDevice device,
    const VkEventCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUEvent* event) {
    gpu::internal::clearLastError();

    if (device == nullptr || event == nullptr) {
        gpu::internal::setLastError("Device and event output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *event = nullptr;

    VkEventCreateInfo defaultCreateInfo{};
    defaultCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
    defaultCreateInfo.flags = 0;

    const VkEventCreateInfo* actualCreateInfo = createInfo != nullptr ? createInfo : &defaultCreateInfo;

    VkEvent handle = VK_NULL_HANDLE;
    const VkResult result = gpuCreateEvent(device->handle, actualCreateInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create event.");
        return result;
    }

    GPUEvent wrapper = new (std::nothrow) GPUEvent_T{device, device->handle, handle, allocator};
    if (wrapper == nullptr) {
        gpuDestroyEvent(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Event.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *event = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuEventDestroy(GPUEvent event) {
    if (event == nullptr) {
        return;
    }

    gpuDestroyEvent(event->deviceHandle, event->handle, event->allocator);
    delete event;
}

GPU_API VkEvent GPU_CALL gpuEventGetVkHandle(GPUEvent event) {
    return event != nullptr ? event->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuEventGetDevice(GPUEvent event) {
    return event != nullptr ? event->device : nullptr;
}

}  // extern "C"

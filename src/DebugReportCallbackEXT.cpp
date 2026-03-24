#include "DebugReportCallbackEXT.h"

#include <new>

#include "Instance.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDebugReportCallbackEXTCreate(
    GPUInstance instance,
    const VkDebugReportCallbackCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDebugReportCallbackEXT* callback) {
    gpu::internal::clearLastError();

    if (instance == nullptr || createInfo == nullptr || callback == nullptr) {
        gpu::internal::setLastError("Instance, create info, and callback output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (instance->destroyRequested) {
        gpu::internal::setLastError("Instance is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *callback = nullptr;

    VkDebugReportCallbackEXT handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateDebugReportCallbackEXT(instance->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create debug report callback.");
        return result;
    }

    GPUDebugReportCallbackEXT wrapper =
        new (std::nothrow) GPUDebugReportCallbackEXT_T{instance, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyDebugReportCallbackEXT(instance->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate DebugReportCallbackEXT.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuInstanceRetain(instance);
    *callback = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDebugReportCallbackEXTDestroy(GPUDebugReportCallbackEXT callback) {
    if (callback == nullptr || callback->destroyRequested) {
        return;
    }

    callback->destroyRequested = true;
    vkDestroyDebugReportCallbackEXT(callback->instance->handle, callback->handle, callback->allocator);
    gpuInstanceDrop(callback->instance);
    delete callback;
}

GPU_API VkDebugReportCallbackEXT GPU_CALL gpuDebugReportCallbackEXTGetVkHandle(GPUDebugReportCallbackEXT callback) {
    return callback != nullptr && !callback->destroyRequested ? callback->handle : VK_NULL_HANDLE;
}

GPU_API GPUInstance GPU_CALL gpuDebugReportCallbackEXTGetInstance(GPUDebugReportCallbackEXT callback) {
    return callback != nullptr && !callback->destroyRequested ? callback->instance : nullptr;
}

}  // extern "C"

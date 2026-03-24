#include "DebugUtilsMessengerEXT.h"

#include <new>

#include "Instance.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDebugUtilsMessengerEXTCreate(
    GPUInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDebugUtilsMessengerEXT* messenger) {
    gpu::internal::clearLastError();

    if (instance == nullptr || createInfo == nullptr || messenger == nullptr) {
        gpu::internal::setLastError("Instance, create info, and messenger output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (instance->destroyRequested) {
        gpu::internal::setLastError("Instance is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *messenger = nullptr;

    VkDebugUtilsMessengerEXT handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateDebugUtilsMessengerEXT(instance->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create debug utils messenger.");
        return result;
    }

    GPUDebugUtilsMessengerEXT wrapper =
        new (std::nothrow) GPUDebugUtilsMessengerEXT_T{instance, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyDebugUtilsMessengerEXT(instance->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate DebugUtilsMessengerEXT.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuInstanceRetain(instance);
    *messenger = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDebugUtilsMessengerEXTDestroy(GPUDebugUtilsMessengerEXT messenger) {
    if (messenger == nullptr || messenger->destroyRequested) {
        return;
    }

    messenger->destroyRequested = true;
    vkDestroyDebugUtilsMessengerEXT(messenger->instance->handle, messenger->handle, messenger->allocator);
    gpuInstanceDrop(messenger->instance);
    delete messenger;
}

GPU_API VkDebugUtilsMessengerEXT GPU_CALL gpuDebugUtilsMessengerEXTGetVkHandle(GPUDebugUtilsMessengerEXT messenger) {
    return messenger != nullptr && !messenger->destroyRequested ? messenger->handle : VK_NULL_HANDLE;
}

GPU_API GPUInstance GPU_CALL gpuDebugUtilsMessengerEXTGetInstance(GPUDebugUtilsMessengerEXT messenger) {
    return messenger != nullptr && !messenger->destroyRequested ? messenger->instance : nullptr;
}

}  // extern "C"

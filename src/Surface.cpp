#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Surface.h"

#include <new>

#include "Instance.h"
#include "Internal/Error.h"
#include "Internal/GlfwState.h"

void gpuSurfaceRetain(GPUSurface surface) {
    if (surface != nullptr) {
        ++surface->refCount;
    }
}

void gpuSurfaceDrop(GPUSurface surface) {
    if (surface == nullptr) {
        return;
    }

    if (surface->refCount > 0) {
        --surface->refCount;
    }

    if (surface->refCount == 0) {
        if (surface->handle != VK_NULL_HANDLE) {
            gpuDestroySurfaceKHR(surface->instance->handle, surface->handle, surface->allocator);
        }
        gpuInstanceDrop(surface->instance);
        delete surface;
    }
}

extern "C" {

GPU_API VkResult GPU_CALL gpuSurfaceCreateGlfw(
    GPUInstance instance,
    void* glfwWindow,
    const VkAllocationCallbacks* allocator,
    GPUSurface* surface) {
    gpu::internal::clearLastError();

    if (instance == nullptr || glfwWindow == nullptr || surface == nullptr) {
        gpu::internal::setLastError("Instance, GLFW window, and surface output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (instance->destroyRequested) {
        gpu::internal::setLastError("Instance is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *surface = nullptr;

    if (!gpu::internal::ensureGlfwInitialized()) {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    VkSurfaceKHR handle = VK_NULL_HANDLE;
    const VkResult result = glfwCreateWindowSurface(
        instance->handle,
        static_cast<GLFWwindow*>(glfwWindow),
        allocator,
        &handle);

    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create Vulkan surface from GLFW window.");
        return result;
    }

    GPUSurface wrapper = new (std::nothrow) GPUSurface_T{instance, handle, allocator, 1, false};
    if (wrapper == nullptr) {
        gpuDestroySurfaceKHR(instance->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Surface.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuInstanceRetain(instance);

    *surface = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuSurfaceDestroy(GPUSurface surface) {
    if (surface == nullptr) {
        return;
    }

    if (surface->destroyRequested) {
        return;
    }

    surface->destroyRequested = true;
    gpuSurfaceDrop(surface);
}

GPU_API VkSurfaceKHR GPU_CALL gpuSurfaceGetVkHandle(GPUSurface surface) {
    return surface != nullptr && !surface->destroyRequested ? surface->handle : VK_NULL_HANDLE;
}

GPU_API GPUInstance GPU_CALL gpuSurfaceGetInstance(GPUSurface surface) {
    return surface != nullptr && !surface->destroyRequested ? surface->instance : nullptr;
}

GPU_API VkSurfaceKHR GPU_CALL gpuSurfaceKHRGetVkHandle(GPUSurface surface) {
    return gpuSurfaceGetVkHandle(surface);
}

GPU_API GPUInstance GPU_CALL gpuSurfaceKHRGetInstance(GPUSurface surface) {
    return gpuSurfaceGetInstance(surface);
}

}  // extern "C"

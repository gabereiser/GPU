
#include "Surface.h"

#include <new>

#include "Instance.h"
#include "Internal/Error.h"

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

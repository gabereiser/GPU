#pragma once

#include "gpu/gpu.h"

struct GPUSurface_T {
    GPUInstance instance;
    VkSurfaceKHR handle;
    const VkAllocationCallbacks* allocator;
    uint32_t refCount;
    bool destroyRequested;
};

void gpuSurfaceRetain(GPUSurface surface);
void gpuSurfaceDrop(GPUSurface surface);

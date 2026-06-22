#pragma once

#include "gpu/gpu.h"
#include <atomic>

struct GPUSurface_T
{
    GPUInstance instance;
    VkSurfaceKHR handle;
    const GpuAllocationCallbacks *allocator;
    std::atomic_uint refCount;
    bool destroyRequested;
};

void gpuSurfaceRetain(GPUSurface surface);
void gpuSurfaceDrop(GPUSurface surface);

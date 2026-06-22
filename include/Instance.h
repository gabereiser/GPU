#pragma once

#include "gpu/gpu.h"
#include <atomic>

struct GPUInstance_T
{
    VkInstance handle;
    const GpuAllocationCallbacks *allocator;
    std::atomic_uint refCount;
    bool destroyRequested;
};

void gpuInstanceRetain(GPUInstance instance);
void gpuInstanceDrop(GPUInstance instance);

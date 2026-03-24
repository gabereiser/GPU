#pragma once

#include "gpu/gpu.h"

struct GPUInstance_T {
    VkInstance handle;
    const VkAllocationCallbacks* allocator;
    uint32_t refCount;
    bool destroyRequested;
};

void gpuInstanceRetain(GPUInstance instance);
void gpuInstanceDrop(GPUInstance instance);

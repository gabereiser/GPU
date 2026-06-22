#pragma once

#include "gpu/gpu.h"
#include <atomic>

struct GPUDisplayModeKHR_T {
    GPUDisplayKHR display;
    VkDisplayModeKHR handle;
    std::atomic_uint refCount;
    bool destroyRequested;
};

void gpuDisplayModeKHRRetain(GPUDisplayModeKHR displayMode);
void gpuDisplayModeKHRDrop(GPUDisplayModeKHR displayMode);

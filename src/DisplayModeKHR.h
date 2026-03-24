#pragma once

#include "gpu/gpu.h"

struct GPUDisplayModeKHR_T {
    GPUDisplayKHR display;
    VkDisplayModeKHR handle;
    uint32_t refCount;
    bool destroyRequested;
};

void gpuDisplayModeKHRRetain(GPUDisplayModeKHR displayMode);
void gpuDisplayModeKHRDrop(GPUDisplayModeKHR displayMode);

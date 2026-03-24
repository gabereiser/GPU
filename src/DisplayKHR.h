#pragma once

#include "gpu/gpu.h"

struct GPUDisplayKHR_T {
    GPUPhysicalDevice physicalDevice;
    VkDisplayKHR handle;
    uint32_t refCount;
    bool destroyRequested;
};

void gpuDisplayKHRRetain(GPUDisplayKHR display);
void gpuDisplayKHRDrop(GPUDisplayKHR display);

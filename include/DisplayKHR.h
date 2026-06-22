#pragma once

#include "gpu/gpu.h"
#include <atomic>

struct GPUDisplayKHR_T {
    GPUPhysicalDevice physicalDevice;
    VkDisplayKHR handle;
    std::atomic_uint refCount;
    bool destroyRequested;
};

void gpuDisplayKHRRetain(GPUDisplayKHR display);
void gpuDisplayKHRDrop(GPUDisplayKHR display);

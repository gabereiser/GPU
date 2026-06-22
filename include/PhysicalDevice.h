#pragma once

#include "gpu/gpu.h"
#include <atomic>

struct GPUPhysicalDevice_T {
    GPUInstance instance;
    VkPhysicalDevice handle;
    std::atomic_uint refCount;
    bool destroyRequested;
};

void gpuPhysicalDeviceRetain(GPUPhysicalDevice physicalDevice);
void gpuPhysicalDeviceDrop(GPUPhysicalDevice physicalDevice);

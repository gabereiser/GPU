#pragma once

#include "gpu/gpu.h"

struct GPUPhysicalDevice_T {
    GPUInstance instance;
    VkPhysicalDevice handle;
    uint32_t refCount;
    bool destroyRequested;
};

void gpuPhysicalDeviceRetain(GPUPhysicalDevice physicalDevice);
void gpuPhysicalDeviceDrop(GPUPhysicalDevice physicalDevice);

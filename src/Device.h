#pragma once

#include "gpu/gpu.h"

struct GPUDevice_T {
    GPUPhysicalDevice physicalDevice;
    VkDevice handle;
    const VkAllocationCallbacks* allocator;
    uint32_t refCount;
    bool destroyRequested;
};

void gpuDeviceRetain(GPUDevice device);
void gpuDeviceDrop(GPUDevice device);

#pragma once

#include "gpu/gpu.h"
#include <atomic>

struct GPUDevice_T
{
    GPUPhysicalDevice physicalDevice;
    VkDevice handle;
    const GpuAllocationCallbacks *allocator;
    std::atomic_uint refCount;
    bool destroyRequested;
};

void gpuDeviceRetain(GPUDevice device);
void gpuDeviceDrop(GPUDevice device);

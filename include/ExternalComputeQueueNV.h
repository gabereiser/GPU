#pragma once

#include "gpu/gpu.h"

struct GPUExternalComputeQueueNV_T
{
    GPUDevice device;
    VkExternalComputeQueueNV handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

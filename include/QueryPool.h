#pragma once

#include "gpu/gpu.h"

struct GPUQueryPool_T
{
    GPUDevice device;
    VkQueryPool handle;
    const GpuAllocationCallbacks *allocator;
};

#pragma once

#include "gpu/gpu.h"

struct GPUBuffer_T
{
    GPUDevice device;
    VkBuffer handle;
    const GpuAllocationCallbacks *allocator;
};

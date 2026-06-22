#pragma once

#include "gpu/gpu.h"

struct GPUCommandPool_T
{
    GPUDevice device;
    VkCommandPool handle;
    const GpuAllocationCallbacks *allocator;
    GPUCommandBuffer firstCommandBuffer;
};

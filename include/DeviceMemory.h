#pragma once

#include "gpu/gpu.h"

struct GPUDeviceMemory_T
{
    GPUDevice device;
    VkDeviceMemory handle;
    const GpuAllocationCallbacks *allocator;
};

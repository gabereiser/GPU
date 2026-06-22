#pragma once

#include "gpu/gpu.h"

struct GPUImage_T
{
    GPUDevice device;
    VkImage handle;
    const GpuAllocationCallbacks *allocator;
};

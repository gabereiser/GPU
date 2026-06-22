#pragma once

#include "gpu/gpu.h"

struct GPUImageView_T
{
    GPUDevice device;
    VkImageView handle;
    const GpuAllocationCallbacks *allocator;
};

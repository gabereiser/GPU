#pragma once

#include "gpu/gpu.h"

struct GPUSemaphore_T
{
    GPUDevice device;
    VkSemaphore handle;
    const GpuAllocationCallbacks *allocator;
};

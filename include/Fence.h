#pragma once

#include "gpu/gpu.h"

struct GPUFence_T
{
    GPUDevice device;
    VkFence handle;
    const GpuAllocationCallbacks *allocator;
};

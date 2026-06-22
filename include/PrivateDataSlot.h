#pragma once

#include "gpu/gpu.h"

struct GPUPrivateDataSlot_T
{
    GPUDevice device;
    VkPrivateDataSlot handle;
    const GpuAllocationCallbacks *allocator;
};

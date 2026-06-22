#pragma once

#include "gpu/gpu.h"

struct GPUEvent_T
{
    GPUDevice device;
    VkEvent handle;
    const GpuAllocationCallbacks *allocator;
};

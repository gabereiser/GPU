#pragma once

#include "gpu/gpu.h"

struct GPUBufferView_T
{
    GPUDevice device;
    VkBufferView handle;
    const GpuAllocationCallbacks *allocator;
};

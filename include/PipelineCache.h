#pragma once

#include "gpu/gpu.h"

struct GPUPipelineCache_T
{
    GPUDevice device;
    VkPipelineCache handle;
    const GpuAllocationCallbacks *allocator;
};

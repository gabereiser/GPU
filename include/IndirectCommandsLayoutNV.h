#pragma once

#include "gpu/gpu.h"

struct GPUIndirectCommandsLayoutNV_T
{
    GPUDevice device;
    VkIndirectCommandsLayoutNV handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

#pragma once

#include "gpu/gpu.h"

struct GPUCuModuleNVX_T
{
    GPUDevice device;
    VkCuModuleNVX handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

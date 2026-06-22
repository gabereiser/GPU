#pragma once

#include "gpu/gpu.h"

struct GPUOpticalFlowSessionNV_T
{
    GPUDevice device;
    VkOpticalFlowSessionNV handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

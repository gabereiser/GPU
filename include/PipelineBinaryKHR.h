#pragma once

#include "gpu/gpu.h"

struct GPUPipelineBinaryKHR_T
{
    GPUDevice device;
    VkPipelineBinaryKHR handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

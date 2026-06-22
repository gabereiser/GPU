#pragma once

#include "gpu/gpu.h"

struct GPUIndirectExecutionSetEXT_T
{
    GPUDevice device;
    VkIndirectExecutionSetEXT handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

#pragma once

#include "gpu/gpu.h"

struct GPUValidationCacheEXT_T
{
    GPUDevice device;
    VkValidationCacheEXT handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

#pragma once

#include "gpu/gpu.h"

struct GPUMicromapEXT_T
{
    GPUDevice device;
    VkMicromapEXT handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

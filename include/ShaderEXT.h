#pragma once

#include "gpu/gpu.h"

struct GPUShaderEXT_T
{
    GPUDevice device;
    VkShaderEXT handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

#pragma once

#include "gpu/gpu.h"

struct GPUAccelerationStructureKHR_T
{
    GPUDevice device;
    VkAccelerationStructureKHR handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

#pragma once

#include "gpu/gpu.h"

struct GPUDeferredOperationKHR_T
{
    GPUDevice device;
    VkDeferredOperationKHR handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};

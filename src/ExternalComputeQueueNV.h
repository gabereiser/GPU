#pragma once

#include "gpu/gpu.h"

struct GPUExternalComputeQueueNV_T {
    GPUDevice device;
    VkExternalComputeQueueNV handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

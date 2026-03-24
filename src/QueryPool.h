#pragma once

#include "gpu/gpu.h"

struct GPUQueryPool_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkQueryPool handle;
    const VkAllocationCallbacks* allocator;
};

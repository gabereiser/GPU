#pragma once

#include "gpu/gpu.h"

struct GPUBuffer_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkBuffer handle;
    const VkAllocationCallbacks* allocator;
};

#pragma once

#include "gpu/gpu.h"

struct GPUCommandPool_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkCommandPool handle;
    const VkAllocationCallbacks* allocator;
    GPUCommandBuffer firstCommandBuffer;
};

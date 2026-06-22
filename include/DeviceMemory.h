#pragma once

#include "gpu/gpu.h"

struct GPUDeviceMemory_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkDeviceMemory handle;
    const VkAllocationCallbacks* allocator;
};

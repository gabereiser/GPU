#pragma once

#include "gpu/gpu.h"

struct GPUSemaphore_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkSemaphore handle;
    const VkAllocationCallbacks* allocator;
};

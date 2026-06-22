#pragma once

#include "gpu/gpu.h"

struct GPUImage_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkImage handle;
    const VkAllocationCallbacks* allocator;
};

#pragma once

#include "gpu/gpu.h"

struct GPUImageView_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkImageView handle;
    const VkAllocationCallbacks* allocator;
};

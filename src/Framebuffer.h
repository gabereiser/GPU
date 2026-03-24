#pragma once

#include "gpu/gpu.h"

struct GPUFramebuffer_T {
    GPUDevice device;
    VkFramebuffer handle;
    const VkAllocationCallbacks* allocator;
};

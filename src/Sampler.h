#pragma once

#include "gpu/gpu.h"

struct GPUSampler_T {
    GPUDevice device;
    VkSampler handle;
    const VkAllocationCallbacks* allocator;
};

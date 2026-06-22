#pragma once

#include "gpu/gpu.h"

struct GPUDescriptorPool_T {
    GPUDevice device;
    VkDescriptorPool handle;
    const VkAllocationCallbacks* allocator;
};

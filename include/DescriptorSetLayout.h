#pragma once

#include "gpu/gpu.h"

struct GPUDescriptorSetLayout_T {
    GPUDevice device;
    VkDescriptorSetLayout handle;
    const VkAllocationCallbacks* allocator;
};

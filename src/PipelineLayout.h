#pragma once

#include "gpu/gpu.h"

struct GPUPipelineLayout_T {
    GPUDevice device;
    VkPipelineLayout handle;
    const VkAllocationCallbacks* allocator;
};

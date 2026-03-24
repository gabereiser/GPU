#pragma once

#include "gpu/gpu.h"

struct GPUPipeline_T {
    GPUDevice device;
    VkPipeline handle;
    const VkAllocationCallbacks* allocator;
};

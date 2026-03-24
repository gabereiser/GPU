#pragma once

#include "gpu/gpu.h"

struct GPURenderPass_T {
    GPUDevice device;
    VkRenderPass handle;
    const VkAllocationCallbacks* allocator;
};

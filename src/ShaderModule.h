#pragma once

#include "gpu/gpu.h"

struct GPUShaderModule_T {
    GPUDevice device;
    VkShaderModule handle;
    const VkAllocationCallbacks* allocator;
};

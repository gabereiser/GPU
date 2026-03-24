#pragma once

#include "gpu/gpu.h"

struct GPUCuFunctionNVX_T {
    GPUDevice device;
    VkCuFunctionNVX handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

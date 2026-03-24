#pragma once

#include "gpu/gpu.h"

struct GPUCudaFunctionNV_T {
    GPUDevice device;
    VkCudaFunctionNV handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

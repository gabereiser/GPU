#pragma once

#include "gpu/gpu.h"

struct GPUCuModuleNVX_T {
    GPUDevice device;
    VkCuModuleNVX handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

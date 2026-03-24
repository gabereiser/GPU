#pragma once

#include "gpu/gpu.h"

struct GPUOpticalFlowSessionNV_T {
    GPUDevice device;
    VkOpticalFlowSessionNV handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

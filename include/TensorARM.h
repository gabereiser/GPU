#pragma once

#include "gpu/gpu.h"

struct GPUTensorARM_T {
    GPUDevice device;
    VkTensorARM handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

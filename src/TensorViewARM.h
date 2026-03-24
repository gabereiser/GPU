#pragma once

#include "gpu/gpu.h"

struct GPUTensorViewARM_T {
    GPUDevice device;
    VkTensorViewARM handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

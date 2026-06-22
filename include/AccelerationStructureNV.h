#pragma once

#include "gpu/gpu.h"

struct GPUAccelerationStructureNV_T {
    GPUDevice device;
    VkAccelerationStructureNV handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

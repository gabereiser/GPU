#pragma once

#include "gpu/gpu.h"

struct GPUAccelerationStructureKHR_T {
    GPUDevice device;
    VkAccelerationStructureKHR handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

#pragma once

#include "gpu/gpu.h"

struct GPUVideoSessionKHR_T {
    GPUDevice device;
    VkVideoSessionKHR handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

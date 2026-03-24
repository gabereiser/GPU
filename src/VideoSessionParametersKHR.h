#pragma once

#include "gpu/gpu.h"

struct GPUVideoSessionParametersKHR_T {
    GPUDevice device;
    VkVideoSessionParametersKHR handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

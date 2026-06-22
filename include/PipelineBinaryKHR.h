#pragma once

#include "gpu/gpu.h"

struct GPUPipelineBinaryKHR_T {
    GPUDevice device;
    VkPipelineBinaryKHR handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

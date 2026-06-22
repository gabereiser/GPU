#pragma once

#include "gpu/gpu.h"

struct GPUDeferredOperationKHR_T {
    GPUDevice device;
    VkDeferredOperationKHR handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

#pragma once

#include "gpu/gpu.h"

struct GPUEvent_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkEvent handle;
    const VkAllocationCallbacks* allocator;
};

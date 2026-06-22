#pragma once

#include "gpu/gpu.h"

struct GPUBufferView_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkBufferView handle;
    const VkAllocationCallbacks* allocator;
};

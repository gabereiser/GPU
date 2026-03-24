#pragma once

#include "gpu/gpu.h"

struct GPUFence_T {
    GPUDevice device;
    VkDevice deviceHandle;
    VkFence handle;
    const VkAllocationCallbacks* allocator;
};

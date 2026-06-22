#pragma once

#include "gpu/gpu.h"

struct GPUMicromapEXT_T {
    GPUDevice device;
    VkMicromapEXT handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

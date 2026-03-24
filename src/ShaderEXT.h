#pragma once

#include "gpu/gpu.h"

struct GPUShaderEXT_T {
    GPUDevice device;
    VkShaderEXT handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

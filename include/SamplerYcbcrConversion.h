#pragma once

#include "gpu/gpu.h"

struct GPUSamplerYcbcrConversion_T {
    GPUDevice device;
    VkSamplerYcbcrConversion handle;
    const VkAllocationCallbacks* allocator;
};

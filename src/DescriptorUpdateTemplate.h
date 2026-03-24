#pragma once

#include "gpu/gpu.h"

struct GPUDescriptorUpdateTemplate_T {
    GPUDevice device;
    VkDescriptorUpdateTemplate handle;
    const VkAllocationCallbacks* allocator;
};

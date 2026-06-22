#pragma once

#include "gpu/gpu.h"

struct GPUIndirectCommandsLayoutEXT_T {
    GPUDevice device;
    VkIndirectCommandsLayoutEXT handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

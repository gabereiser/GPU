#pragma once

#include "gpu/gpu.h"

struct GPUBufferCollectionFUCHSIA_T {
    GPUDevice device;
    VkBufferCollectionFUCHSIA handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

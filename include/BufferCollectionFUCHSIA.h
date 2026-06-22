#pragma once

#include "gpu/gpu.h"
#if defined(VK_USE_PLATFORM_FUCHSIA)
struct GPUBufferCollectionFUCHSIA_T
{
    GPUDevice device;
    VkBufferCollectionFUCHSIA handle;
    const VkAllocationCallbacks *allocator;
    bool destroyRequested;
};
#endif

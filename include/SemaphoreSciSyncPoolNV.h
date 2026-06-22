#pragma once
#if defined(VK_ENABLE_SCISYNC)
#include "gpu/gpu.h"

struct GPUSemaphoreSciSyncPoolNV_T
{
    GPUDevice device;
    VkSemaphoreSciSyncPoolNV handle;
    const VkAllocationCallbacks *allocator;
    bool destroyRequested;
};
#endif
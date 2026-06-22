#pragma once
#if defined(VK_ENABLE_SCISYNC)
#include "gpu/gpu.h"

struct GPUSemaphoreSciSyncPoolNV_T
{
    GPUDevice device;
    VkSemaphoreSciSyncPoolNV handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};
#endif
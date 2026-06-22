#pragma once
#if defined(VK_CUDA_MODULE)
#include "gpu/gpu.h"

struct GPUCudaModuleNV_T
{
    GPUDevice device;
    VkCudaModuleNV handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};
#endif
#pragma once
#if defined(VK_CUDA_MODULE)
#include "gpu/gpu.h"

struct GPUCudaFunctionNV_T
{
    GPUDevice device;
    VkCudaFunctionNV handle;
    const VkAllocationCallbacks *allocator;
    bool destroyRequested;
};
#endif
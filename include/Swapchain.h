#pragma once

#include "gpu/gpu.h"
#include <atomic>

struct GPUSwapchain_T
{
    GPUDevice device;
    GPUSurface surface;
    VkSwapchainKHR handle;
    const GpuAllocationCallbacks *allocator;
    std::atomic_uint refCount;
    bool destroyRequested;
};

void gpuSwapchainRetain(GPUSwapchain swapchain);
void gpuSwapchainDrop(GPUSwapchain swapchain);

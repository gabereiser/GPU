#pragma once

#include "gpu/gpu.h"

struct GPUSwapchain_T {
    GPUDevice device;
    GPUSurface surface;
    VkSwapchainKHR handle;
    const VkAllocationCallbacks* allocator;
    uint32_t refCount;
    bool destroyRequested;
};

void gpuSwapchainRetain(GPUSwapchain swapchain);
void gpuSwapchainDrop(GPUSwapchain swapchain);

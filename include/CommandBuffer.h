#pragma once

#include "gpu/gpu.h"

struct GPUCommandBuffer_T
{
    GPUCommandPool commandPool;
    GPUDevice deviceHandle;
    VkCommandPool commandPoolHandle;
    VkCommandBuffer handle;
    GpuCommandBufferLevel level;
    GPUCommandBuffer next;
    GPUCommandBuffer previous;
};

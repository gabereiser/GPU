#pragma once

#include "gpu/gpu.h"

struct GPUCommandBuffer_T {
    GPUCommandPool commandPool;
    VkDevice deviceHandle;
    VkCommandPool commandPoolHandle;
    VkCommandBuffer handle;
    VkCommandBufferLevel level;
    GPUCommandBuffer next;
    GPUCommandBuffer previous;
};

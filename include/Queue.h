#pragma once

#include "gpu/gpu.h"
#include <atomic>

struct GPUQueue_T {
    GPUDevice device;
    VkQueue handle;
    uint32_t familyIndex;
    uint32_t queueIndex;
    std::atomic_uint refCount;
    bool destroyRequested;
};

void gpuQueueRetain(GPUQueue queue);
void gpuQueueDrop(GPUQueue queue);

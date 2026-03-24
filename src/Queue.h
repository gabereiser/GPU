#pragma once

#include "gpu/gpu.h"

struct GPUQueue_T {
    GPUDevice device;
    VkQueue handle;
    uint32_t familyIndex;
    uint32_t queueIndex;
    uint32_t refCount;
    bool destroyRequested;
};

void gpuQueueRetain(GPUQueue queue);
void gpuQueueDrop(GPUQueue queue);

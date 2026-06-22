#pragma once

#include "gpu/gpu.h"

struct GPUDataGraphPipelineSessionARM_T {
    GPUDevice device;
    VkDataGraphPipelineSessionARM handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

#pragma once
#ifndef NDEBUG
#include "gpu/gpu.h"

struct GPUDebugReportCallbackEXT_T
{
    GPUInstance instance;
    VkDebugReportCallbackEXT handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};
#endif

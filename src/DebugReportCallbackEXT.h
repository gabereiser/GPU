#pragma once

#include "gpu/gpu.h"

struct GPUDebugReportCallbackEXT_T {
    GPUInstance instance;
    VkDebugReportCallbackEXT handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

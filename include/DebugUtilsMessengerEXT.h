#ifndef NDEBUG
#pragma once

#include "gpu/gpu.h"

struct GPUDebugUtilsMessengerEXT_T
{
    GPUInstance instance;
    VkDebugUtilsMessengerEXT handle;
    const GpuAllocationCallbacks *allocator;
    bool destroyRequested;
};
#endif

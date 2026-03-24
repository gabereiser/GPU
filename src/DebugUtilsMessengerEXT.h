#pragma once

#include "gpu/gpu.h"

struct GPUDebugUtilsMessengerEXT_T {
    GPUInstance instance;
    VkDebugUtilsMessengerEXT handle;
    const VkAllocationCallbacks* allocator;
    bool destroyRequested;
};

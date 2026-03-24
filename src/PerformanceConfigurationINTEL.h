#pragma once

#include "gpu/gpu.h"

struct GPUPerformanceConfigurationINTEL_T {
    GPUDevice device;
    VkPerformanceConfigurationINTEL handle;
    bool destroyRequested;
};

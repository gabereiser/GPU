#pragma once

#include "gpu/gpu.h"

struct GPUDescriptorSet_T {
    GPUDescriptorPool pool;
    VkDescriptorSet handle;
};

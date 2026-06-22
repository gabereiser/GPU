#include <iostream>
#include <vector>
#include <cstring>

#include <vulkan/vulkan.h>

#include "gpu/gpu.h"

int main() {
    const char* glslSource = "#version 460\nvoid main() {}";
    void* spirv = nullptr;
    size_t size = 0;
    bool ok = gpuCompileShader(GPU_SHADER_LANGUAGE_GLSL,
                               VK_SHADER_STAGE_VERTEX_BIT,
                               glslSource,
                               std::strlen(glslSource),
                               &spirv,
                               &size);
    std::cout << "GPU compile result: " << (ok ? "success" : "failure") << ", size=" << size << "\n";
    if (ok) gpuFreeShaderBinary(spirv);


    return 0;
}

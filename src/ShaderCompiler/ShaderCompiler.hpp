#pragma once

#include <gpu/gpu.h>
#include <string>
#include <vector>

#ifdef _WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <windows.h>
#endif

// Shader compiler interface
class IShaderCompiler {
public:
    virtual ~IShaderCompiler() = default;
    virtual bool compile(const char* source, size_t length, std::vector<uint32_t>& spirv, std::string& error) = 0;
};

#ifdef GPU_USE_GLSLANG
class GlslangCompiler : public IShaderCompiler {
public:
    bool compile(const char* source, size_t length, std::vector<uint32_t>& spirv, std::string& error) override;
};
#endif

#ifdef GPU_USE_DXC
class DxcCompiler : public IShaderCompiler {
public:
    bool compile(const char* source, size_t length, std::vector<uint32_t>& spirv, std::string& error) override;
};
#endif

// Global shader compiler factory
bool gpuCreateCompiler(GPUShaderLanguage lang, IShaderCompiler** outCompiler);
void gpuDestroyCompiler(IShaderCompiler* compiler);

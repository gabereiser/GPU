#include "ShaderCompiler.hpp"
#include <gpu/gpu.h>
#include <cstring>
#include <cstdlib>

#include <glslang/Public/ShaderLang.h>
#include <SPIRV/GlslangToSpv.h>
#include <glslang/Public/ResourceLimits.h>

extern "C" {

static EShLanguage stageToGlslang(VkShaderStageFlagBits stage) {
    switch (stage) {
        case VK_SHADER_STAGE_VERTEX_BIT: return EShLangVertex;
        case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT: return EShLangTessControl;
        case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT: return EShLangTessEvaluation;
        case VK_SHADER_STAGE_GEOMETRY_BIT: return EShLangGeometry;
        case VK_SHADER_STAGE_FRAGMENT_BIT: return EShLangFragment;
        case VK_SHADER_STAGE_COMPUTE_BIT: return EShLangCompute;
        case VK_SHADER_STAGE_RAYGEN_BIT_KHR: return EShLangRayGen;
        case VK_SHADER_STAGE_ANY_HIT_BIT_KHR: return EShLangAnyHit;
        case VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR: return EShLangClosestHit;
        case VK_SHADER_STAGE_MISS_BIT_KHR: return EShLangMiss;
        case VK_SHADER_STAGE_INTERSECTION_BIT_KHR: return EShLangIntersect;
        case VK_SHADER_STAGE_CALLABLE_BIT_KHR: return EShLangCallable;
        default: return EShLanguage::EShLangCount;
    }
}

static bool compileShader(const std::string& source, VkShaderStageFlagBits stage, GPUShaderLanguage language, void** outSpirv, size_t* outSize) {
    EShLanguage lang = stageToGlslang(stage);
    if (lang == EShLanguage::EShLangCount) {
        return false;
    }

    glslang::InitializeProcess();

    const char* shaderStrings = source.c_str();
    glslang::TShader shader(lang);
    shader.setStringsWithLengths(&shaderStrings, nullptr, 1);

    // Set source language and target environment for Vulkan SPIR-V
    glslang::EShSource srcLang = (language == GPU_SHADER_LANGUAGE_GLSL) ? glslang::EShSourceGlsl : glslang::EShSourceHlsl;
    shader.setEnvInput(srcLang, lang, glslang::EShClientVulkan, 100);
    shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_3);
    shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_3);

    EShMessages messages = static_cast<EShMessages>(EShMsgVulkanRules | EShMsgDefault);

    if (!shader.parse(GetResources(), 100, false, messages)) {
        glslang::FinalizeProcess();
        return false;
    }

    glslang::TProgram program;
    program.addShader(&shader);

    if (!program.link(messages)) {
        glslang::FinalizeProcess();
        return false;
    }

    glslang::SpvOptions spvOptions;
    spvOptions.generateDebugInfo = false;
    spvOptions.disableOptimizer = false;
    spvOptions.optimizeSize = false;

    std::vector<uint32_t> spirv;
    glslang::GlslangToSpv(*program.getIntermediate(lang), spirv, &spvOptions);

    glslang::FinalizeProcess();

    if (spirv.empty()) {
        return false;
    }

    *outSize = spirv.size() * sizeof(uint32_t);
    *outSpirv = malloc(*outSize);
    if (!*outSpirv) {
        return false;
    }
    memcpy(*outSpirv, spirv.data(), *outSize);
    return true;
}

bool GPU_CALL gpuCompileShader(GPUShaderLanguage language, VkShaderStageFlagBits stage, const char* source, size_t sourceLen, void** outSpirv, size_t* outSize) {
    if (!source || sourceLen == 0 || !outSpirv || !outSize) {
        return false;
    }

    std::string src(source, sourceLen);
    return compileShader(src, stage, language, outSpirv, outSize);
}

void GPU_CALL gpuFreeShaderBinary(void* spirv) {
    if (spirv) {
        free(spirv);
    }
}

} // extern "C"

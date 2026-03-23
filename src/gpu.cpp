#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "gpu/gpu.h"

#include <vulkan/vulkan.h>

namespace {

thread_local const char* g_lastError = nullptr;
bool g_glfwInitialized = false;

void setLastError(const char* message) {
    g_lastError = message;
}

}  // namespace

extern "C" {

uint32_t GPU_CALL gpuGetApiVersion(void) {
    setLastError(nullptr);
    return VK_API_VERSION_1_0;
}

GPUFunction GPU_CALL gpuGetInstanceProcAddr(GPUHandle instance, const char* name) {
    setLastError(nullptr);

    if (name == nullptr) {
        setLastError("Function name must not be null.");
        return nullptr;
    }

    return reinterpret_cast<GPUFunction>(
        vkGetInstanceProcAddr(reinterpret_cast<VkInstance>(instance), name));
}

const char* GPU_CALL gpuGetLastError(void) {
    return g_lastError;
}

int32_t GPU_CALL gpuGetRequiredInstanceExtensions(const char*** extensions, uint32_t* count) {
    setLastError(nullptr);

    if (extensions == nullptr || count == nullptr) {
        setLastError("Extensions and count outputs must not be null.");
        return GLFW_FALSE;
    }

    if (!g_glfwInitialized) {
        if (glfwInit() == GLFW_FALSE) {
            setLastError("Failed to initialize GLFW.");
            *extensions = nullptr;
            *count = 0;
            return GLFW_FALSE;
        }

        g_glfwInitialized = true;
    }

    const char** requiredExtensions = glfwGetRequiredInstanceExtensions(count);
    if (requiredExtensions == nullptr || *count == 0) {
        setLastError("Failed to query GLFW Vulkan instance extensions.");
        *extensions = nullptr;
        *count = 0;
        return GLFW_FALSE;
    }

    *extensions = requiredExtensions;
    return GLFW_TRUE;
}

}  // extern "C"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "gpu/gpu.h"

#include "Internal/Error.h"
#include "Internal/GlfwState.h"

extern "C" {

GPU_API uint32_t GPU_CALL gpuGetApiVersion(void) {
    gpu::internal::clearLastError();
    return VK_HEADER_VERSION_COMPLETE;
}

GPU_API const char* GPU_CALL gpuGetLastError(void) {
    return gpu::internal::getLastError();
}

GPU_API int32_t GPU_CALL gpuGetRequiredInstanceExtensions(const char*** extensions, uint32_t* count) {
    gpu::internal::clearLastError();

    if (extensions == nullptr || count == nullptr) {
        gpu::internal::setLastError("Extensions and count outputs must not be null.");
        return GLFW_FALSE;
    }

    if (!gpu::internal::ensureGlfwInitialized()) {
        *extensions = nullptr;
        *count = 0;
        return GLFW_FALSE;
    }

    const char** requiredExtensions = glfwGetRequiredInstanceExtensions(count);
    if (requiredExtensions == nullptr || *count == 0) {
        gpu::internal::setLastError("Failed to query GLFW Vulkan instance extensions.");
        *extensions = nullptr;
        *count = 0;
        return GLFW_FALSE;
    }

    *extensions = requiredExtensions;
    return GLFW_TRUE;
}

GPU_API int32_t GPU_CALL gpuGetFramebufferSizeGlfw(void* glfwWindow, uint32_t* width, uint32_t* height) {
    gpu::internal::clearLastError();

    if (glfwWindow == nullptr || width == nullptr || height == nullptr) {
        gpu::internal::setLastError("GLFW window, width, and height outputs must not be null.");
        return GLFW_FALSE;
    }

    int framebufferWidth = 0;
    int framebufferHeight = 0;
    glfwGetFramebufferSize(static_cast<GLFWwindow*>(glfwWindow), &framebufferWidth, &framebufferHeight);

    *width = static_cast<uint32_t>(framebufferWidth);
    *height = static_cast<uint32_t>(framebufferHeight);
    return GLFW_TRUE;
}

}  // extern "C"

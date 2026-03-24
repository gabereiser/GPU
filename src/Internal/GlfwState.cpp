#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Internal/Error.h"
#include "Internal/GlfwState.h"

namespace {

bool g_glfwInitialized = false;

}

namespace gpu::internal {

bool ensureGlfwInitialized() {
    if (g_glfwInitialized) {
        return true;
    }

    if (glfwInit() == GLFW_FALSE) {
        setLastError("Failed to initialize GLFW.");
        return false;
    }

    g_glfwInitialized = true;
    return true;
}

}  // namespace gpu::internal

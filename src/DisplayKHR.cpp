#include "DisplayKHR.h"

#include <new>
#include <vector>

#include "DisplayModeKHR.h"
#include "PhysicalDevice.h"
#include "Internal/Error.h"

void gpuDisplayKHRRetain(GPUDisplayKHR display) {
    if (display != nullptr) {
        ++display->refCount;
    }
}

void gpuDisplayKHRDrop(GPUDisplayKHR display) {
    if (display == nullptr) {
        return;
    }

    if (display->refCount > 0) {
        --display->refCount;
    }

    if (display->refCount == 0) {
        gpuPhysicalDeviceDrop(display->physicalDevice);
        delete display;
    }
}

extern "C" {

GPU_API uint32_t GPU_CALL gpuPhysicalDeviceGetDisplayCountKHR(GPUPhysicalDevice physicalDevice) {
    gpu::internal::clearLastError();

    if (physicalDevice == nullptr || physicalDevice->destroyRequested) {
        gpu::internal::setLastError("Physical device must not be null or released.");
        return 0;
    }

    uint32_t count = 0;
    const VkResult result = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice->handle, &count, nullptr);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to get display count.");
        return 0;
    }

    return count;
}

GPU_API VkResult GPU_CALL gpuPhysicalDeviceGetDisplayKHR(
    GPUPhysicalDevice physicalDevice,
    uint32_t index,
    GPUDisplayKHR* display) {
    gpu::internal::clearLastError();

    if (physicalDevice == nullptr || display == nullptr) {
        gpu::internal::setLastError("Physical device and display output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (physicalDevice->destroyRequested) {
        gpu::internal::setLastError("Physical device is being released.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *display = nullptr;

    uint32_t count = 0;
    VkResult result = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice->handle, &count, nullptr);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to get display count.");
        return result;
    }

    if (index >= count) {
        gpu::internal::setLastError("Display index is out of range.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    std::vector<VkDisplayPropertiesKHR> properties(count);
    result = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice->handle, &count, properties.data());
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to enumerate displays.");
        return result;
    }

    GPUDisplayKHR wrapper = new (std::nothrow) GPUDisplayKHR_T{physicalDevice, properties[index].display, 1, false};
    if (wrapper == nullptr) {
        gpu::internal::setLastError("Failed to allocate DisplayKHR.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuPhysicalDeviceRetain(physicalDevice);
    *display = wrapper;
    return VK_SUCCESS;
}

GPU_API VkDisplayKHR GPU_CALL gpuDisplayKHRGetVkHandle(GPUDisplayKHR display) {
    return display != nullptr && !display->destroyRequested ? display->handle : VK_NULL_HANDLE;
}

GPU_API GPUPhysicalDevice GPU_CALL gpuDisplayKHRGetPhysicalDevice(GPUDisplayKHR display) {
    return display != nullptr && !display->destroyRequested ? display->physicalDevice : nullptr;
}

GPU_API uint32_t GPU_CALL gpuDisplayKHRGetModeCountKHR(GPUDisplayKHR display) {
    gpu::internal::clearLastError();

    if (display == nullptr || display->destroyRequested) {
        gpu::internal::setLastError("Display must not be null or released.");
        return 0;
    }

    uint32_t count = 0;
    const VkResult result =
        vkGetDisplayModePropertiesKHR(display->physicalDevice->handle, display->handle, &count, nullptr);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to get display mode count.");
        return 0;
    }

    return count;
}

GPU_API VkResult GPU_CALL gpuDisplayKHRGetModeKHR(
    GPUDisplayKHR display,
    uint32_t index,
    GPUDisplayModeKHR* displayMode) {
    gpu::internal::clearLastError();

    if (display == nullptr || displayMode == nullptr) {
        gpu::internal::setLastError("Display and display mode output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (display->destroyRequested) {
        gpu::internal::setLastError("Display is being released.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *displayMode = nullptr;

    uint32_t count = 0;
    VkResult result =
        vkGetDisplayModePropertiesKHR(display->physicalDevice->handle, display->handle, &count, nullptr);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to get display mode count.");
        return result;
    }

    if (index >= count) {
        gpu::internal::setLastError("Display mode index is out of range.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    std::vector<VkDisplayModePropertiesKHR> properties(count);
    result = vkGetDisplayModePropertiesKHR(
        display->physicalDevice->handle,
        display->handle,
        &count,
        properties.data());
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to enumerate display modes.");
        return result;
    }

    GPUDisplayModeKHR wrapper =
        new (std::nothrow) GPUDisplayModeKHR_T{display, properties[index].displayMode, 1, false};
    if (wrapper == nullptr) {
        gpu::internal::setLastError("Failed to allocate DisplayModeKHR.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDisplayKHRRetain(display);
    *displayMode = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDisplayKHRRelease(GPUDisplayKHR display) {
    if (display == nullptr || display->destroyRequested) {
        return;
    }

    display->destroyRequested = true;
    gpuDisplayKHRDrop(display);
}

}  // extern "C"

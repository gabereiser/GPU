#include "DisplayModeKHR.h"

#include "DisplayKHR.h"

void gpuDisplayModeKHRRetain(GPUDisplayModeKHR displayMode) {
    if (displayMode != nullptr) {
        ++displayMode->refCount;
    }
}

void gpuDisplayModeKHRDrop(GPUDisplayModeKHR displayMode) {
    if (displayMode == nullptr) {
        return;
    }

    if (displayMode->refCount > 0) {
        --displayMode->refCount;
    }

    if (displayMode->refCount == 0) {
        gpuDisplayKHRDrop(displayMode->display);
        delete displayMode;
    }
}

extern "C" {

GPU_API VkDisplayModeKHR GPU_CALL gpuDisplayModeKHRGetVkHandle(GPUDisplayModeKHR displayMode) {
    return displayMode != nullptr && !displayMode->destroyRequested ? displayMode->handle : VK_NULL_HANDLE;
}

GPU_API GPUDisplayKHR GPU_CALL gpuDisplayModeKHRGetDisplayKHR(GPUDisplayModeKHR displayMode) {
    return displayMode != nullptr && !displayMode->destroyRequested ? displayMode->display : nullptr;
}

GPU_API GPUPhysicalDevice GPU_CALL gpuDisplayModeKHRGetPhysicalDevice(GPUDisplayModeKHR displayMode) {
    return displayMode != nullptr && !displayMode->destroyRequested
        ? gpuDisplayKHRGetPhysicalDevice(displayMode->display)
        : nullptr;
}

GPU_API void GPU_CALL gpuDisplayModeKHRRelease(GPUDisplayModeKHR displayMode) {
    if (displayMode == nullptr || displayMode->destroyRequested) {
        return;
    }

    displayMode->destroyRequested = true;
    gpuDisplayModeKHRDrop(displayMode);
}

}  // extern "C"

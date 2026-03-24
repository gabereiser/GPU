#include "PhysicalDevice.h"

#include "Instance.h"

void gpuPhysicalDeviceRetain(GPUPhysicalDevice physicalDevice) {
    if (physicalDevice != nullptr) {
        ++physicalDevice->refCount;
    }
}

void gpuPhysicalDeviceDrop(GPUPhysicalDevice physicalDevice) {
    if (physicalDevice == nullptr) {
        return;
    }

    if (physicalDevice->refCount > 0) {
        --physicalDevice->refCount;
    }

    if (physicalDevice->refCount == 0) {
        gpuInstanceDrop(physicalDevice->instance);
        delete physicalDevice;
    }
}

extern "C" {

GPU_API VkPhysicalDevice GPU_CALL gpuPhysicalDeviceGetVkHandle(GPUPhysicalDevice physicalDevice) {
    return physicalDevice != nullptr && !physicalDevice->destroyRequested ? physicalDevice->handle : VK_NULL_HANDLE;
}

GPU_API GPUInstance GPU_CALL gpuPhysicalDeviceGetInstance(GPUPhysicalDevice physicalDevice) {
    return physicalDevice != nullptr && !physicalDevice->destroyRequested ? physicalDevice->instance : nullptr;
}

GPU_API void GPU_CALL gpuPhysicalDeviceRelease(GPUPhysicalDevice physicalDevice) {
    if (physicalDevice == nullptr || physicalDevice->destroyRequested) {
        return;
    }

    physicalDevice->destroyRequested = true;
    gpuPhysicalDeviceDrop(physicalDevice);
}

}  // extern "C"

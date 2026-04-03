#include "PerformanceConfigurationINTEL.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuPerformanceConfigurationINTELAcquire(
    GPUDevice device,
    const VkPerformanceConfigurationAcquireInfoINTEL* acquireInfo,
    GPUPerformanceConfigurationINTEL* configuration) {
    gpu::internal::clearLastError();
    if (device == nullptr || acquireInfo == nullptr || configuration == nullptr) {
        gpu::internal::setLastError("Device, acquire info, and configuration output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    *configuration = nullptr;
    VkPerformanceConfigurationINTEL handle = VK_NULL_HANDLE;
    const VkResult result = gpuAcquirePerformanceConfigurationINTEL(device->handle, acquireInfo, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to acquire performance configuration INTEL.");
        return result;
    }
    GPUPerformanceConfigurationINTEL wrapper = new (std::nothrow) GPUPerformanceConfigurationINTEL_T{device, handle, false};
    if (wrapper == nullptr) {
        gpuReleasePerformanceConfigurationINTEL(device->handle, handle);
        gpu::internal::setLastError("Failed to allocate PerformanceConfigurationINTEL.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    gpuDeviceRetain(device);
    *configuration = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuPerformanceConfigurationINTELRelease(GPUPerformanceConfigurationINTEL configuration) {
    if (configuration == nullptr || configuration->destroyRequested) {
        return;
    }
    configuration->destroyRequested = true;
    gpuReleasePerformanceConfigurationINTEL(configuration->device->handle, configuration->handle);
    gpuDeviceDrop(configuration->device);
    delete configuration;
}

GPU_API VkPerformanceConfigurationINTEL GPU_CALL gpuPerformanceConfigurationINTELGetVkHandle(
    GPUPerformanceConfigurationINTEL configuration) {
    return configuration != nullptr && !configuration->destroyRequested ? configuration->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuPerformanceConfigurationINTELGetDevice(GPUPerformanceConfigurationINTEL configuration) {
    return configuration != nullptr && !configuration->destroyRequested ? configuration->device : nullptr;
}

}  // extern "C"

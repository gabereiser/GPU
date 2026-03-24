#include "Swapchain.h"

#include <new>

#include "Device.h"
#include "Surface.h"
#include "Internal/Error.h"

void gpuSwapchainRetain(GPUSwapchain swapchain) {
    if (swapchain != nullptr) {
        ++swapchain->refCount;
    }
}

void gpuSwapchainDrop(GPUSwapchain swapchain) {
    if (swapchain == nullptr) {
        return;
    }

    if (swapchain->refCount > 0) {
        --swapchain->refCount;
    }

    if (swapchain->refCount == 0) {
        if (swapchain->handle != VK_NULL_HANDLE) {
            vkDestroySwapchainKHR(swapchain->device->handle, swapchain->handle, swapchain->allocator);
        }
        gpuDeviceDrop(swapchain->device);
        gpuSurfaceDrop(swapchain->surface);
        delete swapchain;
    }
}

extern "C" {

GPU_API VkResult GPU_CALL gpuSwapchainCreate(
    GPUDevice device,
    GPUSurface surface,
    const VkSwapchainCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSwapchain* swapchain) {
    gpu::internal::clearLastError();

    if (device == nullptr || surface == nullptr || createInfo == nullptr || swapchain == nullptr) {
        gpu::internal::setLastError("Device, surface, create info, and swapchain output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested || surface->destroyRequested) {
        gpu::internal::setLastError("Device or surface is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *swapchain = nullptr;

    VkSwapchainKHR handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateSwapchainKHR(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create Vulkan swapchain.");
        return result;
    }

    GPUSwapchain wrapper = new (std::nothrow) GPUSwapchain_T{device, surface, handle, allocator, 1, false};
    if (wrapper == nullptr) {
        vkDestroySwapchainKHR(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate Swapchain.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    gpuSurfaceRetain(surface);

    *swapchain = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuSwapchainDestroy(GPUSwapchain swapchain) {
    if (swapchain == nullptr) {
        return;
    }

    if (swapchain->destroyRequested) {
        return;
    }

    swapchain->destroyRequested = true;
    gpuSwapchainDrop(swapchain);
}

GPU_API VkSwapchainKHR GPU_CALL gpuSwapchainGetVkHandle(GPUSwapchain swapchain) {
    return swapchain != nullptr && !swapchain->destroyRequested ? swapchain->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuSwapchainGetDevice(GPUSwapchain swapchain) {
    return swapchain != nullptr && !swapchain->destroyRequested ? swapchain->device : nullptr;
}

GPU_API GPUSurface GPU_CALL gpuSwapchainGetSurface(GPUSwapchain swapchain) {
    return swapchain != nullptr && !swapchain->destroyRequested ? swapchain->surface : nullptr;
}

GPU_API VkSwapchainKHR GPU_CALL gpuSwapchainKHRGetVkHandle(GPUSwapchain swapchain) {
    return gpuSwapchainGetVkHandle(swapchain);
}

GPU_API GPUDevice GPU_CALL gpuSwapchainKHRGetDevice(GPUSwapchain swapchain) {
    return gpuSwapchainGetDevice(swapchain);
}

GPU_API GPUSurface GPU_CALL gpuSwapchainKHRGetSurface(GPUSwapchain swapchain) {
    return gpuSwapchainGetSurface(swapchain);
}

}  // extern "C"

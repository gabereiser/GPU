#include "ShaderModule.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuShaderModuleCreate(
    GPUDevice device,
    const VkShaderModuleCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUShaderModule* shaderModule) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || shaderModule == nullptr) {
        gpu::internal::setLastError("Device, create info, and shader module output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *shaderModule = nullptr;

    VkShaderModule handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateShaderModule(device->handle, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create shader module.");
        return result;
    }

    GPUShaderModule wrapper = new (std::nothrow) GPUShaderModule_T{device, handle, allocator};
    if (wrapper == nullptr) {
        vkDestroyShaderModule(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate ShaderModule.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *shaderModule = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuShaderModuleDestroy(GPUShaderModule shaderModule) {
    if (shaderModule == nullptr) {
        return;
    }

    vkDestroyShaderModule(shaderModule->device->handle, shaderModule->handle, shaderModule->allocator);
    delete shaderModule;
}

GPU_API VkShaderModule GPU_CALL gpuShaderModuleGetVkHandle(GPUShaderModule shaderModule) {
    return shaderModule != nullptr ? shaderModule->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuShaderModuleGetDevice(GPUShaderModule shaderModule) {
    return shaderModule != nullptr ? shaderModule->device : nullptr;
}

}  // extern "C"

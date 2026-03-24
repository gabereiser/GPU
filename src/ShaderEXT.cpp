#include "ShaderEXT.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuShaderEXTCreate(
    GPUDevice device,
    const VkShaderCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUShaderEXT* shader) {
    gpu::internal::clearLastError();

    if (device == nullptr || createInfo == nullptr || shader == nullptr) {
        gpu::internal::setLastError("Device, create info, and shader output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (device->destroyRequested) {
        gpu::internal::setLastError("Device is being destroyed.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *shader = nullptr;

    VkShaderEXT handle = VK_NULL_HANDLE;
    const VkResult result = vkCreateShadersEXT(device->handle, 1, createInfo, allocator, &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to create shader EXT.");
        return result;
    }

    GPUShaderEXT wrapper = new (std::nothrow) GPUShaderEXT_T{device, handle, allocator, false};
    if (wrapper == nullptr) {
        vkDestroyShaderEXT(device->handle, handle, allocator);
        gpu::internal::setLastError("Failed to allocate ShaderEXT.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    gpuDeviceRetain(device);
    *shader = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuShaderEXTDestroy(GPUShaderEXT shader) {
    if (shader == nullptr || shader->destroyRequested) {
        return;
    }

    shader->destroyRequested = true;
    vkDestroyShaderEXT(shader->device->handle, shader->handle, shader->allocator);
    gpuDeviceDrop(shader->device);
    delete shader;
}

GPU_API VkShaderEXT GPU_CALL gpuShaderEXTGetVkHandle(GPUShaderEXT shader) {
    return shader != nullptr && !shader->destroyRequested ? shader->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuShaderEXTGetDevice(GPUShaderEXT shader) {
    return shader != nullptr && !shader->destroyRequested ? shader->device : nullptr;
}

}  // extern "C"

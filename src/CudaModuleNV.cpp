#if defined(VK_CUDA_MODULE)
#include "CudaModuleNV.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C"
{

    GPU_API VkResult GPU_CALL gpuCudaModuleNVCreate(
        GPUDevice device,
        const VkCudaModuleCreateInfoNV *createInfo,
        const VkAllocationCallbacks *allocator,
        GPUCudaModuleNV *module)
    {
        gpu::internal::clearLastError();

        if (device == nullptr || createInfo == nullptr || module == nullptr)
        {
            gpu::internal::setLastError("Device, create info, and CUDA module output must not be null.");
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        if (device->destroyRequested)
        {
            gpu::internal::setLastError("Device is being destroyed.");
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        *module = nullptr;

        VkCudaModuleNV handle = VK_NULL_HANDLE;
        const VkResult result = gpuCreateCudaModuleNV(device->handle, createInfo, allocator, &handle);
        if (result != VK_SUCCESS)
        {
            gpu::internal::setLastError("Failed to create CUDA module NV.");
            return result;
        }

        GPUCudaModuleNV wrapper = new (std::nothrow) GPUCudaModuleNV_T{device, handle, allocator, false};
        if (wrapper == nullptr)
        {
            gpuDestroyCudaModuleNV(device->handle, handle, allocator);
            gpu::internal::setLastError("Failed to allocate CudaModuleNV.");
            return VK_ERROR_OUT_OF_HOST_MEMORY;
        }

        gpuDeviceRetain(device);
        *module = wrapper;
        return VK_SUCCESS;
    }

    GPU_API void GPU_CALL gpuCudaModuleNVDestroy(GPUCudaModuleNV module)
    {
        if (module == nullptr || module->destroyRequested)
        {
            return;
        }

        module->destroyRequested = true;
        gpuDestroyCudaModuleNV(module->device->handle, module->handle, module->allocator);
        gpuDeviceDrop(module->device);
        delete module;
    }

    GPU_API VkCudaModuleNV GPU_CALL gpuCudaModuleNVGetVkHandle(GPUCudaModuleNV module)
    {
        return module != nullptr && !module->destroyRequested ? module->handle : VK_NULL_HANDLE;
    }

    GPU_API GPUDevice GPU_CALL gpuCudaModuleNVGetDevice(GPUCudaModuleNV module)
    {
        return module != nullptr && !module->destroyRequested ? module->device : nullptr;
    }

} // extern "C"
#endif
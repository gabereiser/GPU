#if defined(VK_ENABLE_SCISYNC)
#include "SemaphoreSciSyncPoolNV.h"

#include <new>

#include "Device.h"
#include "Internal/Error.h"

extern "C"
{

    GPU_API VkResult GPU_CALL gpuSemaphoreSciSyncPoolNVCreate(
        GPUDevice device,
        const VkSemaphoreSciSyncPoolCreateInfoNV *createInfo,
        const VkAllocationCallbacks *allocator,
        GPUSemaphoreSciSyncPoolNV *semaphoreSciSyncPool)
    {
        gpu::internal::clearLastError();

        if (device == nullptr || createInfo == nullptr || semaphoreSciSyncPool == nullptr)
        {
            gpu::internal::setLastError("Device, create info, and semaphore sci sync pool output must not be null.");
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        if (device->destroyRequested)
        {
            gpu::internal::setLastError("Device is being destroyed.");
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        *semaphoreSciSyncPool = nullptr;

        VkSemaphoreSciSyncPoolNV handle = VK_NULL_HANDLE;
        const VkResult result =
            gpuCreateSemaphoreSciSyncPoolNV(device->handle, createInfo, allocator, &handle);
        if (result != VK_SUCCESS)
        {
            gpu::internal::setLastError("Failed to create semaphore sci sync pool NV.");
            return result;
        }

        GPUSemaphoreSciSyncPoolNV wrapper =
            new (std::nothrow) GPUSemaphoreSciSyncPoolNV_T{device, handle, allocator, false};
        if (wrapper == nullptr)
        {
            gpuDestroySemaphoreSciSyncPoolNV(device->handle, handle, allocator);
            gpu::internal::setLastError("Failed to allocate SemaphoreSciSyncPoolNV.");
            return VK_ERROR_OUT_OF_HOST_MEMORY;
        }

        gpuDeviceRetain(device);
        *semaphoreSciSyncPool = wrapper;
        return VK_SUCCESS;
    }

    GPU_API void GPU_CALL gpuSemaphoreSciSyncPoolNVDestroy(GPUSemaphoreSciSyncPoolNV semaphoreSciSyncPool)
    {
        if (semaphoreSciSyncPool == nullptr || semaphoreSciSyncPool->destroyRequested)
        {
            return;
        }

        semaphoreSciSyncPool->destroyRequested = true;
        gpuDestroySemaphoreSciSyncPoolNV(
            semaphoreSciSyncPool->device->handle,
            semaphoreSciSyncPool->handle,
            semaphoreSciSyncPool->allocator);
        gpuDeviceDrop(semaphoreSciSyncPool->device);
        delete semaphoreSciSyncPool;
    }

    GPU_API VkSemaphoreSciSyncPoolNV GPU_CALL gpuSemaphoreSciSyncPoolNVGetVkHandle(
        GPUSemaphoreSciSyncPoolNV semaphoreSciSyncPool)
    {
        return semaphoreSciSyncPool != nullptr && !semaphoreSciSyncPool->destroyRequested
                   ? semaphoreSciSyncPool->handle
                   : VK_NULL_HANDLE;
    }

    GPU_API GPUDevice GPU_CALL gpuSemaphoreSciSyncPoolNVGetDevice(GPUSemaphoreSciSyncPoolNV semaphoreSciSyncPool)
    {
        return semaphoreSciSyncPool != nullptr && !semaphoreSciSyncPool->destroyRequested
                   ? semaphoreSciSyncPool->device
                   : nullptr;
    }

} // extern "C"
#endif
#include "DescriptorSet.h"

#include <new>

#include "DescriptorPool.h"
#include "Device.h"
#include "Internal/Error.h"

extern "C" {

GPU_API VkResult GPU_CALL gpuDescriptorSetAllocate(
    GPUDescriptorPool descriptorPool,
    const VkDescriptorSetAllocateInfo* allocateInfo,
    GPUDescriptorSet* descriptorSet) {
    gpu::internal::clearLastError();

    if (descriptorPool == nullptr || allocateInfo == nullptr || descriptorSet == nullptr) {
        gpu::internal::setLastError("Descriptor pool, allocate info, and descriptor set output must not be null.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    if (allocateInfo->descriptorSetCount != 1) {
        gpu::internal::setLastError("Descriptor set allocation currently supports exactly one set.");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    *descriptorSet = nullptr;

    VkDescriptorSetAllocateInfo request = *allocateInfo;
    request.descriptorPool = descriptorPool->handle;
    request.descriptorSetCount = 1;

    VkDescriptorSet handle = VK_NULL_HANDLE;
    const VkResult result = gpuAllocateDescriptorSets(
        descriptorPool->device->handle,
        &request,
        &handle);
    if (result != VK_SUCCESS) {
        gpu::internal::setLastError("Failed to allocate descriptor set.");
        return result;
    }

    GPUDescriptorSet wrapper = new (std::nothrow) GPUDescriptorSet_T{descriptorPool, handle};
    if (wrapper == nullptr) {
        gpuFreeDescriptorSets(descriptorPool->device->handle, descriptorPool->handle, 1, &handle);
        gpu::internal::setLastError("Failed to allocate DescriptorSet.");
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    *descriptorSet = wrapper;
    return VK_SUCCESS;
}

GPU_API void GPU_CALL gpuDescriptorSetDestroy(GPUDescriptorSet descriptorSet) {
    if (descriptorSet == nullptr) {
        return;
    }

    if (descriptorSet->pool != nullptr) {
        gpuFreeDescriptorSets(
            descriptorSet->pool->device->handle,
            descriptorSet->pool->handle,
            1,
            &descriptorSet->handle);
    }

    delete descriptorSet;
}

GPU_API VkDescriptorSet GPU_CALL gpuDescriptorSetGetVkHandle(GPUDescriptorSet descriptorSet) {
    return descriptorSet != nullptr ? descriptorSet->handle : VK_NULL_HANDLE;
}

GPU_API GPUDescriptorPool GPU_CALL gpuDescriptorSetGetPool(GPUDescriptorSet descriptorSet) {
    return descriptorSet != nullptr ? descriptorSet->pool : nullptr;
}

GPU_API GPUDevice GPU_CALL gpuDescriptorSetGetDevice(GPUDescriptorSet descriptorSet) {
    return descriptorSet != nullptr && descriptorSet->pool != nullptr ? descriptorSet->pool->device : nullptr;
}

}  // extern "C"

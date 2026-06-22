#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>
#include "gpu/gpu_structs.h"

// Simple boolean aliases matching Vulkan's VkBool32 values.
#define GPU_TRUE VK_TRUE
#define GPU_FALSE VK_FALSE
#if defined(VK_ENABLE_BETA_EXTENSIONS)
#include <vulkan/vulkan_beta.h>
#endif

#if defined(_WIN32)
#if defined(GPU_BUILD)
#define GPU_API __declspec(dllexport)
#else
#define GPU_API __declspec(dllimport)
#endif
#define GPU_CALL VKAPI_CALL
#else
#define GPU_API
#define GPU_CALL VKAPI_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GPUInstance_T* GPUInstance;
typedef struct GPUPhysicalDevice_T* GPUPhysicalDevice;
typedef struct GPUDevice_T* GPUDevice;
typedef struct GPUQueue_T* GPUQueue;
typedef struct GPUSurface_T* GPUSurface;

typedef struct GPUSwapchain_T* GPUSwapchain;
typedef struct GPUShaderModule_T* GPUShaderModule;
typedef struct GPUPipeline_T* GPUPipeline;
typedef struct GPUPipelineLayout_T* GPUPipelineLayout;
typedef struct GPUSampler_T* GPUSampler;
typedef struct GPUDescriptorSetLayout_T* GPUDescriptorSetLayout;
typedef struct GPUDescriptorPool_T* GPUDescriptorPool;
typedef struct GPUDescriptorSet_T* GPUDescriptorSet;
typedef struct GPUFramebuffer_T* GPUFramebuffer;
typedef struct GPURenderPass_T* GPURenderPass;
typedef struct GPUPipelineCache_T* GPUPipelineCache;
typedef struct GPUDescriptorUpdateTemplate_T* GPUDescriptorUpdateTemplate;
typedef struct GPUSamplerYcbcrConversion_T* GPUSamplerYcbcrConversion;
typedef struct GPUPrivateDataSlot_T* GPUPrivateDataSlot;
typedef struct GPUCommandPool_T* GPUCommandPool;
typedef struct GPUCommandBuffer_T* GPUCommandBuffer;
typedef struct GPUDeviceMemory_T* GPUDeviceMemory;
typedef struct GPUBuffer_T* GPUBuffer;
typedef struct GPUBufferView_T* GPUBufferView;
typedef struct GPUImage_T* GPUImage;
typedef struct GPUImageView_T* GPUImageView;
typedef struct GPUFence_T* GPUFence;
typedef struct GPUSemaphore_T* GPUSemaphore;
typedef struct GPUEvent_T* GPUEvent;
typedef struct GPUQueryPool_T* GPUQueryPool;
typedef struct GPUDebugReportCallbackEXT_T* GPUDebugReportCallbackEXT;
typedef struct GPUDebugUtilsMessengerEXT_T* GPUDebugUtilsMessengerEXT;
typedef struct GPUValidationCacheEXT_T* GPUValidationCacheEXT;
typedef struct GPUDeferredOperationKHR_T* GPUDeferredOperationKHR;
typedef struct GPUIndirectCommandsLayoutNV_T* GPUIndirectCommandsLayoutNV;
typedef struct GPUIndirectCommandsLayoutEXT_T* GPUIndirectCommandsLayoutEXT;
typedef struct GPUIndirectExecutionSetEXT_T* GPUIndirectExecutionSetEXT;
typedef struct GPUAccelerationStructureKHR_T* GPUAccelerationStructureKHR;
typedef struct GPUAccelerationStructureNV_T* GPUAccelerationStructureNV;
typedef struct GPUMicromapEXT_T* GPUMicromapEXT;
typedef struct GPUBufferCollectionFUCHSIA_T* GPUBufferCollectionFUCHSIA;
typedef struct GPUPerformanceConfigurationINTEL_T* GPUPerformanceConfigurationINTEL;
typedef struct GPUPipelineBinaryKHR_T* GPUPipelineBinaryKHR;
typedef struct GPUCuModuleNVX_T* GPUCuModuleNVX;
typedef struct GPUCuFunctionNVX_T* GPUCuFunctionNVX;
typedef struct GPUOpticalFlowSessionNV_T* GPUOpticalFlowSessionNV;
typedef struct GPUShaderEXT_T* GPUShaderEXT;
typedef struct GPUTensorARM_T* GPUTensorARM;
typedef struct GPUTensorViewARM_T* GPUTensorViewARM;
typedef struct GPUDataGraphPipelineSessionARM_T* GPUDataGraphPipelineSessionARM;
typedef struct GPUDisplayKHR_T* GPUDisplayKHR;
typedef struct GPUDisplayModeKHR_T* GPUDisplayModeKHR;
typedef struct GPUVideoSessionKHR_T* GPUVideoSessionKHR;
typedef struct GPUVideoSessionParametersKHR_T* GPUVideoSessionParametersKHR;
typedef struct GPUSemaphoreSciSyncPoolNV_T* GPUSemaphoreSciSyncPoolNV;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
typedef struct GPUCudaModuleNV_T* GPUCudaModuleNV;
typedef struct GPUCudaFunctionNV_T* GPUCudaFunctionNV;
#endif
typedef struct GPUExternalComputeQueueNV_T* GPUExternalComputeQueueNV;

typedef enum {
    GPU_SHADER_LANGUAGE_GLSL = 0,
    GPU_SHADER_LANGUAGE_HLSL = 1
} GPUShaderLanguage;

GPU_API bool GPU_CALL gpuCompileShader(
    GPUShaderLanguage language,
    GpuShaderStageFlagBits stage,
    const char* source,
    size_t sourceLen,
    void** outSpirv,
    size_t* outSize);

GPU_API void GPU_CALL gpuFreeShaderBinary(void* spirv);

GPU_API uint32_t GPU_CALL gpuGetApiVersion(void);
GPU_API const char* GPU_CALL gpuGetLastError(void);

GPU_API GpuResult GPU_CALL gpuInstanceCreate(
    const GpuInstanceCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUInstance* instance);
GPU_API void GPU_CALL gpuInstanceDestroy(GPUInstance instance);
GPU_API uint32_t GPU_CALL gpuInstanceGetPhysicalDeviceCount(GPUInstance instance);
GPU_API GpuResult GPU_CALL gpuInstanceGetPhysicalDevice(
    GPUInstance instance,
    uint32_t index,
    GPUPhysicalDevice* physicalDevice);

GPU_API GPUInstance GPU_CALL gpuPhysicalDeviceGetInstance(GPUPhysicalDevice physicalDevice);
GPU_API void GPU_CALL gpuPhysicalDeviceRelease(GPUPhysicalDevice physicalDevice);
GPU_API uint32_t GPU_CALL gpuPhysicalDeviceGetDisplayCountKHR(GPUPhysicalDevice physicalDevice);
GPU_API GpuResult GPU_CALL gpuPhysicalDeviceGetDisplayKHR(
    GPUPhysicalDevice physicalDevice,
    uint32_t index,
    GPUDisplayKHR* display);

GPU_API GpuResult GPU_CALL gpuDeviceCreate(
    GPUPhysicalDevice physicalDevice,
    const GpuDeviceCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUDevice* device);
GPU_API void GPU_CALL gpuDeviceDestroy(GPUDevice device);
GPU_API GPUPhysicalDevice GPU_CALL gpuDeviceGetPhysicalDevice(GPUDevice device);
GPU_API GpuResult GPU_CALL gpuDeviceGetQueue(
    GPUDevice device,
    uint32_t familyIndex,
    uint32_t queueIndex,
    GPUQueue* queue);

GPU_API GPUDevice GPU_CALL gpuQueueGetDevice(GPUQueue queue);
GPU_API uint32_t GPU_CALL gpuQueueGetFamilyIndex(GPUQueue queue);
GPU_API uint32_t GPU_CALL gpuQueueGetQueueIndex(GPUQueue queue);
GPU_API void GPU_CALL gpuQueueRelease(GPUQueue queue);

GPU_API void GPU_CALL gpuSurfaceDestroy(GPUSurface surface);
GPU_API GPUInstance GPU_CALL gpuSurfaceGetInstance(GPUSurface surface);
GPU_API GPUInstance GPU_CALL gpuSurfaceKHRGetInstance(GPUSurface surface);

GPU_API GpuResult GPU_CALL gpuDebugReportCallbackEXTCreate(
    GPUInstance instance,
    const GpuDebugReportCallbackCreateInfoEXT* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUDebugReportCallbackEXT* callback);
GPU_API void GPU_CALL gpuDebugReportCallbackEXTDestroy(GPUDebugReportCallbackEXT callback);
GPU_API GPUInstance GPU_CALL gpuDebugReportCallbackEXTGetInstance(GPUDebugReportCallbackEXT callback);

GPU_API GpuResult GPU_CALL gpuDebugUtilsMessengerEXTCreate(
    GPUInstance instance,
    const GpuDebugUtilsMessengerCreateInfoEXT* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUDebugUtilsMessengerEXT* messenger);
GPU_API void GPU_CALL gpuDebugUtilsMessengerEXTDestroy(GPUDebugUtilsMessengerEXT messenger);
GPU_API GPUInstance GPU_CALL gpuDebugUtilsMessengerEXTGetInstance(GPUDebugUtilsMessengerEXT messenger);

GPU_API GpuResult GPU_CALL gpuSwapchainCreate(
    GPUDevice device,
    GPUSurface surface,
    const GpuSwapchainCreateInfoKHR* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUSwapchain* swapchain);
GPU_API void GPU_CALL gpuSwapchainDestroy(GPUSwapchain swapchain);
GPU_API GPUDevice GPU_CALL gpuSwapchainGetDevice(GPUSwapchain swapchain);
GPU_API GPUSurface GPU_CALL gpuSwapchainGetSurface(GPUSwapchain swapchain);
GPU_API GPUDevice GPU_CALL gpuSwapchainKHRGetDevice(GPUSwapchain swapchain);
GPU_API GPUSurface GPU_CALL gpuSwapchainKHRGetSurface(GPUSwapchain swapchain);

GPU_API GpuResult GPU_CALL gpuShaderModuleCreate(
    GPUDevice device,
    const GpuShaderModuleCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUShaderModule* shaderModule);
GPU_API void GPU_CALL gpuShaderModuleDestroy(GPUShaderModule shaderModule);
GPU_API GPUDevice GPU_CALL gpuShaderModuleGetDevice(GPUShaderModule shaderModule);

GPU_API GpuResult GPU_CALL gpuPipelineLayoutCreate(
    GPUDevice device,
    const GpuPipelineLayoutCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUPipelineLayout* pipelineLayout);
GPU_API void GPU_CALL gpuPipelineLayoutDestroy(GPUPipelineLayout pipelineLayout);
GPU_API GPUDevice GPU_CALL gpuPipelineLayoutGetDevice(GPUPipelineLayout pipelineLayout);

GPU_API GpuResult GPU_CALL gpuSamplerCreate(
    GPUDevice device,
    const GpuSamplerCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUSampler* sampler);
GPU_API void GPU_CALL gpuSamplerDestroy(GPUSampler sampler);
GPU_API GPUDevice GPU_CALL gpuSamplerGetDevice(GPUSampler sampler);

GPU_API GpuResult GPU_CALL gpuDescriptorSetLayoutCreate(
    GPUDevice device,
    const GpuDescriptorSetLayoutCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUDescriptorSetLayout* descriptorSetLayout);
GPU_API void GPU_CALL gpuDescriptorSetLayoutDestroy(GPUDescriptorSetLayout descriptorSetLayout);
GPU_API GPUDevice GPU_CALL gpuDescriptorSetLayoutGetDevice(GPUDescriptorSetLayout descriptorSetLayout);

GPU_API GpuResult GPU_CALL gpuDescriptorPoolCreate(
    GPUDevice device,
    const GpuDescriptorPoolCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUDescriptorPool* descriptorPool);
GPU_API void GPU_CALL gpuDescriptorPoolDestroy(GPUDescriptorPool descriptorPool);
GPU_API GPUDevice GPU_CALL gpuDescriptorPoolGetDevice(GPUDescriptorPool descriptorPool);

GPU_API GpuResult GPU_CALL gpuDescriptorSetAllocate(
    GPUDescriptorPool descriptorPool,
    const GpuDescriptorSetAllocateInfo* allocateInfo,
    GPUDescriptorSet* descriptorSet);
GPU_API void GPU_CALL gpuDescriptorSetDestroy(GPUDescriptorSet descriptorSet);
GPU_API GPUDescriptorPool GPU_CALL gpuDescriptorSetGetPool(GPUDescriptorSet descriptorSet);
GPU_API GPUDevice GPU_CALL gpuDescriptorSetGetDevice(GPUDescriptorSet descriptorSet);

GPU_API GpuResult GPU_CALL gpuFramebufferCreate(
    GPUDevice device,
    const GpuFramebufferCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUFramebuffer* framebuffer);
GPU_API void GPU_CALL gpuFramebufferDestroy(GPUFramebuffer framebuffer);
GPU_API GPUDevice GPU_CALL gpuFramebufferGetDevice(GPUFramebuffer framebuffer);

GPU_API GpuResult GPU_CALL gpuRenderPassCreate(
    GPUDevice device,
    const GpuRenderPassCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPURenderPass* renderPass);
GPU_API void GPU_CALL gpuRenderPassDestroy(GPURenderPass renderPass);
GPU_API GPUDevice GPU_CALL gpuRenderPassGetDevice(GPURenderPass renderPass);

GPU_API GpuResult GPU_CALL gpuPipelineCreateGraphics(
    GPUDevice device,
    GPUPipelineCache pipelineCache,
    const GpuGraphicsPipelineCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUPipeline* pipeline);
GPU_API GpuResult GPU_CALL gpuPipelineCreateCompute(
    GPUDevice device,
    GPUPipelineCache pipelineCache,
    const GpuComputePipelineCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUPipeline* pipeline);
GPU_API void GPU_CALL gpuPipelineDestroy(GPUPipeline pipeline);
GPU_API GPUDevice GPU_CALL gpuPipelineGetDevice(GPUPipeline pipeline);

GPU_API GpuResult GPU_CALL gpuPipelineCacheCreate(
    GPUDevice device,
    const GpuPipelineCacheCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUPipelineCache* pipelineCache);
GPU_API void GPU_CALL gpuPipelineCacheDestroy(GPUPipelineCache pipelineCache);
GPU_API GPUDevice GPU_CALL gpuPipelineCacheGetDevice(GPUPipelineCache pipelineCache);

GPU_API GpuResult GPU_CALL gpuDescriptorUpdateTemplateCreate(
    GPUDevice device,
    const GpuDescriptorUpdateTemplateCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUDescriptorUpdateTemplate* descriptorUpdateTemplate);
GPU_API void GPU_CALL gpuDescriptorUpdateTemplateDestroy(GPUDescriptorUpdateTemplate descriptorUpdateTemplate);
GPU_API GPUDevice GPU_CALL gpuDescriptorUpdateTemplateGetDevice(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate);
GPU_API GPUDevice GPU_CALL gpuDescriptorUpdateTemplateKHRGetDevice(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate);

GPU_API GpuResult GPU_CALL gpuSamplerYcbcrConversionCreate(
    GPUDevice device,
    const GpuSamplerYcbcrConversionCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUSamplerYcbcrConversion* samplerYcbcrConversion);
GPU_API void GPU_CALL gpuSamplerYcbcrConversionDestroy(GPUSamplerYcbcrConversion samplerYcbcrConversion);
GPU_API GPUDevice GPU_CALL gpuSamplerYcbcrConversionGetDevice(
    GPUSamplerYcbcrConversion samplerYcbcrConversion);
GPU_API GPUDevice GPU_CALL gpuSamplerYcbcrConversionKHRGetDevice(
    GPUSamplerYcbcrConversion samplerYcbcrConversion);

GPU_API GpuResult GPU_CALL gpuPrivateDataSlotCreate(
    GPUDevice device,
    const GpuPrivateDataSlotCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUPrivateDataSlot* privateDataSlot);
GPU_API void GPU_CALL gpuPrivateDataSlotDestroy(GPUPrivateDataSlot privateDataSlot);
GPU_API GPUDevice GPU_CALL gpuPrivateDataSlotGetDevice(GPUPrivateDataSlot privateDataSlot);
GPU_API GPUDevice GPU_CALL gpuPrivateDataSlotEXTGetDevice(GPUPrivateDataSlot privateDataSlot);

GPU_API GpuResult GPU_CALL gpuCommandPoolCreate(
    GPUDevice device,
    const GpuCommandPoolCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUCommandPool* commandPool);
GPU_API void GPU_CALL gpuCommandPoolDestroy(GPUCommandPool commandPool);
GPU_API GPUDevice GPU_CALL gpuCommandPoolGetDevice(GPUCommandPool commandPool);

GPU_API GpuResult GPU_CALL gpuCommandBufferCreate(
    GPUCommandPool commandPool,
    GpuCommandBufferLevel level,
    GPUCommandBuffer* commandBuffer);
GPU_API void GPU_CALL gpuCommandBufferDestroy(GPUCommandBuffer commandBuffer);
GPU_API GPUCommandPool GPU_CALL gpuCommandBufferGetCommandPool(GPUCommandBuffer commandBuffer);

GPU_API GpuResult GPU_CALL gpuDeviceMemoryCreate(
    GPUDevice device,
    const GpuMemoryAllocateInfo* allocateInfo,
    const GpuAllocationCallbacks* allocator,
    GPUDeviceMemory* memory);
GPU_API void GPU_CALL gpuDeviceMemoryDestroy(GPUDeviceMemory memory);
GPU_API GPUDevice GPU_CALL gpuDeviceMemoryGetDevice(GPUDeviceMemory memory);

GPU_API GpuResult GPU_CALL gpuBufferCreate(
    GPUDevice device,
    const GpuBufferCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUBuffer* buffer);
GPU_API void GPU_CALL gpuBufferDestroy(GPUBuffer buffer);
GPU_API GPUDevice GPU_CALL gpuBufferGetDevice(GPUBuffer buffer);

GPU_API GpuResult GPU_CALL gpuBufferViewCreate(
    GPUDevice device,
    const GpuBufferViewCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUBufferView* bufferView);
GPU_API void GPU_CALL gpuBufferViewDestroy(GPUBufferView bufferView);
GPU_API GPUDevice GPU_CALL gpuBufferViewGetDevice(GPUBufferView bufferView);

GPU_API GpuResult GPU_CALL gpuImageCreate(
    GPUDevice device,
    const GpuImageCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUImage* image);
GPU_API void GPU_CALL gpuImageDestroy(GPUImage image);
GPU_API GPUDevice GPU_CALL gpuImageGetDevice(GPUImage image);

GPU_API GpuResult GPU_CALL gpuImageViewCreate(
    GPUDevice device,
    const GpuImageViewCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUImageView* imageView);
GPU_API void GPU_CALL gpuImageViewDestroy(GPUImageView imageView);
GPU_API GPUDevice GPU_CALL gpuImageViewGetDevice(GPUImageView imageView);

GPU_API GpuResult GPU_CALL gpuFenceCreate(
    GPUDevice device,
    const GpuFenceCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUFence* fence);
GPU_API void GPU_CALL gpuFenceDestroy(GPUFence fence);
GPU_API GPUDevice GPU_CALL gpuFenceGetDevice(GPUFence fence);

GPU_API GpuResult GPU_CALL gpuDeviceWaitForFences(GPUDevice device, uint32_t fenceCount, const GPUFence* pFences, GpuBool32 waitAll, uint64_t timeout);

GPU_API GpuResult GPU_CALL gpuSemaphoreCreate(
    GPUDevice device,
    const GpuSemaphoreCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUSemaphore* semaphore);
GPU_API void GPU_CALL gpuSemaphoreDestroy(GPUSemaphore semaphore);
GPU_API GPUDevice GPU_CALL gpuSemaphoreGetDevice(GPUSemaphore semaphore);

GPU_API GpuResult GPU_CALL gpuEventCreate(
    GPUDevice device,
    const GpuEventCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUEvent* event);
GPU_API void GPU_CALL gpuEventDestroy(GPUEvent event);
GPU_API GPUDevice GPU_CALL gpuEventGetDevice(GPUEvent event);

GPU_API GpuResult GPU_CALL gpuQueryPoolCreate(
    GPUDevice device,
    const GpuQueryPoolCreateInfo* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUQueryPool* queryPool);
GPU_API void GPU_CALL gpuQueryPoolDestroy(GPUQueryPool queryPool);
GPU_API GPUDevice GPU_CALL gpuQueryPoolGetDevice(GPUQueryPool queryPool);

GPU_API GpuResult GPU_CALL gpuValidationCacheEXTCreate(
    GPUDevice device,
    const GpuValidationCacheCreateInfoEXT* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUValidationCacheEXT* validationCache);
GPU_API void GPU_CALL gpuValidationCacheEXTDestroy(GPUValidationCacheEXT validationCache);
GPU_API GPUDevice GPU_CALL gpuValidationCacheEXTGetDevice(GPUValidationCacheEXT validationCache);

GPU_API GpuResult GPU_CALL gpuDeferredOperationKHRCreate(
    GPUDevice device,
    const GpuAllocationCallbacks* allocator,
    GPUDeferredOperationKHR* deferredOperation);
GPU_API void GPU_CALL gpuDeferredOperationKHRDestroy(GPUDeferredOperationKHR deferredOperation);
GPU_API GPUDevice GPU_CALL gpuDeferredOperationKHRGetDevice(GPUDeferredOperationKHR deferredOperation);

GPU_API GpuResult GPU_CALL gpuIndirectCommandsLayoutNVCreate(
    GPUDevice device,
    const GpuIndirectCommandsLayoutCreateInfoNV* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUIndirectCommandsLayoutNV* indirectCommandsLayout);
GPU_API void GPU_CALL gpuIndirectCommandsLayoutNVDestroy(GPUIndirectCommandsLayoutNV indirectCommandsLayout);
GPU_API GPUDevice GPU_CALL gpuIndirectCommandsLayoutNVGetDevice(GPUIndirectCommandsLayoutNV indirectCommandsLayout);

GPU_API GpuResult GPU_CALL gpuIndirectCommandsLayoutEXTCreate(
    GPUDevice device,
    const GpuIndirectCommandsLayoutCreateInfoEXT* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUIndirectCommandsLayoutEXT* indirectCommandsLayout);
GPU_API void GPU_CALL gpuIndirectCommandsLayoutEXTDestroy(GPUIndirectCommandsLayoutEXT indirectCommandsLayout);
GPU_API GPUDevice GPU_CALL gpuIndirectCommandsLayoutEXTGetDevice(
    GPUIndirectCommandsLayoutEXT indirectCommandsLayout);

GPU_API GpuResult GPU_CALL gpuIndirectExecutionSetEXTCreate(
    GPUDevice device,
    const GpuIndirectExecutionSetCreateInfoEXT* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUIndirectExecutionSetEXT* indirectExecutionSet);
GPU_API void GPU_CALL gpuIndirectExecutionSetEXTDestroy(GPUIndirectExecutionSetEXT indirectExecutionSet);
GPU_API GPUDevice GPU_CALL gpuIndirectExecutionSetEXTGetDevice(GPUIndirectExecutionSetEXT indirectExecutionSet);

GPU_API GpuResult GPU_CALL gpuAccelerationStructureKHRCreate(
    GPUDevice device,
    const GpuAccelerationStructureCreateInfoKHR* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUAccelerationStructureKHR* accelerationStructure);
GPU_API void GPU_CALL gpuAccelerationStructureKHRDestroy(GPUAccelerationStructureKHR accelerationStructure);
GPU_API GPUDevice GPU_CALL gpuAccelerationStructureKHRGetDevice(GPUAccelerationStructureKHR accelerationStructure);

GPU_API GpuResult GPU_CALL gpuAccelerationStructureNVCreate(
    GPUDevice device,
    const GpuAccelerationStructureCreateInfoNV* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUAccelerationStructureNV* accelerationStructure);
GPU_API void GPU_CALL gpuAccelerationStructureNVDestroy(GPUAccelerationStructureNV accelerationStructure);
GPU_API GPUDevice GPU_CALL gpuAccelerationStructureNVGetDevice(GPUAccelerationStructureNV accelerationStructure);

GPU_API GpuResult GPU_CALL gpuMicromapEXTCreate(
    GPUDevice device,
    const GpuMicromapCreateInfoEXT* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUMicromapEXT* micromap);
GPU_API void GPU_CALL gpuMicromapEXTDestroy(GPUMicromapEXT micromap);
GPU_API GPUDevice GPU_CALL gpuMicromapEXTGetDevice(GPUMicromapEXT micromap);
#ifdef FUCHSIA
GPU_API GpuResult GPU_CALL gpuBufferCollectionFUCHSIACreate(
    GPUDevice device,
    const GpuBufferCollectionCreateInfoFUCHSIA* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUBufferCollectionFUCHSIA* collection);
GPU_API void GPU_CALL gpuBufferCollectionFUCHSIADestroy(GPUBufferCollectionFUCHSIA collection);
GPU_API GPUDevice GPU_CALL gpuBufferCollectionFUCHSIAGetDevice(GPUBufferCollectionFUCHSIA collection);
#endif
GPU_API GpuResult GPU_CALL gpuPipelineBinaryKHRCreate(
    GPUDevice device,
    const GpuPipelineBinaryCreateInfoKHR* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUPipelineBinaryKHR* pipelineBinary);
GPU_API void GPU_CALL gpuPipelineBinaryKHRDestroy(GPUPipelineBinaryKHR pipelineBinary);
GPU_API GPUDevice GPU_CALL gpuPipelineBinaryKHRGetDevice(GPUPipelineBinaryKHR pipelineBinary);

GPU_API GpuResult GPU_CALL gpuCuModuleNVXCreate(
    GPUDevice device,
    const GpuCuModuleCreateInfoNVX* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUCuModuleNVX* cuModule);
GPU_API void GPU_CALL gpuCuModuleNVXDestroy(GPUCuModuleNVX cuModule);
GPU_API GPUDevice GPU_CALL gpuCuModuleNVXGetDevice(GPUCuModuleNVX cuModule);

GPU_API GpuResult GPU_CALL gpuCuFunctionNVXCreate(
    GPUDevice device,
    const GpuCuFunctionCreateInfoNVX* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUCuFunctionNVX* cuFunction);
GPU_API void GPU_CALL gpuCuFunctionNVXDestroy(GPUCuFunctionNVX cuFunction);
GPU_API GPUDevice GPU_CALL gpuCuFunctionNVXGetDevice(GPUCuFunctionNVX cuFunction);

GPU_API GpuResult GPU_CALL gpuOpticalFlowSessionNVCreate(
    GPUDevice device,
    const GpuOpticalFlowSessionCreateInfoNV* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUOpticalFlowSessionNV* session);
GPU_API void GPU_CALL gpuOpticalFlowSessionNVDestroy(GPUOpticalFlowSessionNV session);
GPU_API GPUDevice GPU_CALL gpuOpticalFlowSessionNVGetDevice(GPUOpticalFlowSessionNV session);

GPU_API GpuResult GPU_CALL gpuShaderEXTCreate(
    GPUDevice device,
    const GpuShaderCreateInfoEXT* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUShaderEXT* shader);
GPU_API void GPU_CALL gpuShaderEXTDestroy(GPUShaderEXT shader);
GPU_API GPUDevice GPU_CALL gpuShaderEXTGetDevice(GPUShaderEXT shader);

GPU_API GpuResult GPU_CALL gpuTensorARMCreate(
    GPUDevice device,
    const GpuTensorCreateInfoARM* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUTensorARM* tensor);
GPU_API void GPU_CALL gpuTensorARMDestroy(GPUTensorARM tensor);
GPU_API GPUDevice GPU_CALL gpuTensorARMGetDevice(GPUTensorARM tensor);

GPU_API GpuResult GPU_CALL gpuTensorViewARMCreate(
    GPUDevice device,
    const GpuTensorViewCreateInfoARM* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUTensorViewARM* tensorView);
GPU_API void GPU_CALL gpuTensorViewARMDestroy(GPUTensorViewARM tensorView);
GPU_API GPUDevice GPU_CALL gpuTensorViewARMGetDevice(GPUTensorViewARM tensorView);

GPU_API GpuResult GPU_CALL gpuDataGraphPipelineSessionARMCreate(
    GPUDevice device,
    const GpuDataGraphPipelineSessionCreateInfoARM* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUDataGraphPipelineSessionARM* session);
GPU_API void GPU_CALL gpuDataGraphPipelineSessionARMDestroy(GPUDataGraphPipelineSessionARM session);
GPU_API GPUDevice GPU_CALL gpuDataGraphPipelineSessionARMGetDevice(GPUDataGraphPipelineSessionARM session);

GPU_API GPUPhysicalDevice GPU_CALL gpuDisplayKHRGetPhysicalDevice(GPUDisplayKHR display);
GPU_API uint32_t GPU_CALL gpuDisplayKHRGetModeCountKHR(GPUDisplayKHR display);
GPU_API GpuResult GPU_CALL gpuDisplayKHRGetModeKHR(
    GPUDisplayKHR display,
    uint32_t index,
    GPUDisplayModeKHR* displayMode);
GPU_API void GPU_CALL gpuDisplayKHRRelease(GPUDisplayKHR display);

GPU_API GPUDisplayKHR GPU_CALL gpuDisplayModeKHRGetDisplayKHR(GPUDisplayModeKHR displayMode);
GPU_API GPUPhysicalDevice GPU_CALL gpuDisplayModeKHRGetPhysicalDevice(GPUDisplayModeKHR displayMode);
GPU_API void GPU_CALL gpuDisplayModeKHRRelease(GPUDisplayModeKHR displayMode);

GPU_API GpuResult GPU_CALL gpuVideoSessionKHRCreate(
    GPUDevice device,
    const GpuVideoSessionCreateInfoKHR* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUVideoSessionKHR* videoSession);
GPU_API void GPU_CALL gpuVideoSessionKHRDestroy(GPUVideoSessionKHR videoSession);
GPU_API GPUDevice GPU_CALL gpuVideoSessionKHRGetDevice(GPUVideoSessionKHR videoSession);

GPU_API GpuResult GPU_CALL gpuVideoSessionParametersKHRCreate(
    GPUDevice device,
    const GpuVideoSessionParametersCreateInfoKHR* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUVideoSessionParametersKHR* videoSessionParameters);
GPU_API void GPU_CALL gpuVideoSessionParametersKHRDestroy(GPUVideoSessionParametersKHR videoSessionParameters);
GPU_API GPUDevice GPU_CALL gpuVideoSessionParametersKHRGetDevice(
    GPUVideoSessionParametersKHR videoSessionParameters);
#if defined(VK_ENABLE_SCISYNC)
GPU_API GpuResult GPU_CALL gpuSemaphoreSciSyncPoolNVCreate(
    GPUDevice device,
    const GpuSemaphoreSciSyncPoolCreateInfoNV* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUSemaphoreSciSyncPoolNV* semaphoreSciSyncPool);
GPU_API void GPU_CALL gpuSemaphoreSciSyncPoolNVDestroy(GPUSemaphoreSciSyncPoolNV semaphoreSciSyncPool);
GPU_API GPUDevice GPU_CALL gpuSemaphoreSciSyncPoolNVGetDevice(GPUSemaphoreSciSyncPoolNV semaphoreSciSyncPool);
#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)
GPU_API GpuResult GPU_CALL gpuCudaModuleNVCreate(
    GPUDevice device,
    const GpuCudaModuleCreateInfoNV* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUCudaModuleNV* cudaModule);
GPU_API void GPU_CALL gpuCudaModuleNVDestroy(GPUCudaModuleNV cudaModule);
GPU_API GPUDevice GPU_CALL gpuCudaModuleNVGetDevice(GPUCudaModuleNV cudaModule);

GPU_API GpuResult GPU_CALL gpuCudaFunctionNVCreate(
    GPUDevice device,
    const GpuCudaFunctionCreateInfoNV* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUCudaFunctionNV* cudaFunction);
GPU_API void GPU_CALL gpuCudaFunctionNVDestroy(GPUCudaFunctionNV cudaFunction);
GPU_API GPUDevice GPU_CALL gpuCudaFunctionNVGetDevice(GPUCudaFunctionNV cudaFunction);
#endif

GPU_API GpuResult GPU_CALL gpuExternalComputeQueueNVCreate(
    GPUDevice device,
    const GpuExternalComputeQueueCreateInfoNV* createInfo,
    const GpuAllocationCallbacks* allocator,
    GPUExternalComputeQueueNV* externalComputeQueue);
GPU_API void GPU_CALL gpuExternalComputeQueueNVDestroy(GPUExternalComputeQueueNV externalComputeQueue);
GPU_API GPUDevice GPU_CALL gpuExternalComputeQueueNVGetDevice(GPUExternalComputeQueueNV externalComputeQueue);

GPU_API GpuResult GPU_CALL gpuPerformanceConfigurationINTELAcquire(
    GPUDevice device,
    const GpuPerformanceConfigurationAcquireInfoINTEL* acquireInfo,
    GPUPerformanceConfigurationINTEL* configuration);
GPU_API void GPU_CALL gpuPerformanceConfigurationINTELRelease(GPUPerformanceConfigurationINTEL configuration);
GPU_API GPUDevice GPU_CALL gpuPerformanceConfigurationINTELGetDevice(GPUPerformanceConfigurationINTEL configuration);


#ifdef __cplusplus
}
#endif
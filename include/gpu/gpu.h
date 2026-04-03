#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>
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

GPU_API uint32_t GPU_CALL gpuGetApiVersion(void);
GPU_API const char* GPU_CALL gpuGetLastError(void);
GPU_API int32_t GPU_CALL gpuGetRequiredInstanceExtensions(const char*** extensions, uint32_t* count);
GPU_API int32_t GPU_CALL gpuGetFramebufferSizeGlfw(void* glfwWindow, uint32_t* width, uint32_t* height);

GPU_API VkResult GPU_CALL gpuInstanceCreate(
    const VkInstanceCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUInstance* instance);
GPU_API void GPU_CALL gpuInstanceDestroy(GPUInstance instance);
GPU_API VkInstance GPU_CALL gpuInstanceGetVkHandle(GPUInstance instance);
GPU_API uint32_t GPU_CALL gpuInstanceGetPhysicalDeviceCount(GPUInstance instance);
GPU_API VkResult GPU_CALL gpuInstanceGetPhysicalDevice(
    GPUInstance instance,
    uint32_t index,
    GPUPhysicalDevice* physicalDevice);

GPU_API VkPhysicalDevice GPU_CALL gpuPhysicalDeviceGetVkHandle(GPUPhysicalDevice physicalDevice);
GPU_API GPUInstance GPU_CALL gpuPhysicalDeviceGetInstance(GPUPhysicalDevice physicalDevice);
GPU_API void GPU_CALL gpuPhysicalDeviceRelease(GPUPhysicalDevice physicalDevice);
GPU_API uint32_t GPU_CALL gpuPhysicalDeviceGetDisplayCountKHR(GPUPhysicalDevice physicalDevice);
GPU_API VkResult GPU_CALL gpuPhysicalDeviceGetDisplayKHR(
    GPUPhysicalDevice physicalDevice,
    uint32_t index,
    GPUDisplayKHR* display);

GPU_API VkResult GPU_CALL gpuDeviceCreate(
    GPUPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDevice* device);
GPU_API void GPU_CALL gpuDeviceDestroy(GPUDevice device);
GPU_API VkDevice GPU_CALL gpuDeviceGetVkHandle(GPUDevice device);
GPU_API GPUPhysicalDevice GPU_CALL gpuDeviceGetPhysicalDevice(GPUDevice device);
GPU_API VkResult GPU_CALL gpuDeviceGetQueue(
    GPUDevice device,
    uint32_t familyIndex,
    uint32_t queueIndex,
    GPUQueue* queue);

GPU_API VkQueue GPU_CALL gpuQueueGetVkHandle(GPUQueue queue);
GPU_API GPUDevice GPU_CALL gpuQueueGetDevice(GPUQueue queue);
GPU_API uint32_t GPU_CALL gpuQueueGetFamilyIndex(GPUQueue queue);
GPU_API uint32_t GPU_CALL gpuQueueGetQueueIndex(GPUQueue queue);
GPU_API void GPU_CALL gpuQueueRelease(GPUQueue queue);

GPU_API VkResult GPU_CALL gpuSurfaceCreateGlfw(
    GPUInstance instance,
    void* glfwWindow,
    const VkAllocationCallbacks* allocator,
    GPUSurface* surface);
GPU_API void GPU_CALL gpuSurfaceDestroy(GPUSurface surface);
GPU_API VkSurfaceKHR GPU_CALL gpuSurfaceGetVkHandle(GPUSurface surface);
GPU_API GPUInstance GPU_CALL gpuSurfaceGetInstance(GPUSurface surface);
GPU_API VkSurfaceKHR GPU_CALL gpuSurfaceKHRGetVkHandle(GPUSurface surface);
GPU_API GPUInstance GPU_CALL gpuSurfaceKHRGetInstance(GPUSurface surface);

GPU_API VkResult GPU_CALL gpuDebugReportCallbackEXTCreate(
    GPUInstance instance,
    const VkDebugReportCallbackCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDebugReportCallbackEXT* callback);
GPU_API void GPU_CALL gpuDebugReportCallbackEXTDestroy(GPUDebugReportCallbackEXT callback);
GPU_API VkDebugReportCallbackEXT GPU_CALL gpuDebugReportCallbackEXTGetVkHandle(GPUDebugReportCallbackEXT callback);
GPU_API GPUInstance GPU_CALL gpuDebugReportCallbackEXTGetInstance(GPUDebugReportCallbackEXT callback);

GPU_API VkResult GPU_CALL gpuDebugUtilsMessengerEXTCreate(
    GPUInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDebugUtilsMessengerEXT* messenger);
GPU_API void GPU_CALL gpuDebugUtilsMessengerEXTDestroy(GPUDebugUtilsMessengerEXT messenger);
GPU_API VkDebugUtilsMessengerEXT GPU_CALL gpuDebugUtilsMessengerEXTGetVkHandle(GPUDebugUtilsMessengerEXT messenger);
GPU_API GPUInstance GPU_CALL gpuDebugUtilsMessengerEXTGetInstance(GPUDebugUtilsMessengerEXT messenger);

GPU_API VkResult GPU_CALL gpuSwapchainCreate(
    GPUDevice device,
    GPUSurface surface,
    const VkSwapchainCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSwapchain* swapchain);
GPU_API void GPU_CALL gpuSwapchainDestroy(GPUSwapchain swapchain);
GPU_API VkSwapchainKHR GPU_CALL gpuSwapchainGetVkHandle(GPUSwapchain swapchain);
GPU_API GPUDevice GPU_CALL gpuSwapchainGetDevice(GPUSwapchain swapchain);
GPU_API GPUSurface GPU_CALL gpuSwapchainGetSurface(GPUSwapchain swapchain);
GPU_API VkSwapchainKHR GPU_CALL gpuSwapchainKHRGetVkHandle(GPUSwapchain swapchain);
GPU_API GPUDevice GPU_CALL gpuSwapchainKHRGetDevice(GPUSwapchain swapchain);
GPU_API GPUSurface GPU_CALL gpuSwapchainKHRGetSurface(GPUSwapchain swapchain);

GPU_API VkResult GPU_CALL gpuShaderModuleCreate(
    GPUDevice device,
    const VkShaderModuleCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUShaderModule* shaderModule);
GPU_API void GPU_CALL gpuShaderModuleDestroy(GPUShaderModule shaderModule);
GPU_API VkShaderModule GPU_CALL gpuShaderModuleGetVkHandle(GPUShaderModule shaderModule);
GPU_API GPUDevice GPU_CALL gpuShaderModuleGetDevice(GPUShaderModule shaderModule);

GPU_API VkResult GPU_CALL gpuPipelineLayoutCreate(
    GPUDevice device,
    const VkPipelineLayoutCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipelineLayout* pipelineLayout);
GPU_API void GPU_CALL gpuPipelineLayoutDestroy(GPUPipelineLayout pipelineLayout);
GPU_API VkPipelineLayout GPU_CALL gpuPipelineLayoutGetVkHandle(GPUPipelineLayout pipelineLayout);
GPU_API GPUDevice GPU_CALL gpuPipelineLayoutGetDevice(GPUPipelineLayout pipelineLayout);

GPU_API VkResult GPU_CALL gpuSamplerCreate(
    GPUDevice device,
    const VkSamplerCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSampler* sampler);
GPU_API void GPU_CALL gpuSamplerDestroy(GPUSampler sampler);
GPU_API VkSampler GPU_CALL gpuSamplerGetVkHandle(GPUSampler sampler);
GPU_API GPUDevice GPU_CALL gpuSamplerGetDevice(GPUSampler sampler);

GPU_API VkResult GPU_CALL gpuDescriptorSetLayoutCreate(
    GPUDevice device,
    const VkDescriptorSetLayoutCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDescriptorSetLayout* descriptorSetLayout);
GPU_API void GPU_CALL gpuDescriptorSetLayoutDestroy(GPUDescriptorSetLayout descriptorSetLayout);
GPU_API VkDescriptorSetLayout GPU_CALL gpuDescriptorSetLayoutGetVkHandle(GPUDescriptorSetLayout descriptorSetLayout);
GPU_API GPUDevice GPU_CALL gpuDescriptorSetLayoutGetDevice(GPUDescriptorSetLayout descriptorSetLayout);

GPU_API VkResult GPU_CALL gpuDescriptorPoolCreate(
    GPUDevice device,
    const VkDescriptorPoolCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDescriptorPool* descriptorPool);
GPU_API void GPU_CALL gpuDescriptorPoolDestroy(GPUDescriptorPool descriptorPool);
GPU_API VkDescriptorPool GPU_CALL gpuDescriptorPoolGetVkHandle(GPUDescriptorPool descriptorPool);
GPU_API GPUDevice GPU_CALL gpuDescriptorPoolGetDevice(GPUDescriptorPool descriptorPool);

GPU_API VkResult GPU_CALL gpuDescriptorSetAllocate(
    GPUDescriptorPool descriptorPool,
    const VkDescriptorSetAllocateInfo* allocateInfo,
    GPUDescriptorSet* descriptorSet);
GPU_API void GPU_CALL gpuDescriptorSetDestroy(GPUDescriptorSet descriptorSet);
GPU_API VkDescriptorSet GPU_CALL gpuDescriptorSetGetVkHandle(GPUDescriptorSet descriptorSet);
GPU_API GPUDescriptorPool GPU_CALL gpuDescriptorSetGetPool(GPUDescriptorSet descriptorSet);
GPU_API GPUDevice GPU_CALL gpuDescriptorSetGetDevice(GPUDescriptorSet descriptorSet);

GPU_API VkResult GPU_CALL gpuFramebufferCreate(
    GPUDevice device,
    const VkFramebufferCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUFramebuffer* framebuffer);
GPU_API void GPU_CALL gpuFramebufferDestroy(GPUFramebuffer framebuffer);
GPU_API VkFramebuffer GPU_CALL gpuFramebufferGetVkHandle(GPUFramebuffer framebuffer);
GPU_API GPUDevice GPU_CALL gpuFramebufferGetDevice(GPUFramebuffer framebuffer);

GPU_API VkResult GPU_CALL gpuRenderPassCreate(
    GPUDevice device,
    const VkRenderPassCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPURenderPass* renderPass);
GPU_API void GPU_CALL gpuRenderPassDestroy(GPURenderPass renderPass);
GPU_API VkRenderPass GPU_CALL gpuRenderPassGetVkHandle(GPURenderPass renderPass);
GPU_API GPUDevice GPU_CALL gpuRenderPassGetDevice(GPURenderPass renderPass);

GPU_API VkResult GPU_CALL gpuPipelineCreateGraphics(
    GPUDevice device,
    GPUPipelineCache pipelineCache,
    const VkGraphicsPipelineCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipeline* pipeline);
GPU_API VkResult GPU_CALL gpuPipelineCreateCompute(
    GPUDevice device,
    GPUPipelineCache pipelineCache,
    const VkComputePipelineCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipeline* pipeline);
GPU_API void GPU_CALL gpuPipelineDestroy(GPUPipeline pipeline);
GPU_API VkPipeline GPU_CALL gpuPipelineGetVkHandle(GPUPipeline pipeline);
GPU_API GPUDevice GPU_CALL gpuPipelineGetDevice(GPUPipeline pipeline);

GPU_API VkResult GPU_CALL gpuPipelineCacheCreate(
    GPUDevice device,
    const VkPipelineCacheCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipelineCache* pipelineCache);
GPU_API void GPU_CALL gpuPipelineCacheDestroy(GPUPipelineCache pipelineCache);
GPU_API VkPipelineCache GPU_CALL gpuPipelineCacheGetVkHandle(GPUPipelineCache pipelineCache);
GPU_API GPUDevice GPU_CALL gpuPipelineCacheGetDevice(GPUPipelineCache pipelineCache);

GPU_API VkResult GPU_CALL gpuDescriptorUpdateTemplateCreate(
    GPUDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDescriptorUpdateTemplate* descriptorUpdateTemplate);
GPU_API void GPU_CALL gpuDescriptorUpdateTemplateDestroy(GPUDescriptorUpdateTemplate descriptorUpdateTemplate);
GPU_API VkDescriptorUpdateTemplate GPU_CALL gpuDescriptorUpdateTemplateGetVkHandle(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate);
GPU_API GPUDevice GPU_CALL gpuDescriptorUpdateTemplateGetDevice(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate);
GPU_API VkDescriptorUpdateTemplate GPU_CALL gpuDescriptorUpdateTemplateKHRGetVkHandle(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate);
GPU_API GPUDevice GPU_CALL gpuDescriptorUpdateTemplateKHRGetDevice(
    GPUDescriptorUpdateTemplate descriptorUpdateTemplate);

GPU_API VkResult GPU_CALL gpuSamplerYcbcrConversionCreate(
    GPUDevice device,
    const VkSamplerYcbcrConversionCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSamplerYcbcrConversion* samplerYcbcrConversion);
GPU_API void GPU_CALL gpuSamplerYcbcrConversionDestroy(GPUSamplerYcbcrConversion samplerYcbcrConversion);
GPU_API VkSamplerYcbcrConversion GPU_CALL gpuSamplerYcbcrConversionGetVkHandle(
    GPUSamplerYcbcrConversion samplerYcbcrConversion);
GPU_API GPUDevice GPU_CALL gpuSamplerYcbcrConversionGetDevice(
    GPUSamplerYcbcrConversion samplerYcbcrConversion);
GPU_API VkSamplerYcbcrConversion GPU_CALL gpuSamplerYcbcrConversionKHRGetVkHandle(
    GPUSamplerYcbcrConversion samplerYcbcrConversion);
GPU_API GPUDevice GPU_CALL gpuSamplerYcbcrConversionKHRGetDevice(
    GPUSamplerYcbcrConversion samplerYcbcrConversion);

GPU_API VkResult GPU_CALL gpuPrivateDataSlotCreate(
    GPUDevice device,
    const VkPrivateDataSlotCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPrivateDataSlot* privateDataSlot);
GPU_API void GPU_CALL gpuPrivateDataSlotDestroy(GPUPrivateDataSlot privateDataSlot);
GPU_API VkPrivateDataSlot GPU_CALL gpuPrivateDataSlotGetVkHandle(GPUPrivateDataSlot privateDataSlot);
GPU_API GPUDevice GPU_CALL gpuPrivateDataSlotGetDevice(GPUPrivateDataSlot privateDataSlot);
GPU_API VkPrivateDataSlot GPU_CALL gpuPrivateDataSlotEXTGetVkHandle(GPUPrivateDataSlot privateDataSlot);
GPU_API GPUDevice GPU_CALL gpuPrivateDataSlotEXTGetDevice(GPUPrivateDataSlot privateDataSlot);

GPU_API VkResult GPU_CALL gpuCommandPoolCreate(
    GPUDevice device,
    const VkCommandPoolCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCommandPool* commandPool);
GPU_API void GPU_CALL gpuCommandPoolDestroy(GPUCommandPool commandPool);
GPU_API VkCommandPool GPU_CALL gpuCommandPoolGetVkHandle(GPUCommandPool commandPool);
GPU_API GPUDevice GPU_CALL gpuCommandPoolGetDevice(GPUCommandPool commandPool);

GPU_API VkResult GPU_CALL gpuCommandBufferCreate(
    GPUCommandPool commandPool,
    VkCommandBufferLevel level,
    GPUCommandBuffer* commandBuffer);
GPU_API void GPU_CALL gpuCommandBufferDestroy(GPUCommandBuffer commandBuffer);
GPU_API VkCommandBuffer GPU_CALL gpuCommandBufferGetVkHandle(GPUCommandBuffer commandBuffer);
GPU_API GPUCommandPool GPU_CALL gpuCommandBufferGetCommandPool(GPUCommandBuffer commandBuffer);

GPU_API VkResult GPU_CALL gpuDeviceMemoryCreate(
    GPUDevice device,
    const VkMemoryAllocateInfo* allocateInfo,
    const VkAllocationCallbacks* allocator,
    GPUDeviceMemory* memory);
GPU_API void GPU_CALL gpuDeviceMemoryDestroy(GPUDeviceMemory memory);
GPU_API VkDeviceMemory GPU_CALL gpuDeviceMemoryGetVkHandle(GPUDeviceMemory memory);
GPU_API GPUDevice GPU_CALL gpuDeviceMemoryGetDevice(GPUDeviceMemory memory);

GPU_API VkResult GPU_CALL gpuBufferCreate(
    GPUDevice device,
    const VkBufferCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUBuffer* buffer);
GPU_API void GPU_CALL gpuBufferDestroy(GPUBuffer buffer);
GPU_API VkBuffer GPU_CALL gpuBufferGetVkHandle(GPUBuffer buffer);
GPU_API GPUDevice GPU_CALL gpuBufferGetDevice(GPUBuffer buffer);

GPU_API VkResult GPU_CALL gpuBufferViewCreate(
    GPUDevice device,
    const VkBufferViewCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUBufferView* bufferView);
GPU_API void GPU_CALL gpuBufferViewDestroy(GPUBufferView bufferView);
GPU_API VkBufferView GPU_CALL gpuBufferViewGetVkHandle(GPUBufferView bufferView);
GPU_API GPUDevice GPU_CALL gpuBufferViewGetDevice(GPUBufferView bufferView);

GPU_API VkResult GPU_CALL gpuImageCreate(
    GPUDevice device,
    const VkImageCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUImage* image);
GPU_API void GPU_CALL gpuImageDestroy(GPUImage image);
GPU_API VkImage GPU_CALL gpuImageGetVkHandle(GPUImage image);
GPU_API GPUDevice GPU_CALL gpuImageGetDevice(GPUImage image);

GPU_API VkResult GPU_CALL gpuImageViewCreate(
    GPUDevice device,
    const VkImageViewCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUImageView* imageView);
GPU_API void GPU_CALL gpuImageViewDestroy(GPUImageView imageView);
GPU_API VkImageView GPU_CALL gpuImageViewGetVkHandle(GPUImageView imageView);
GPU_API GPUDevice GPU_CALL gpuImageViewGetDevice(GPUImageView imageView);

GPU_API VkResult GPU_CALL gpuFenceCreate(
    GPUDevice device,
    const VkFenceCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUFence* fence);
GPU_API void GPU_CALL gpuFenceDestroy(GPUFence fence);
GPU_API VkFence GPU_CALL gpuFenceGetVkHandle(GPUFence fence);
GPU_API GPUDevice GPU_CALL gpuFenceGetDevice(GPUFence fence);

GPU_API VkResult GPU_CALL gpuSemaphoreCreate(
    GPUDevice device,
    const VkSemaphoreCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSemaphore* semaphore);
GPU_API void GPU_CALL gpuSemaphoreDestroy(GPUSemaphore semaphore);
GPU_API VkSemaphore GPU_CALL gpuSemaphoreGetVkHandle(GPUSemaphore semaphore);
GPU_API GPUDevice GPU_CALL gpuSemaphoreGetDevice(GPUSemaphore semaphore);

GPU_API VkResult GPU_CALL gpuEventCreate(
    GPUDevice device,
    const VkEventCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUEvent* event);
GPU_API void GPU_CALL gpuEventDestroy(GPUEvent event);
GPU_API VkEvent GPU_CALL gpuEventGetVkHandle(GPUEvent event);
GPU_API GPUDevice GPU_CALL gpuEventGetDevice(GPUEvent event);

GPU_API VkResult GPU_CALL gpuQueryPoolCreate(
    GPUDevice device,
    const VkQueryPoolCreateInfo* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUQueryPool* queryPool);
GPU_API void GPU_CALL gpuQueryPoolDestroy(GPUQueryPool queryPool);
GPU_API VkQueryPool GPU_CALL gpuQueryPoolGetVkHandle(GPUQueryPool queryPool);
GPU_API GPUDevice GPU_CALL gpuQueryPoolGetDevice(GPUQueryPool queryPool);

GPU_API VkResult GPU_CALL gpuValidationCacheEXTCreate(
    GPUDevice device,
    const VkValidationCacheCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUValidationCacheEXT* validationCache);
GPU_API void GPU_CALL gpuValidationCacheEXTDestroy(GPUValidationCacheEXT validationCache);
GPU_API VkValidationCacheEXT GPU_CALL gpuValidationCacheEXTGetVkHandle(GPUValidationCacheEXT validationCache);
GPU_API GPUDevice GPU_CALL gpuValidationCacheEXTGetDevice(GPUValidationCacheEXT validationCache);

GPU_API VkResult GPU_CALL gpuDeferredOperationKHRCreate(
    GPUDevice device,
    const VkAllocationCallbacks* allocator,
    GPUDeferredOperationKHR* deferredOperation);
GPU_API void GPU_CALL gpuDeferredOperationKHRDestroy(GPUDeferredOperationKHR deferredOperation);
GPU_API VkDeferredOperationKHR GPU_CALL gpuDeferredOperationKHRGetVkHandle(GPUDeferredOperationKHR deferredOperation);
GPU_API GPUDevice GPU_CALL gpuDeferredOperationKHRGetDevice(GPUDeferredOperationKHR deferredOperation);

GPU_API VkResult GPU_CALL gpuIndirectCommandsLayoutNVCreate(
    GPUDevice device,
    const VkIndirectCommandsLayoutCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUIndirectCommandsLayoutNV* indirectCommandsLayout);
GPU_API void GPU_CALL gpuIndirectCommandsLayoutNVDestroy(GPUIndirectCommandsLayoutNV indirectCommandsLayout);
GPU_API VkIndirectCommandsLayoutNV GPU_CALL gpuIndirectCommandsLayoutNVGetVkHandle(
    GPUIndirectCommandsLayoutNV indirectCommandsLayout);
GPU_API GPUDevice GPU_CALL gpuIndirectCommandsLayoutNVGetDevice(GPUIndirectCommandsLayoutNV indirectCommandsLayout);

GPU_API VkResult GPU_CALL gpuIndirectCommandsLayoutEXTCreate(
    GPUDevice device,
    const VkIndirectCommandsLayoutCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUIndirectCommandsLayoutEXT* indirectCommandsLayout);
GPU_API void GPU_CALL gpuIndirectCommandsLayoutEXTDestroy(GPUIndirectCommandsLayoutEXT indirectCommandsLayout);
GPU_API VkIndirectCommandsLayoutEXT GPU_CALL gpuIndirectCommandsLayoutEXTGetVkHandle(
    GPUIndirectCommandsLayoutEXT indirectCommandsLayout);
GPU_API GPUDevice GPU_CALL gpuIndirectCommandsLayoutEXTGetDevice(
    GPUIndirectCommandsLayoutEXT indirectCommandsLayout);

GPU_API VkResult GPU_CALL gpuIndirectExecutionSetEXTCreate(
    GPUDevice device,
    const VkIndirectExecutionSetCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUIndirectExecutionSetEXT* indirectExecutionSet);
GPU_API void GPU_CALL gpuIndirectExecutionSetEXTDestroy(GPUIndirectExecutionSetEXT indirectExecutionSet);
GPU_API VkIndirectExecutionSetEXT GPU_CALL gpuIndirectExecutionSetEXTGetVkHandle(
    GPUIndirectExecutionSetEXT indirectExecutionSet);
GPU_API GPUDevice GPU_CALL gpuIndirectExecutionSetEXTGetDevice(GPUIndirectExecutionSetEXT indirectExecutionSet);

GPU_API VkResult GPU_CALL gpuAccelerationStructureKHRCreate(
    GPUDevice device,
    const VkAccelerationStructureCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUAccelerationStructureKHR* accelerationStructure);
GPU_API void GPU_CALL gpuAccelerationStructureKHRDestroy(GPUAccelerationStructureKHR accelerationStructure);
GPU_API VkAccelerationStructureKHR GPU_CALL gpuAccelerationStructureKHRGetVkHandle(
    GPUAccelerationStructureKHR accelerationStructure);
GPU_API GPUDevice GPU_CALL gpuAccelerationStructureKHRGetDevice(GPUAccelerationStructureKHR accelerationStructure);

GPU_API VkResult GPU_CALL gpuAccelerationStructureNVCreate(
    GPUDevice device,
    const VkAccelerationStructureCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUAccelerationStructureNV* accelerationStructure);
GPU_API void GPU_CALL gpuAccelerationStructureNVDestroy(GPUAccelerationStructureNV accelerationStructure);
GPU_API VkAccelerationStructureNV GPU_CALL gpuAccelerationStructureNVGetVkHandle(
    GPUAccelerationStructureNV accelerationStructure);
GPU_API GPUDevice GPU_CALL gpuAccelerationStructureNVGetDevice(GPUAccelerationStructureNV accelerationStructure);

GPU_API VkResult GPU_CALL gpuMicromapEXTCreate(
    GPUDevice device,
    const VkMicromapCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUMicromapEXT* micromap);
GPU_API void GPU_CALL gpuMicromapEXTDestroy(GPUMicromapEXT micromap);
GPU_API VkMicromapEXT GPU_CALL gpuMicromapEXTGetVkHandle(GPUMicromapEXT micromap);
GPU_API GPUDevice GPU_CALL gpuMicromapEXTGetDevice(GPUMicromapEXT micromap);
#ifdef FUCHSIA
GPU_API VkResult GPU_CALL gpuBufferCollectionFUCHSIACreate(
    GPUDevice device,
    const VkBufferCollectionCreateInfoFUCHSIA* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUBufferCollectionFUCHSIA* collection);
GPU_API void GPU_CALL gpuBufferCollectionFUCHSIADestroy(GPUBufferCollectionFUCHSIA collection);
GPU_API VkBufferCollectionFUCHSIA GPU_CALL gpuBufferCollectionFUCHSIAGetVkHandle(GPUBufferCollectionFUCHSIA collection);
GPU_API GPUDevice GPU_CALL gpuBufferCollectionFUCHSIAGetDevice(GPUBufferCollectionFUCHSIA collection);
#endif
GPU_API VkResult GPU_CALL gpuPipelineBinaryKHRCreate(
    GPUDevice device,
    const VkPipelineBinaryCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUPipelineBinaryKHR* pipelineBinary);
GPU_API void GPU_CALL gpuPipelineBinaryKHRDestroy(GPUPipelineBinaryKHR pipelineBinary);
GPU_API VkPipelineBinaryKHR GPU_CALL gpuPipelineBinaryKHRGetVkHandle(GPUPipelineBinaryKHR pipelineBinary);
GPU_API GPUDevice GPU_CALL gpuPipelineBinaryKHRGetDevice(GPUPipelineBinaryKHR pipelineBinary);

GPU_API VkResult GPU_CALL gpuCuModuleNVXCreate(
    GPUDevice device,
    const VkCuModuleCreateInfoNVX* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCuModuleNVX* cuModule);
GPU_API void GPU_CALL gpuCuModuleNVXDestroy(GPUCuModuleNVX cuModule);
GPU_API VkCuModuleNVX GPU_CALL gpuCuModuleNVXGetVkHandle(GPUCuModuleNVX cuModule);
GPU_API GPUDevice GPU_CALL gpuCuModuleNVXGetDevice(GPUCuModuleNVX cuModule);

GPU_API VkResult GPU_CALL gpuCuFunctionNVXCreate(
    GPUDevice device,
    const VkCuFunctionCreateInfoNVX* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCuFunctionNVX* cuFunction);
GPU_API void GPU_CALL gpuCuFunctionNVXDestroy(GPUCuFunctionNVX cuFunction);
GPU_API VkCuFunctionNVX GPU_CALL gpuCuFunctionNVXGetVkHandle(GPUCuFunctionNVX cuFunction);
GPU_API GPUDevice GPU_CALL gpuCuFunctionNVXGetDevice(GPUCuFunctionNVX cuFunction);

GPU_API VkResult GPU_CALL gpuOpticalFlowSessionNVCreate(
    GPUDevice device,
    const VkOpticalFlowSessionCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUOpticalFlowSessionNV* session);
GPU_API void GPU_CALL gpuOpticalFlowSessionNVDestroy(GPUOpticalFlowSessionNV session);
GPU_API VkOpticalFlowSessionNV GPU_CALL gpuOpticalFlowSessionNVGetVkHandle(GPUOpticalFlowSessionNV session);
GPU_API GPUDevice GPU_CALL gpuOpticalFlowSessionNVGetDevice(GPUOpticalFlowSessionNV session);

GPU_API VkResult GPU_CALL gpuShaderEXTCreate(
    GPUDevice device,
    const VkShaderCreateInfoEXT* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUShaderEXT* shader);
GPU_API void GPU_CALL gpuShaderEXTDestroy(GPUShaderEXT shader);
GPU_API VkShaderEXT GPU_CALL gpuShaderEXTGetVkHandle(GPUShaderEXT shader);
GPU_API GPUDevice GPU_CALL gpuShaderEXTGetDevice(GPUShaderEXT shader);

GPU_API VkResult GPU_CALL gpuTensorARMCreate(
    GPUDevice device,
    const VkTensorCreateInfoARM* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUTensorARM* tensor);
GPU_API void GPU_CALL gpuTensorARMDestroy(GPUTensorARM tensor);
GPU_API VkTensorARM GPU_CALL gpuTensorARMGetVkHandle(GPUTensorARM tensor);
GPU_API GPUDevice GPU_CALL gpuTensorARMGetDevice(GPUTensorARM tensor);

GPU_API VkResult GPU_CALL gpuTensorViewARMCreate(
    GPUDevice device,
    const VkTensorViewCreateInfoARM* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUTensorViewARM* tensorView);
GPU_API void GPU_CALL gpuTensorViewARMDestroy(GPUTensorViewARM tensorView);
GPU_API VkTensorViewARM GPU_CALL gpuTensorViewARMGetVkHandle(GPUTensorViewARM tensorView);
GPU_API GPUDevice GPU_CALL gpuTensorViewARMGetDevice(GPUTensorViewARM tensorView);

GPU_API VkResult GPU_CALL gpuDataGraphPipelineSessionARMCreate(
    GPUDevice device,
    const VkDataGraphPipelineSessionCreateInfoARM* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUDataGraphPipelineSessionARM* session);
GPU_API void GPU_CALL gpuDataGraphPipelineSessionARMDestroy(GPUDataGraphPipelineSessionARM session);
GPU_API VkDataGraphPipelineSessionARM GPU_CALL gpuDataGraphPipelineSessionARMGetVkHandle(
    GPUDataGraphPipelineSessionARM session);
GPU_API GPUDevice GPU_CALL gpuDataGraphPipelineSessionARMGetDevice(GPUDataGraphPipelineSessionARM session);

GPU_API VkDisplayKHR GPU_CALL gpuDisplayKHRGetVkHandle(GPUDisplayKHR display);
GPU_API GPUPhysicalDevice GPU_CALL gpuDisplayKHRGetPhysicalDevice(GPUDisplayKHR display);
GPU_API uint32_t GPU_CALL gpuDisplayKHRGetModeCountKHR(GPUDisplayKHR display);
GPU_API VkResult GPU_CALL gpuDisplayKHRGetModeKHR(
    GPUDisplayKHR display,
    uint32_t index,
    GPUDisplayModeKHR* displayMode);
GPU_API void GPU_CALL gpuDisplayKHRRelease(GPUDisplayKHR display);

GPU_API VkDisplayModeKHR GPU_CALL gpuDisplayModeKHRGetVkHandle(GPUDisplayModeKHR displayMode);
GPU_API GPUDisplayKHR GPU_CALL gpuDisplayModeKHRGetDisplayKHR(GPUDisplayModeKHR displayMode);
GPU_API GPUPhysicalDevice GPU_CALL gpuDisplayModeKHRGetPhysicalDevice(GPUDisplayModeKHR displayMode);
GPU_API void GPU_CALL gpuDisplayModeKHRRelease(GPUDisplayModeKHR displayMode);

GPU_API VkResult GPU_CALL gpuVideoSessionKHRCreate(
    GPUDevice device,
    const VkVideoSessionCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUVideoSessionKHR* videoSession);
GPU_API void GPU_CALL gpuVideoSessionKHRDestroy(GPUVideoSessionKHR videoSession);
GPU_API VkVideoSessionKHR GPU_CALL gpuVideoSessionKHRGetVkHandle(GPUVideoSessionKHR videoSession);
GPU_API GPUDevice GPU_CALL gpuVideoSessionKHRGetDevice(GPUVideoSessionKHR videoSession);

GPU_API VkResult GPU_CALL gpuVideoSessionParametersKHRCreate(
    GPUDevice device,
    const VkVideoSessionParametersCreateInfoKHR* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUVideoSessionParametersKHR* videoSessionParameters);
GPU_API void GPU_CALL gpuVideoSessionParametersKHRDestroy(GPUVideoSessionParametersKHR videoSessionParameters);
GPU_API VkVideoSessionParametersKHR GPU_CALL gpuVideoSessionParametersKHRGetVkHandle(
    GPUVideoSessionParametersKHR videoSessionParameters);
GPU_API GPUDevice GPU_CALL gpuVideoSessionParametersKHRGetDevice(
    GPUVideoSessionParametersKHR videoSessionParameters);
#if defined(VK_ENABLE_SCISYNC)
GPU_API VkResult GPU_CALL gpuSemaphoreSciSyncPoolNVCreate(
    GPUDevice device,
    const VkSemaphoreSciSyncPoolCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUSemaphoreSciSyncPoolNV* semaphoreSciSyncPool);
GPU_API void GPU_CALL gpuSemaphoreSciSyncPoolNVDestroy(GPUSemaphoreSciSyncPoolNV semaphoreSciSyncPool);
GPU_API VkSemaphoreSciSyncPoolNV GPU_CALL gpuSemaphoreSciSyncPoolNVGetVkHandle(
    GPUSemaphoreSciSyncPoolNV semaphoreSciSyncPool);
GPU_API GPUDevice GPU_CALL gpuSemaphoreSciSyncPoolNVGetDevice(GPUSemaphoreSciSyncPoolNV semaphoreSciSyncPool);
#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)
GPU_API VkResult GPU_CALL gpuCudaModuleNVCreate(
    GPUDevice device,
    const VkCudaModuleCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCudaModuleNV* cudaModule);
GPU_API void GPU_CALL gpuCudaModuleNVDestroy(GPUCudaModuleNV cudaModule);
GPU_API VkCudaModuleNV GPU_CALL gpuCudaModuleNVGetVkHandle(GPUCudaModuleNV cudaModule);
GPU_API GPUDevice GPU_CALL gpuCudaModuleNVGetDevice(GPUCudaModuleNV cudaModule);

GPU_API VkResult GPU_CALL gpuCudaFunctionNVCreate(
    GPUDevice device,
    const VkCudaFunctionCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUCudaFunctionNV* cudaFunction);
GPU_API void GPU_CALL gpuCudaFunctionNVDestroy(GPUCudaFunctionNV cudaFunction);
GPU_API VkCudaFunctionNV GPU_CALL gpuCudaFunctionNVGetVkHandle(GPUCudaFunctionNV cudaFunction);
GPU_API GPUDevice GPU_CALL gpuCudaFunctionNVGetDevice(GPUCudaFunctionNV cudaFunction);
#endif

GPU_API VkResult GPU_CALL gpuExternalComputeQueueNVCreate(
    GPUDevice device,
    const VkExternalComputeQueueCreateInfoNV* createInfo,
    const VkAllocationCallbacks* allocator,
    GPUExternalComputeQueueNV* externalComputeQueue);
GPU_API void GPU_CALL gpuExternalComputeQueueNVDestroy(GPUExternalComputeQueueNV externalComputeQueue);
GPU_API VkExternalComputeQueueNV GPU_CALL gpuExternalComputeQueueNVGetVkHandle(
    GPUExternalComputeQueueNV externalComputeQueue);
GPU_API GPUDevice GPU_CALL gpuExternalComputeQueueNVGetDevice(GPUExternalComputeQueueNV externalComputeQueue);

GPU_API VkResult GPU_CALL gpuPerformanceConfigurationINTELAcquire(
    GPUDevice device,
    const VkPerformanceConfigurationAcquireInfoINTEL* acquireInfo,
    GPUPerformanceConfigurationINTEL* configuration);
GPU_API void GPU_CALL gpuPerformanceConfigurationINTELRelease(GPUPerformanceConfigurationINTEL configuration);
GPU_API VkPerformanceConfigurationINTEL GPU_CALL gpuPerformanceConfigurationINTELGetVkHandle(
    GPUPerformanceConfigurationINTEL configuration);
GPU_API GPUDevice GPU_CALL gpuPerformanceConfigurationINTELGetDevice(GPUPerformanceConfigurationINTEL configuration);

#include "gpu/gpu_vulkan.h"

#ifdef __cplusplus
}
#endif

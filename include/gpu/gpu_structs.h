#pragma once

/*
 * Minimal GPU‑named structures that mirror the Vulkan creation‑info structs.
 * They contain only the fields needed for the README example and are
 * directly forwarded to the underlying Vulkan loader via the GPU wrapper.
 * No Vulkan‑prefixed symbols appear in user code.
 */
#include <stdint.h>
#include <vulkan/vulkan.h>
#if defined(VK_ENABLE_BETA_EXTENSIONS)
#include <vulkan/vulkan_beta.h>
#endif

/* Structure type identifiers – values match the Vulkan spec. */

// GPU‑prefixed aliases for Vulkan creation‑info structs. These are
// simple typedefs so they are binary compatible with the original Vulkan types.
// They let user code avoid any `Vk` symbols while still passing the
// required fields to the underlying Vulkan loader.

typedef VkResult                       GpuResult;
typedef VkAllocationCallbacks          GpuAllocationCallbacks;
typedef VkBool32                       GpuBool32;
typedef VkCommandBufferLevel           GpuCommandBufferLevel;
typedef VkShaderStageFlagBits          GpuShaderStageFlagBits;

typedef VkSwapchainCreateInfoKHR           GpuSwapchainCreateInfoKHR;
typedef VkShaderModuleCreateInfo           GpuShaderModuleCreateInfo;
typedef VkPipelineLayoutCreateInfo         GpuPipelineLayoutCreateInfo;
typedef VkSamplerCreateInfo                GpuSamplerCreateInfo;
typedef VkDescriptorSetLayoutCreateInfo    GpuDescriptorSetLayoutCreateInfo;
typedef VkDescriptorPoolCreateInfo         GpuDescriptorPoolCreateInfo;
typedef VkDescriptorSetAllocateInfo        GpuDescriptorSetAllocateInfo;
typedef VkFramebufferCreateInfo            GpuFramebufferCreateInfo;
typedef VkRenderPassCreateInfo             GpuRenderPassCreateInfo;
typedef VkGraphicsPipelineCreateInfo       GpuGraphicsPipelineCreateInfo;
typedef VkComputePipelineCreateInfo        GpuComputePipelineCreateInfo;
typedef VkPipelineCacheCreateInfo          GpuPipelineCacheCreateInfo;
typedef VkDescriptorUpdateTemplateCreateInfo GpuDescriptorUpdateTemplateCreateInfo;
typedef VkSamplerYcbcrConversionCreateInfo GpuSamplerYcbcrConversionCreateInfo;
typedef VkPrivateDataSlotCreateInfo        GpuPrivateDataSlotCreateInfo;
typedef VkCommandPoolCreateInfo            GpuCommandPoolCreateInfo;
typedef VkBufferCreateInfo                 GpuBufferCreateInfo;
typedef VkBufferViewCreateInfo             GpuBufferViewCreateInfo;
typedef VkImageCreateInfo                  GpuImageCreateInfo;
typedef VkImageViewCreateInfo              GpuImageViewCreateInfo;
typedef VkFenceCreateInfo                  GpuFenceCreateInfo;
typedef VkSemaphoreCreateInfo              GpuSemaphoreCreateInfo;
typedef VkEventCreateInfo                  GpuEventCreateInfo;
typedef VkQueryPoolCreateInfo              GpuQueryPoolCreateInfo;
typedef VkMemoryAllocateInfo               GpuMemoryAllocateInfo;
typedef VkValidationCacheCreateInfoEXT     GpuValidationCacheCreateInfoEXT;
typedef VkIndirectCommandsLayoutCreateInfoNV  GpuIndirectCommandsLayoutCreateInfoNV;
typedef VkIndirectCommandsLayoutCreateInfoEXT GpuIndirectCommandsLayoutCreateInfoEXT;
typedef VkIndirectExecutionSetCreateInfoEXT   GpuIndirectExecutionSetCreateInfoEXT;
typedef VkAccelerationStructureCreateInfoKHR  GpuAccelerationStructureCreateInfoKHR;
typedef VkAccelerationStructureCreateInfoNV   GpuAccelerationStructureCreateInfoNV;
typedef VkMicromapCreateInfoEXT            GpuMicromapCreateInfoEXT;
#ifdef VK_USE_PLATFORM_FUCHSIA
typedef VkBufferCollectionCreateInfoFUCHSIA GpuBufferCollectionCreateInfoFUCHSIA;
#endif
typedef VkPipelineBinaryCreateInfoKHR      GpuPipelineBinaryCreateInfoKHR;
typedef VkCuModuleCreateInfoNVX            GpuCuModuleCreateInfoNVX;
typedef VkCuFunctionCreateInfoNVX          GpuCuFunctionCreateInfoNVX;
typedef VkOpticalFlowSessionCreateInfoNV   GpuOpticalFlowSessionCreateInfoNV;
typedef VkShaderCreateInfoEXT              GpuShaderCreateInfoEXT;
typedef VkTensorCreateInfoARM              GpuTensorCreateInfoARM;
typedef VkTensorViewCreateInfoARM          GpuTensorViewCreateInfoARM;
typedef VkDataGraphPipelineSessionCreateInfoARM GpuDataGraphPipelineSessionCreateInfoARM;
typedef VkVideoSessionCreateInfoKHR        GpuVideoSessionCreateInfoKHR;
typedef VkVideoSessionParametersCreateInfoKHR GpuVideoSessionParametersCreateInfoKHR;
#ifdef VK_ENABLE_SCISYNC
typedef VkSemaphoreSciSyncPoolCreateInfoNV GpuSemaphoreSciSyncPoolCreateInfoNV;
#endif
#ifdef VK_ENABLE_BETA_EXTENSIONS
typedef VkCudaModuleCreateInfoNV           GpuCudaModuleCreateInfoNV;
typedef VkCudaFunctionCreateInfoNV         GpuCudaFunctionCreateInfoNV;
#endif
typedef VkExternalComputeQueueCreateInfoNV GpuExternalComputeQueueCreateInfoNV;
typedef VkPerformanceConfigurationAcquireInfoINTEL GpuPerformanceConfigurationAcquireInfoINTEL;
typedef VkDebugReportCallbackCreateInfoEXT GpuDebugReportCallbackCreateInfoEXT;
typedef VkDebugUtilsMessengerCreateInfoEXT GpuDebugUtilsMessengerCreateInfoEXT;

#define GPU_STRUCTURE_TYPE_APPLICATION_INFO        0u
#define GPU_STRUCTURE_TYPE_INSTANCE_CREATE_INFO    1u
#define GPU_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO 2u
#define GPU_STRUCTURE_TYPE_DEVICE_CREATE_INFO      3u

typedef struct GpuApplicationInfo {
    uint32_t    sType;
    const char* pApplicationName;
    uint32_t    applicationVersion;
    const char* pEngineName;
    uint32_t    engineVersion;
    uint32_t    apiVersion;
} GpuApplicationInfo;

typedef struct GpuInstanceCreateInfo {
    uint32_t    sType;
    const GpuApplicationInfo* pApplicationInfo;
    uint32_t    enabledExtensionCount;
    const char* const* ppEnabledExtensionNames;
} GpuInstanceCreateInfo;

typedef struct GpuDeviceQueueCreateInfo {
    uint32_t sType;
    uint32_t queueFamilyIndex;
    uint32_t queueCount;
    const float* pQueuePriorities;
} GpuDeviceQueueCreateInfo;

typedef struct GpuDeviceCreateInfo {
    uint32_t sType;
    uint32_t queueCreateInfoCount;
    const GpuDeviceQueueCreateInfo* pQueueCreateInfos;
} GpuDeviceCreateInfo;
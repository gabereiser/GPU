using System.Runtime.InteropServices;

namespace GPU;

internal unsafe readonly struct NativeApi
{
    public NativeApi(nint moduleHandle)
    {
        ModuleHandle = moduleHandle;

        gpuGetApiVersion = (delegate* unmanaged<uint>)Load(nameof(gpuGetApiVersion));
        gpuGetLastError = (delegate* unmanaged<byte*>)Load(nameof(gpuGetLastError));
        gpuGetRequiredInstanceExtensions = (delegate* unmanaged<byte***, uint*, int>)Load(nameof(gpuGetRequiredInstanceExtensions));
        gpuGetFramebufferSizeGlfw = (delegate* unmanaged<nint, uint*, uint*, int>)Load(nameof(gpuGetFramebufferSizeGlfw));

        gpuInstanceCreate = (delegate* unmanaged<void*, void*, nint*, Result>)Load(nameof(gpuInstanceCreate));
        gpuInstanceDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuInstanceDestroy));
        gpuInstanceGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuInstanceGetVkHandle));
        gpuInstanceGetPhysicalDeviceCount = (delegate* unmanaged<nint, uint>)Load(nameof(gpuInstanceGetPhysicalDeviceCount));
        gpuInstanceGetPhysicalDevice = (delegate* unmanaged<nint, uint, nint*, Result>)Load(nameof(gpuInstanceGetPhysicalDevice));

        gpuPhysicalDeviceGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuPhysicalDeviceGetVkHandle));
        gpuPhysicalDeviceGetInstance = (delegate* unmanaged<nint, nint>)Load(nameof(gpuPhysicalDeviceGetInstance));
        gpuPhysicalDeviceRelease = (delegate* unmanaged<nint, void>)Load(nameof(gpuPhysicalDeviceRelease));
        gpuPhysicalDeviceGetDisplayCountKHR = (delegate* unmanaged<nint, uint>)Load(nameof(gpuPhysicalDeviceGetDisplayCountKHR));
        gpuPhysicalDeviceGetDisplayKHR = (delegate* unmanaged<nint, uint, nint*, Result>)Load(nameof(gpuPhysicalDeviceGetDisplayKHR));

        gpuDeviceCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuDeviceCreate));
        gpuDeviceDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDeviceDestroy));
        gpuDeviceGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDeviceGetVkHandle));
        gpuDeviceGetPhysicalDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDeviceGetPhysicalDevice));
        gpuDeviceGetQueue = (delegate* unmanaged<nint, uint, uint, nint*, Result>)Load(nameof(gpuDeviceGetQueue));

        gpuQueueGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuQueueGetVkHandle));
        gpuQueueGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuQueueGetDevice));
        gpuQueueGetFamilyIndex = (delegate* unmanaged<nint, uint>)Load(nameof(gpuQueueGetFamilyIndex));
        gpuQueueGetQueueIndex = (delegate* unmanaged<nint, uint>)Load(nameof(gpuQueueGetQueueIndex));
        gpuQueueRelease = (delegate* unmanaged<nint, void>)Load(nameof(gpuQueueRelease));

        gpuSurfaceCreateGlfw = (delegate* unmanaged<nint, nint, void*, nint*, Result>)Load(nameof(gpuSurfaceCreateGlfw));
        gpuSurfaceDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuSurfaceDestroy));
        gpuSurfaceGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSurfaceGetVkHandle));
        gpuSurfaceGetInstance = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSurfaceGetInstance));
        gpuSurfaceKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSurfaceKHRGetVkHandle));
        gpuSurfaceKHRGetInstance = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSurfaceKHRGetInstance));

        gpuDebugReportCallbackEXTCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuDebugReportCallbackEXTCreate));
        gpuDebugReportCallbackEXTDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDebugReportCallbackEXTDestroy));
        gpuDebugReportCallbackEXTGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDebugReportCallbackEXTGetVkHandle));
        gpuDebugReportCallbackEXTGetInstance = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDebugReportCallbackEXTGetInstance));

        gpuDebugUtilsMessengerEXTCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuDebugUtilsMessengerEXTCreate));
        gpuDebugUtilsMessengerEXTDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDebugUtilsMessengerEXTDestroy));
        gpuDebugUtilsMessengerEXTGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDebugUtilsMessengerEXTGetVkHandle));
        gpuDebugUtilsMessengerEXTGetInstance = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDebugUtilsMessengerEXTGetInstance));

        gpuSwapchainCreate = (delegate* unmanaged<nint, nint, void*, void*, nint*, Result>)Load(nameof(gpuSwapchainCreate));
        gpuSwapchainDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuSwapchainDestroy));
        gpuSwapchainGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSwapchainGetVkHandle));
        gpuSwapchainGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSwapchainGetDevice));
        gpuSwapchainGetSurface = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSwapchainGetSurface));
        gpuSwapchainKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSwapchainKHRGetVkHandle));
        gpuSwapchainKHRGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSwapchainKHRGetDevice));
        gpuSwapchainKHRGetSurface = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSwapchainKHRGetSurface));

        gpuShaderModuleCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuShaderModuleCreate));
        gpuShaderModuleDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuShaderModuleDestroy));
        gpuShaderModuleGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuShaderModuleGetVkHandle));
        gpuShaderModuleGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuShaderModuleGetDevice));

        gpuPipelineLayoutCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuPipelineLayoutCreate));
        gpuPipelineLayoutDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuPipelineLayoutDestroy));
        gpuPipelineLayoutGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuPipelineLayoutGetVkHandle));
        gpuPipelineLayoutGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuPipelineLayoutGetDevice));

        gpuSamplerCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuSamplerCreate));
        gpuSamplerDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuSamplerDestroy));
        gpuSamplerGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSamplerGetVkHandle));
        gpuSamplerGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSamplerGetDevice));

        gpuDescriptorSetLayoutCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuDescriptorSetLayoutCreate));
        gpuDescriptorSetLayoutDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDescriptorSetLayoutDestroy));
        gpuDescriptorSetLayoutGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDescriptorSetLayoutGetVkHandle));
        gpuDescriptorSetLayoutGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDescriptorSetLayoutGetDevice));

        gpuDescriptorPoolCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuDescriptorPoolCreate));
        gpuDescriptorPoolDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDescriptorPoolDestroy));
        gpuDescriptorPoolGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDescriptorPoolGetVkHandle));
        gpuDescriptorPoolGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDescriptorPoolGetDevice));

        gpuDescriptorSetAllocate = (delegate* unmanaged<nint, void*, nint*, Result>)Load(nameof(gpuDescriptorSetAllocate));
        gpuDescriptorSetDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDescriptorSetDestroy));
        gpuDescriptorSetGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDescriptorSetGetVkHandle));
        gpuDescriptorSetGetPool = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDescriptorSetGetPool));
        gpuDescriptorSetGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDescriptorSetGetDevice));

        gpuFramebufferCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuFramebufferCreate));
        gpuFramebufferDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuFramebufferDestroy));
        gpuFramebufferGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuFramebufferGetVkHandle));
        gpuFramebufferGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuFramebufferGetDevice));

        gpuRenderPassCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuRenderPassCreate));
        gpuRenderPassDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuRenderPassDestroy));
        gpuRenderPassGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuRenderPassGetVkHandle));
        gpuRenderPassGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuRenderPassGetDevice));

        gpuPipelineCreateGraphics = (delegate* unmanaged<nint, nint, void*, void*, nint*, Result>)Load(nameof(gpuPipelineCreateGraphics));
        gpuPipelineCreateCompute = (delegate* unmanaged<nint, nint, void*, void*, nint*, Result>)Load(nameof(gpuPipelineCreateCompute));
        gpuPipelineDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuPipelineDestroy));
        gpuPipelineGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuPipelineGetVkHandle));
        gpuPipelineGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuPipelineGetDevice));

        gpuPipelineCacheCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuPipelineCacheCreate));
        gpuPipelineCacheDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuPipelineCacheDestroy));
        gpuPipelineCacheGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuPipelineCacheGetVkHandle));
        gpuPipelineCacheGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuPipelineCacheGetDevice));

        gpuDescriptorUpdateTemplateCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuDescriptorUpdateTemplateCreate));
        gpuDescriptorUpdateTemplateDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDescriptorUpdateTemplateDestroy));
        gpuDescriptorUpdateTemplateGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDescriptorUpdateTemplateGetVkHandle));
        gpuDescriptorUpdateTemplateGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDescriptorUpdateTemplateGetDevice));
        gpuDescriptorUpdateTemplateKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDescriptorUpdateTemplateKHRGetVkHandle));
        gpuDescriptorUpdateTemplateKHRGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDescriptorUpdateTemplateKHRGetDevice));

        gpuSamplerYcbcrConversionCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuSamplerYcbcrConversionCreate));
        gpuSamplerYcbcrConversionDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuSamplerYcbcrConversionDestroy));
        gpuSamplerYcbcrConversionGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSamplerYcbcrConversionGetVkHandle));
        gpuSamplerYcbcrConversionGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSamplerYcbcrConversionGetDevice));
        gpuSamplerYcbcrConversionKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSamplerYcbcrConversionKHRGetVkHandle));
        gpuSamplerYcbcrConversionKHRGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSamplerYcbcrConversionKHRGetDevice));

        gpuPrivateDataSlotCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuPrivateDataSlotCreate));
        gpuPrivateDataSlotDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuPrivateDataSlotDestroy));
        gpuPrivateDataSlotGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuPrivateDataSlotGetVkHandle));
        gpuPrivateDataSlotGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuPrivateDataSlotGetDevice));
        gpuPrivateDataSlotEXTGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuPrivateDataSlotEXTGetVkHandle));
        gpuPrivateDataSlotEXTGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuPrivateDataSlotEXTGetDevice));

        gpuCommandPoolCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuCommandPoolCreate));
        gpuCommandPoolDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuCommandPoolDestroy));
        gpuCommandPoolGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuCommandPoolGetVkHandle));
        gpuCommandPoolGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuCommandPoolGetDevice));

        gpuCommandBufferCreate = (delegate* unmanaged<nint, int, nint*, Result>)Load(nameof(gpuCommandBufferCreate));
        gpuCommandBufferDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuCommandBufferDestroy));
        gpuCommandBufferGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuCommandBufferGetVkHandle));
        gpuCommandBufferGetCommandPool = (delegate* unmanaged<nint, nint>)Load(nameof(gpuCommandBufferGetCommandPool));

        gpuDeviceMemoryCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuDeviceMemoryCreate));
        gpuDeviceMemoryDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDeviceMemoryDestroy));
        gpuDeviceMemoryGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDeviceMemoryGetVkHandle));
        gpuDeviceMemoryGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDeviceMemoryGetDevice));

        gpuBufferCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuBufferCreate));
        gpuBufferDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuBufferDestroy));
        gpuBufferGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuBufferGetVkHandle));
        gpuBufferGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuBufferGetDevice));

        gpuBufferViewCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuBufferViewCreate));
        gpuBufferViewDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuBufferViewDestroy));
        gpuBufferViewGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuBufferViewGetVkHandle));
        gpuBufferViewGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuBufferViewGetDevice));

        gpuImageCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuImageCreate));
        gpuImageDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuImageDestroy));
        gpuImageGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuImageGetVkHandle));
        gpuImageGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuImageGetDevice));

        gpuImageViewCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuImageViewCreate));
        gpuImageViewDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuImageViewDestroy));
        gpuImageViewGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuImageViewGetVkHandle));
        gpuImageViewGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuImageViewGetDevice));

        gpuFenceCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuFenceCreate));
        gpuFenceDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuFenceDestroy));
        gpuFenceGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuFenceGetVkHandle));
        gpuFenceGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuFenceGetDevice));

        gpuSemaphoreCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuSemaphoreCreate));
        gpuSemaphoreDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuSemaphoreDestroy));
        gpuSemaphoreGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSemaphoreGetVkHandle));
        gpuSemaphoreGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSemaphoreGetDevice));

        gpuEventCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuEventCreate));
        gpuEventDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuEventDestroy));
        gpuEventGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuEventGetVkHandle));
        gpuEventGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuEventGetDevice));

        gpuQueryPoolCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuQueryPoolCreate));
        gpuQueryPoolDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuQueryPoolDestroy));
        gpuQueryPoolGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuQueryPoolGetVkHandle));
        gpuQueryPoolGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuQueryPoolGetDevice));

        gpuValidationCacheEXTCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuValidationCacheEXTCreate));
        gpuValidationCacheEXTDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuValidationCacheEXTDestroy));
        gpuValidationCacheEXTGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuValidationCacheEXTGetVkHandle));
        gpuValidationCacheEXTGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuValidationCacheEXTGetDevice));

        gpuDeferredOperationKHRCreate = (delegate* unmanaged<nint, void*, nint*, Result>)Load(nameof(gpuDeferredOperationKHRCreate));
        gpuDeferredOperationKHRDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDeferredOperationKHRDestroy));
        gpuDeferredOperationKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDeferredOperationKHRGetVkHandle));
        gpuDeferredOperationKHRGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDeferredOperationKHRGetDevice));

        gpuIndirectCommandsLayoutNVCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuIndirectCommandsLayoutNVCreate));
        gpuIndirectCommandsLayoutNVDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuIndirectCommandsLayoutNVDestroy));
        gpuIndirectCommandsLayoutNVGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuIndirectCommandsLayoutNVGetVkHandle));
        gpuIndirectCommandsLayoutNVGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuIndirectCommandsLayoutNVGetDevice));

        gpuIndirectCommandsLayoutEXTCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuIndirectCommandsLayoutEXTCreate));
        gpuIndirectCommandsLayoutEXTDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuIndirectCommandsLayoutEXTDestroy));
        gpuIndirectCommandsLayoutEXTGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuIndirectCommandsLayoutEXTGetVkHandle));
        gpuIndirectCommandsLayoutEXTGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuIndirectCommandsLayoutEXTGetDevice));

        gpuIndirectExecutionSetEXTCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuIndirectExecutionSetEXTCreate));
        gpuIndirectExecutionSetEXTDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuIndirectExecutionSetEXTDestroy));
        gpuIndirectExecutionSetEXTGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuIndirectExecutionSetEXTGetVkHandle));
        gpuIndirectExecutionSetEXTGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuIndirectExecutionSetEXTGetDevice));

        gpuAccelerationStructureKHRCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuAccelerationStructureKHRCreate));
        gpuAccelerationStructureKHRDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuAccelerationStructureKHRDestroy));
        gpuAccelerationStructureKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuAccelerationStructureKHRGetVkHandle));
        gpuAccelerationStructureKHRGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuAccelerationStructureKHRGetDevice));

        gpuAccelerationStructureNVCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuAccelerationStructureNVCreate));
        gpuAccelerationStructureNVDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuAccelerationStructureNVDestroy));
        gpuAccelerationStructureNVGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuAccelerationStructureNVGetVkHandle));
        gpuAccelerationStructureNVGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuAccelerationStructureNVGetDevice));

        gpuMicromapEXTCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuMicromapEXTCreate));
        gpuMicromapEXTDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuMicromapEXTDestroy));
        gpuMicromapEXTGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuMicromapEXTGetVkHandle));
        gpuMicromapEXTGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuMicromapEXTGetDevice));

        gpuBufferCollectionFUCHSIACreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuBufferCollectionFUCHSIACreate));
        gpuBufferCollectionFUCHSIADestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuBufferCollectionFUCHSIADestroy));
        gpuBufferCollectionFUCHSIAGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuBufferCollectionFUCHSIAGetVkHandle));
        gpuBufferCollectionFUCHSIAGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuBufferCollectionFUCHSIAGetDevice));

        gpuPerformanceConfigurationINTELAcquire = (delegate* unmanaged<nint, void*, nint*, Result>)Load(nameof(gpuPerformanceConfigurationINTELAcquire));
        gpuPerformanceConfigurationINTELRelease = (delegate* unmanaged<nint, void>)Load(nameof(gpuPerformanceConfigurationINTELRelease));
        gpuPerformanceConfigurationINTELGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuPerformanceConfigurationINTELGetVkHandle));
        gpuPerformanceConfigurationINTELGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuPerformanceConfigurationINTELGetDevice));

        gpuPipelineBinaryKHRCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuPipelineBinaryKHRCreate));
        gpuPipelineBinaryKHRDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuPipelineBinaryKHRDestroy));
        gpuPipelineBinaryKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuPipelineBinaryKHRGetVkHandle));
        gpuPipelineBinaryKHRGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuPipelineBinaryKHRGetDevice));

        gpuCuModuleNVXCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuCuModuleNVXCreate));
        gpuCuModuleNVXDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuCuModuleNVXDestroy));
        gpuCuModuleNVXGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuCuModuleNVXGetVkHandle));
        gpuCuModuleNVXGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuCuModuleNVXGetDevice));

        gpuCuFunctionNVXCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuCuFunctionNVXCreate));
        gpuCuFunctionNVXDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuCuFunctionNVXDestroy));
        gpuCuFunctionNVXGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuCuFunctionNVXGetVkHandle));
        gpuCuFunctionNVXGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuCuFunctionNVXGetDevice));

        gpuOpticalFlowSessionNVCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuOpticalFlowSessionNVCreate));
        gpuOpticalFlowSessionNVDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuOpticalFlowSessionNVDestroy));
        gpuOpticalFlowSessionNVGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuOpticalFlowSessionNVGetVkHandle));
        gpuOpticalFlowSessionNVGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuOpticalFlowSessionNVGetDevice));

        gpuShaderEXTCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuShaderEXTCreate));
        gpuShaderEXTDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuShaderEXTDestroy));
        gpuShaderEXTGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuShaderEXTGetVkHandle));
        gpuShaderEXTGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuShaderEXTGetDevice));

        gpuTensorARMCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuTensorARMCreate));
        gpuTensorARMDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuTensorARMDestroy));
        gpuTensorARMGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuTensorARMGetVkHandle));
        gpuTensorARMGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuTensorARMGetDevice));

        gpuTensorViewARMCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuTensorViewARMCreate));
        gpuTensorViewARMDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuTensorViewARMDestroy));
        gpuTensorViewARMGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuTensorViewARMGetVkHandle));
        gpuTensorViewARMGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuTensorViewARMGetDevice));

        gpuDataGraphPipelineSessionARMCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuDataGraphPipelineSessionARMCreate));
        gpuDataGraphPipelineSessionARMDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuDataGraphPipelineSessionARMDestroy));
        gpuDataGraphPipelineSessionARMGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDataGraphPipelineSessionARMGetVkHandle));
        gpuDataGraphPipelineSessionARMGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDataGraphPipelineSessionARMGetDevice));

        gpuDisplayKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDisplayKHRGetVkHandle));
        gpuDisplayKHRGetPhysicalDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDisplayKHRGetPhysicalDevice));
        gpuDisplayKHRGetModeCountKHR = (delegate* unmanaged<nint, uint>)Load(nameof(gpuDisplayKHRGetModeCountKHR));
        gpuDisplayKHRGetModeKHR = (delegate* unmanaged<nint, uint, nint*, Result>)Load(nameof(gpuDisplayKHRGetModeKHR));
        gpuDisplayKHRRelease = (delegate* unmanaged<nint, void>)Load(nameof(gpuDisplayKHRRelease));

        gpuDisplayModeKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuDisplayModeKHRGetVkHandle));
        gpuDisplayModeKHRGetDisplayKHR = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDisplayModeKHRGetDisplayKHR));
        gpuDisplayModeKHRGetPhysicalDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuDisplayModeKHRGetPhysicalDevice));
        gpuDisplayModeKHRRelease = (delegate* unmanaged<nint, void>)Load(nameof(gpuDisplayModeKHRRelease));

        gpuVideoSessionKHRCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuVideoSessionKHRCreate));
        gpuVideoSessionKHRDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuVideoSessionKHRDestroy));
        gpuVideoSessionKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuVideoSessionKHRGetVkHandle));
        gpuVideoSessionKHRGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuVideoSessionKHRGetDevice));

        gpuVideoSessionParametersKHRCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuVideoSessionParametersKHRCreate));
        gpuVideoSessionParametersKHRDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuVideoSessionParametersKHRDestroy));
        gpuVideoSessionParametersKHRGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuVideoSessionParametersKHRGetVkHandle));
        gpuVideoSessionParametersKHRGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuVideoSessionParametersKHRGetDevice));

        gpuSemaphoreSciSyncPoolNVCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuSemaphoreSciSyncPoolNVCreate));
        gpuSemaphoreSciSyncPoolNVDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuSemaphoreSciSyncPoolNVDestroy));
        gpuSemaphoreSciSyncPoolNVGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuSemaphoreSciSyncPoolNVGetVkHandle));
        gpuSemaphoreSciSyncPoolNVGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuSemaphoreSciSyncPoolNVGetDevice));

        gpuCudaModuleNVCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuCudaModuleNVCreate));
        gpuCudaModuleNVDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuCudaModuleNVDestroy));
        gpuCudaModuleNVGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuCudaModuleNVGetVkHandle));
        gpuCudaModuleNVGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuCudaModuleNVGetDevice));

        gpuCudaFunctionNVCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuCudaFunctionNVCreate));
        gpuCudaFunctionNVDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuCudaFunctionNVDestroy));
        gpuCudaFunctionNVGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuCudaFunctionNVGetVkHandle));
        gpuCudaFunctionNVGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuCudaFunctionNVGetDevice));

        gpuExternalComputeQueueNVCreate = (delegate* unmanaged<nint, void*, void*, nint*, Result>)Load(nameof(gpuExternalComputeQueueNVCreate));
        gpuExternalComputeQueueNVDestroy = (delegate* unmanaged<nint, void>)Load(nameof(gpuExternalComputeQueueNVDestroy));
        gpuExternalComputeQueueNVGetVkHandle = (delegate* unmanaged<nint, nuint>)Load(nameof(gpuExternalComputeQueueNVGetVkHandle));
        gpuExternalComputeQueueNVGetDevice = (delegate* unmanaged<nint, nint>)Load(nameof(gpuExternalComputeQueueNVGetDevice));

        nint Load(string exportName) => NativeLibrary.GetExport(moduleHandle, exportName);
    }

    public nint ModuleHandle { get; }

    public readonly delegate* unmanaged<uint> gpuGetApiVersion;
    public readonly delegate* unmanaged<byte*> gpuGetLastError;
    public readonly delegate* unmanaged<byte***, uint*, int> gpuGetRequiredInstanceExtensions;
    public readonly delegate* unmanaged<nint, uint*, uint*, int> gpuGetFramebufferSizeGlfw;

    public readonly delegate* unmanaged<void*, void*, nint*, Result> gpuInstanceCreate;
    public readonly delegate* unmanaged<nint, void> gpuInstanceDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuInstanceGetVkHandle;
    public readonly delegate* unmanaged<nint, uint> gpuInstanceGetPhysicalDeviceCount;
    public readonly delegate* unmanaged<nint, uint, nint*, Result> gpuInstanceGetPhysicalDevice;

    public readonly delegate* unmanaged<nint, nuint> gpuPhysicalDeviceGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuPhysicalDeviceGetInstance;
    public readonly delegate* unmanaged<nint, void> gpuPhysicalDeviceRelease;
    public readonly delegate* unmanaged<nint, uint> gpuPhysicalDeviceGetDisplayCountKHR;
    public readonly delegate* unmanaged<nint, uint, nint*, Result> gpuPhysicalDeviceGetDisplayKHR;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuDeviceCreate;
    public readonly delegate* unmanaged<nint, void> gpuDeviceDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDeviceGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDeviceGetPhysicalDevice;
    public readonly delegate* unmanaged<nint, uint, uint, nint*, Result> gpuDeviceGetQueue;

    public readonly delegate* unmanaged<nint, nuint> gpuQueueGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuQueueGetDevice;
    public readonly delegate* unmanaged<nint, uint> gpuQueueGetFamilyIndex;
    public readonly delegate* unmanaged<nint, uint> gpuQueueGetQueueIndex;
    public readonly delegate* unmanaged<nint, void> gpuQueueRelease;

    public readonly delegate* unmanaged<nint, nint, void*, nint*, Result> gpuSurfaceCreateGlfw;
    public readonly delegate* unmanaged<nint, void> gpuSurfaceDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuSurfaceGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSurfaceGetInstance;
    public readonly delegate* unmanaged<nint, nuint> gpuSurfaceKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSurfaceKHRGetInstance;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuDebugReportCallbackEXTCreate;
    public readonly delegate* unmanaged<nint, void> gpuDebugReportCallbackEXTDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDebugReportCallbackEXTGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDebugReportCallbackEXTGetInstance;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuDebugUtilsMessengerEXTCreate;
    public readonly delegate* unmanaged<nint, void> gpuDebugUtilsMessengerEXTDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDebugUtilsMessengerEXTGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDebugUtilsMessengerEXTGetInstance;

    public readonly delegate* unmanaged<nint, nint, void*, void*, nint*, Result> gpuSwapchainCreate;
    public readonly delegate* unmanaged<nint, void> gpuSwapchainDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuSwapchainGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSwapchainGetDevice;
    public readonly delegate* unmanaged<nint, nint> gpuSwapchainGetSurface;
    public readonly delegate* unmanaged<nint, nuint> gpuSwapchainKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSwapchainKHRGetDevice;
    public readonly delegate* unmanaged<nint, nint> gpuSwapchainKHRGetSurface;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuShaderModuleCreate;
    public readonly delegate* unmanaged<nint, void> gpuShaderModuleDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuShaderModuleGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuShaderModuleGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuPipelineLayoutCreate;
    public readonly delegate* unmanaged<nint, void> gpuPipelineLayoutDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuPipelineLayoutGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuPipelineLayoutGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuSamplerCreate;
    public readonly delegate* unmanaged<nint, void> gpuSamplerDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuSamplerGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSamplerGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuDescriptorSetLayoutCreate;
    public readonly delegate* unmanaged<nint, void> gpuDescriptorSetLayoutDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDescriptorSetLayoutGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDescriptorSetLayoutGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuDescriptorPoolCreate;
    public readonly delegate* unmanaged<nint, void> gpuDescriptorPoolDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDescriptorPoolGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDescriptorPoolGetDevice;

    public readonly delegate* unmanaged<nint, void*, nint*, Result> gpuDescriptorSetAllocate;
    public readonly delegate* unmanaged<nint, void> gpuDescriptorSetDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDescriptorSetGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDescriptorSetGetPool;
    public readonly delegate* unmanaged<nint, nint> gpuDescriptorSetGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuFramebufferCreate;
    public readonly delegate* unmanaged<nint, void> gpuFramebufferDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuFramebufferGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuFramebufferGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuRenderPassCreate;
    public readonly delegate* unmanaged<nint, void> gpuRenderPassDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuRenderPassGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuRenderPassGetDevice;

    public readonly delegate* unmanaged<nint, nint, void*, void*, nint*, Result> gpuPipelineCreateGraphics;
    public readonly delegate* unmanaged<nint, nint, void*, void*, nint*, Result> gpuPipelineCreateCompute;
    public readonly delegate* unmanaged<nint, void> gpuPipelineDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuPipelineGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuPipelineGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuPipelineCacheCreate;
    public readonly delegate* unmanaged<nint, void> gpuPipelineCacheDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuPipelineCacheGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuPipelineCacheGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuDescriptorUpdateTemplateCreate;
    public readonly delegate* unmanaged<nint, void> gpuDescriptorUpdateTemplateDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDescriptorUpdateTemplateGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDescriptorUpdateTemplateGetDevice;
    public readonly delegate* unmanaged<nint, nuint> gpuDescriptorUpdateTemplateKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDescriptorUpdateTemplateKHRGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuSamplerYcbcrConversionCreate;
    public readonly delegate* unmanaged<nint, void> gpuSamplerYcbcrConversionDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuSamplerYcbcrConversionGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSamplerYcbcrConversionGetDevice;
    public readonly delegate* unmanaged<nint, nuint> gpuSamplerYcbcrConversionKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSamplerYcbcrConversionKHRGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuPrivateDataSlotCreate;
    public readonly delegate* unmanaged<nint, void> gpuPrivateDataSlotDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuPrivateDataSlotGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuPrivateDataSlotGetDevice;
    public readonly delegate* unmanaged<nint, nuint> gpuPrivateDataSlotEXTGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuPrivateDataSlotEXTGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuCommandPoolCreate;
    public readonly delegate* unmanaged<nint, void> gpuCommandPoolDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuCommandPoolGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuCommandPoolGetDevice;

    public readonly delegate* unmanaged<nint, int, nint*, Result> gpuCommandBufferCreate;
    public readonly delegate* unmanaged<nint, void> gpuCommandBufferDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuCommandBufferGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuCommandBufferGetCommandPool;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuDeviceMemoryCreate;
    public readonly delegate* unmanaged<nint, void> gpuDeviceMemoryDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDeviceMemoryGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDeviceMemoryGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuBufferCreate;
    public readonly delegate* unmanaged<nint, void> gpuBufferDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuBufferGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuBufferGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuBufferViewCreate;
    public readonly delegate* unmanaged<nint, void> gpuBufferViewDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuBufferViewGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuBufferViewGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuImageCreate;
    public readonly delegate* unmanaged<nint, void> gpuImageDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuImageGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuImageGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuImageViewCreate;
    public readonly delegate* unmanaged<nint, void> gpuImageViewDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuImageViewGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuImageViewGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuFenceCreate;
    public readonly delegate* unmanaged<nint, void> gpuFenceDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuFenceGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuFenceGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuSemaphoreCreate;
    public readonly delegate* unmanaged<nint, void> gpuSemaphoreDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuSemaphoreGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSemaphoreGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuEventCreate;
    public readonly delegate* unmanaged<nint, void> gpuEventDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuEventGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuEventGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuQueryPoolCreate;
    public readonly delegate* unmanaged<nint, void> gpuQueryPoolDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuQueryPoolGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuQueryPoolGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuValidationCacheEXTCreate;
    public readonly delegate* unmanaged<nint, void> gpuValidationCacheEXTDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuValidationCacheEXTGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuValidationCacheEXTGetDevice;

    public readonly delegate* unmanaged<nint, void*, nint*, Result> gpuDeferredOperationKHRCreate;
    public readonly delegate* unmanaged<nint, void> gpuDeferredOperationKHRDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDeferredOperationKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDeferredOperationKHRGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuIndirectCommandsLayoutNVCreate;
    public readonly delegate* unmanaged<nint, void> gpuIndirectCommandsLayoutNVDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuIndirectCommandsLayoutNVGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuIndirectCommandsLayoutNVGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuIndirectCommandsLayoutEXTCreate;
    public readonly delegate* unmanaged<nint, void> gpuIndirectCommandsLayoutEXTDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuIndirectCommandsLayoutEXTGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuIndirectCommandsLayoutEXTGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuIndirectExecutionSetEXTCreate;
    public readonly delegate* unmanaged<nint, void> gpuIndirectExecutionSetEXTDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuIndirectExecutionSetEXTGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuIndirectExecutionSetEXTGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuAccelerationStructureKHRCreate;
    public readonly delegate* unmanaged<nint, void> gpuAccelerationStructureKHRDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuAccelerationStructureKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuAccelerationStructureKHRGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuAccelerationStructureNVCreate;
    public readonly delegate* unmanaged<nint, void> gpuAccelerationStructureNVDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuAccelerationStructureNVGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuAccelerationStructureNVGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuMicromapEXTCreate;
    public readonly delegate* unmanaged<nint, void> gpuMicromapEXTDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuMicromapEXTGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuMicromapEXTGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuBufferCollectionFUCHSIACreate;
    public readonly delegate* unmanaged<nint, void> gpuBufferCollectionFUCHSIADestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuBufferCollectionFUCHSIAGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuBufferCollectionFUCHSIAGetDevice;

    public readonly delegate* unmanaged<nint, void*, nint*, Result> gpuPerformanceConfigurationINTELAcquire;
    public readonly delegate* unmanaged<nint, void> gpuPerformanceConfigurationINTELRelease;
    public readonly delegate* unmanaged<nint, nuint> gpuPerformanceConfigurationINTELGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuPerformanceConfigurationINTELGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuPipelineBinaryKHRCreate;
    public readonly delegate* unmanaged<nint, void> gpuPipelineBinaryKHRDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuPipelineBinaryKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuPipelineBinaryKHRGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuCuModuleNVXCreate;
    public readonly delegate* unmanaged<nint, void> gpuCuModuleNVXDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuCuModuleNVXGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuCuModuleNVXGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuCuFunctionNVXCreate;
    public readonly delegate* unmanaged<nint, void> gpuCuFunctionNVXDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuCuFunctionNVXGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuCuFunctionNVXGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuOpticalFlowSessionNVCreate;
    public readonly delegate* unmanaged<nint, void> gpuOpticalFlowSessionNVDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuOpticalFlowSessionNVGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuOpticalFlowSessionNVGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuShaderEXTCreate;
    public readonly delegate* unmanaged<nint, void> gpuShaderEXTDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuShaderEXTGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuShaderEXTGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuTensorARMCreate;
    public readonly delegate* unmanaged<nint, void> gpuTensorARMDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuTensorARMGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuTensorARMGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuTensorViewARMCreate;
    public readonly delegate* unmanaged<nint, void> gpuTensorViewARMDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuTensorViewARMGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuTensorViewARMGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuDataGraphPipelineSessionARMCreate;
    public readonly delegate* unmanaged<nint, void> gpuDataGraphPipelineSessionARMDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuDataGraphPipelineSessionARMGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDataGraphPipelineSessionARMGetDevice;

    public readonly delegate* unmanaged<nint, nuint> gpuDisplayKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDisplayKHRGetPhysicalDevice;
    public readonly delegate* unmanaged<nint, uint> gpuDisplayKHRGetModeCountKHR;
    public readonly delegate* unmanaged<nint, uint, nint*, Result> gpuDisplayKHRGetModeKHR;
    public readonly delegate* unmanaged<nint, void> gpuDisplayKHRRelease;

    public readonly delegate* unmanaged<nint, nuint> gpuDisplayModeKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuDisplayModeKHRGetDisplayKHR;
    public readonly delegate* unmanaged<nint, nint> gpuDisplayModeKHRGetPhysicalDevice;
    public readonly delegate* unmanaged<nint, void> gpuDisplayModeKHRRelease;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuVideoSessionKHRCreate;
    public readonly delegate* unmanaged<nint, void> gpuVideoSessionKHRDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuVideoSessionKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuVideoSessionKHRGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuVideoSessionParametersKHRCreate;
    public readonly delegate* unmanaged<nint, void> gpuVideoSessionParametersKHRDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuVideoSessionParametersKHRGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuVideoSessionParametersKHRGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuSemaphoreSciSyncPoolNVCreate;
    public readonly delegate* unmanaged<nint, void> gpuSemaphoreSciSyncPoolNVDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuSemaphoreSciSyncPoolNVGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuSemaphoreSciSyncPoolNVGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuCudaModuleNVCreate;
    public readonly delegate* unmanaged<nint, void> gpuCudaModuleNVDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuCudaModuleNVGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuCudaModuleNVGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuCudaFunctionNVCreate;
    public readonly delegate* unmanaged<nint, void> gpuCudaFunctionNVDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuCudaFunctionNVGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuCudaFunctionNVGetDevice;

    public readonly delegate* unmanaged<nint, void*, void*, nint*, Result> gpuExternalComputeQueueNVCreate;
    public readonly delegate* unmanaged<nint, void> gpuExternalComputeQueueNVDestroy;
    public readonly delegate* unmanaged<nint, nuint> gpuExternalComputeQueueNVGetVkHandle;
    public readonly delegate* unmanaged<nint, nint> gpuExternalComputeQueueNVGetDevice;
}


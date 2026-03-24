using System.Runtime.InteropServices;

namespace GPU;

[StructLayout(LayoutKind.Sequential)]
public struct ApplicationInfo
{
    public StructureType SType;
    public nint PNext;
    public nint PApplicationName;
    public uint ApplicationVersion;
    public nint PEngineName;
    public uint EngineVersion;
    public uint ApiVersion;
}

[StructLayout(LayoutKind.Sequential)]
public struct AllocationCallbacks
{
    public nint PUserData;
    public nint PfnAllocation;
    public nint PfnReallocation;
    public nint PfnFree;
    public nint PfnInternalAllocation;
    public nint PfnInternalFree;
}

[StructLayout(LayoutKind.Sequential)]
public struct InstanceCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nint PApplicationInfo;
    public uint EnabledLayerCount;
    public nint PpEnabledLayerNames;
    public uint EnabledExtensionCount;
    public nint PpEnabledExtensionNames;
}

[StructLayout(LayoutKind.Sequential)]
public struct DeviceQueueCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint QueueFamilyIndex;
    public uint QueueCount;
    public nint PQueuePriorities;
}

[StructLayout(LayoutKind.Sequential)]
public struct DeviceCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint QueueCreateInfoCount;
    public nint PQueueCreateInfos;
    public uint EnabledLayerCount;
    public nint PpEnabledLayerNames;
    public uint EnabledExtensionCount;
    public nint PpEnabledExtensionNames;
    public nint PEnabledFeatures;
}

[StructLayout(LayoutKind.Sequential)]
public struct Extent2D
{
    public uint Width;
    public uint Height;
}

[StructLayout(LayoutKind.Sequential)]
public struct Extent3D
{
    public uint Width;
    public uint Height;
    public uint Depth;
}

[StructLayout(LayoutKind.Sequential)]
public struct Offset2D
{
    public int X;
    public int Y;
}

[StructLayout(LayoutKind.Sequential)]
public struct Rect2D
{
    public Offset2D Offset;
    public Extent2D Extent;
}

[StructLayout(LayoutKind.Sequential)]
public struct SwapchainCreateInfoKHR
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint Surface;
    public uint MinImageCount;
    public Format ImageFormat;
    public uint ImageColorSpace;
    public Extent2D ImageExtent;
    public uint ImageArrayLayers;
    public ImageUsageFlags ImageUsage;
    public SharingMode ImageSharingMode;
    public uint QueueFamilyIndexCount;
    public nint PQueueFamilyIndices;
    public uint PreTransform;
    public uint CompositeAlpha;
    public PresentModeKHR PresentMode;
    public uint Clipped;
    public nuint OldSwapchain;
}

[StructLayout(LayoutKind.Sequential)]
public struct ShaderModuleCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint CodeSize;
    public nint PCode;
}

[StructLayout(LayoutKind.Sequential)]
public struct PipelineLayoutCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint SetLayoutCount;
    public nint PSetLayouts;
    public uint PushConstantRangeCount;
    public nint PPushConstantRanges;
}

[StructLayout(LayoutKind.Sequential)]
public struct SamplerCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint MagFilter;
    public uint MinFilter;
    public uint MipmapMode;
    public uint AddressModeU;
    public uint AddressModeV;
    public uint AddressModeW;
    public float MipLodBias;
    public uint AnisotropyEnable;
    public float MaxAnisotropy;
    public uint CompareEnable;
    public CompareOp CompareOp;
    public float MinLod;
    public float MaxLod;
    public uint BorderColor;
    public uint UnnormalizedCoordinates;
}

[StructLayout(LayoutKind.Sequential)]
public struct DescriptorSetLayoutBinding
{
    public uint Binding;
    public DescriptorType DescriptorType;
    public uint DescriptorCount;
    public ShaderStageFlags StageFlags;
    public nint PImmutableSamplers;
}

[StructLayout(LayoutKind.Sequential)]
public struct DescriptorSetLayoutCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public DescriptorSetLayoutCreateFlags Flags;
    public uint BindingCount;
    public nint PBindings;
}

[StructLayout(LayoutKind.Sequential)]
public struct DescriptorPoolSize
{
    public DescriptorType Type;
    public uint DescriptorCount;
}

[StructLayout(LayoutKind.Sequential)]
public struct DescriptorImageInfo
{
    public nuint Sampler;
    public nuint ImageView;
    public ImageLayout ImageLayout;
}

[StructLayout(LayoutKind.Sequential)]
public struct DescriptorBufferInfo
{
    public nuint Buffer;
    public DeviceSize Offset;
    public DeviceSize Range;
}

[StructLayout(LayoutKind.Sequential)]
public struct DescriptorPoolCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public DescriptorPoolCreateFlags Flags;
    public uint MaxSets;
    public uint PoolSizeCount;
    public nint PPoolSizes;
}

[StructLayout(LayoutKind.Sequential)]
public struct DescriptorSetAllocateInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint DescriptorPool;
    public uint DescriptorSetCount;
    public nint PSetLayouts;
}

[StructLayout(LayoutKind.Sequential)]
public struct WriteDescriptorSet
{
    public StructureType SType;
    public nint PNext;
    public nuint DstSet;
    public uint DstBinding;
    public uint DstArrayElement;
    public uint DescriptorCount;
    public DescriptorType DescriptorType;
    public nint PImageInfo;
    public nint PBufferInfo;
    public nint PTexelBufferView;
}

[StructLayout(LayoutKind.Sequential)]
public struct CopyDescriptorSet
{
    public StructureType SType;
    public nint PNext;
    public nuint SrcSet;
    public uint SrcBinding;
    public uint SrcArrayElement;
    public nuint DstSet;
    public uint DstBinding;
    public uint DstArrayElement;
    public uint DescriptorCount;
}

[StructLayout(LayoutKind.Sequential)]
public struct FramebufferCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint RenderPass;
    public uint AttachmentCount;
    public nint PAttachments;
    public uint Width;
    public uint Height;
    public uint Layers;
}

[StructLayout(LayoutKind.Sequential)]
public struct RenderPassCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint AttachmentCount;
    public nint PAttachments;
    public uint SubpassCount;
    public nint PSubpasses;
    public uint DependencyCount;
    public nint PDependencies;
}

[StructLayout(LayoutKind.Sequential)]
public struct PipelineShaderStageCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public ShaderStageFlags Stage;
    public nuint Module;
    public nint PName;
    public nint PSpecializationInfo;
}

[StructLayout(LayoutKind.Sequential)]
public struct GraphicsPipelineCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint StageCount;
    public nint PStages;
    public nint PVertexInputState;
    public nint PInputAssemblyState;
    public nint PTessellationState;
    public nint PViewportState;
    public nint PRasterizationState;
    public nint PMultisampleState;
    public nint PDepthStencilState;
    public nint PColorBlendState;
    public nint PDynamicState;
    public nuint Layout;
    public nuint RenderPass;
    public uint Subpass;
    public nuint BasePipelineHandle;
    public int BasePipelineIndex;
}

[StructLayout(LayoutKind.Sequential)]
public struct ComputePipelineCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public PipelineShaderStageCreateInfo Stage;
    public nuint Layout;
    public nuint BasePipelineHandle;
    public int BasePipelineIndex;
}

[StructLayout(LayoutKind.Sequential)]
public struct PipelineCacheCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint InitialDataSize;
    public nint PInitialData;
}

[StructLayout(LayoutKind.Sequential)]
public struct PipelineBinaryCreateInfoKHR
{
    public StructureType SType;
    public nint PNext;
    public nint PKeysAndDataInfo;
    public nuint Pipeline;
    public nint PPipelineCreateInfo;
}

[StructLayout(LayoutKind.Sequential)]
public struct DescriptorUpdateTemplateCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint DescriptorUpdateEntryCount;
    public nint PDescriptorUpdateEntries;
    public uint TemplateType;
    public nuint DescriptorSetLayout;
    public PipelineBindPoint PipelineBindPoint;
    public nuint PipelineLayout;
    public uint Set;
}

[StructLayout(LayoutKind.Sequential)]
public struct SamplerYcbcrConversionCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public Format Format;
    public uint YcbcrModel;
    public uint YcbcrRange;
    public ComponentMapping Components;
    public uint XChromaOffset;
    public uint YChromaOffset;
    public uint ChromaFilter;
    public Bool32 ForceExplicitReconstruction;
}

[StructLayout(LayoutKind.Sequential)]
public struct PrivateDataSlotCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
}

[StructLayout(LayoutKind.Sequential)]
public struct ValidationCacheCreateInfoEXT
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint InitialDataSize;
    public nint PInitialData;
}

[StructLayout(LayoutKind.Sequential)]
public struct CommandPoolCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public CommandPoolCreateFlags Flags;
    public uint QueueFamilyIndex;
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryAllocateInfo
{
    public StructureType SType;
    public nint PNext;
    public ulong AllocationSize;
    public uint MemoryTypeIndex;
}

[StructLayout(LayoutKind.Sequential)]
public struct BufferCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public ulong Size;
    public BufferUsageFlags Usage;
    public SharingMode SharingMode;
    public uint QueueFamilyIndexCount;
    public nint PQueueFamilyIndices;
}

[StructLayout(LayoutKind.Sequential)]
public struct BufferViewCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint Buffer;
    public Format Format;
    public ulong Offset;
    public ulong Range;
}

[StructLayout(LayoutKind.Sequential)]
public struct ImageCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public ImageCreateFlags Flags;
    public ImageType ImageType;
    public Format Format;
    public Extent3D Extent;
    public uint MipLevels;
    public uint ArrayLayers;
    public SampleCountFlags Samples;
    public ImageTiling Tiling;
    public ImageUsageFlags Usage;
    public SharingMode SharingMode;
    public uint QueueFamilyIndexCount;
    public nint PQueueFamilyIndices;
    public ImageLayout InitialLayout;
}

[StructLayout(LayoutKind.Sequential)]
public struct ComponentMapping
{
    public uint R;
    public uint G;
    public uint B;
    public uint A;
}

[StructLayout(LayoutKind.Sequential)]
public struct ImageSubresourceRange
{
    public uint AspectMask;
    public uint BaseMipLevel;
    public uint LevelCount;
    public uint BaseArrayLayer;
    public uint LayerCount;
}

[StructLayout(LayoutKind.Sequential)]
public struct ImageViewCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint Image;
    public ImageViewType ViewType;
    public Format Format;
    public ComponentMapping Components;
    public ImageSubresourceRange SubresourceRange;
}

[StructLayout(LayoutKind.Sequential)]
public struct FenceCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public FenceCreateFlags Flags;
}

[StructLayout(LayoutKind.Sequential)]
public struct SemaphoreCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
}

[StructLayout(LayoutKind.Sequential)]
public struct EventCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
}

[StructLayout(LayoutKind.Sequential)]
public struct QueryPoolCreateInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public QueryType QueryType;
    public uint QueryCount;
    public uint PipelineStatistics;
}

[StructLayout(LayoutKind.Sequential)]
public struct DebugReportCallbackCreateInfoEXT
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nint PfnCallback;
    public nint PUserData;
}

[StructLayout(LayoutKind.Sequential)]
public struct DebugUtilsMessengerCreateInfoEXT
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint MessageSeverity;
    public uint MessageType;
    public nint PfnUserCallback;
    public nint PUserData;
}

[StructLayout(LayoutKind.Sequential)]
public struct CommandBufferAllocateInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint CommandPool;
    public CommandBufferLevel Level;
    public uint CommandBufferCount;
}

[StructLayout(LayoutKind.Sequential)]
public struct CommandBufferBeginInfo
{
    public StructureType SType;
    public nint PNext;
    public CommandBufferUsageFlags Flags;
    public nint PInheritanceInfo;
}

[StructLayout(LayoutKind.Sequential)]
public struct SubmitInfo
{
    public StructureType SType;
    public nint PNext;
    public uint WaitSemaphoreCount;
    public nint PWaitSemaphores;
    public nint PWaitDstStageMask;
    public uint CommandBufferCount;
    public nint PCommandBuffers;
    public uint SignalSemaphoreCount;
    public nint PSignalSemaphores;
}

[StructLayout(LayoutKind.Sequential)]
public struct PresentInfoKHR
{
    public StructureType SType;
    public nint PNext;
    public uint WaitSemaphoreCount;
    public nint PWaitSemaphores;
    public uint SwapchainCount;
    public nint PSwapchains;
    public nint PImageIndices;
    public nint PResults;
}

[StructLayout(LayoutKind.Sequential)]
public struct RenderPassBeginInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint RenderPass;
    public nuint Framebuffer;
    public Rect2D RenderArea;
    public uint ClearValueCount;
    public nint PClearValues;
}

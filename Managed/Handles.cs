namespace GPU;

public readonly struct InstanceHandle
{
    public InstanceHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct PhysicalDeviceHandle
{
    public PhysicalDeviceHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DeviceHandle
{
    public DeviceHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct QueueHandle
{
    public QueueHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct SurfaceHandle
{
    public SurfaceHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct SwapchainHandle
{
    public SwapchainHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct ShaderModuleHandle
{
    public ShaderModuleHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct PipelineHandle
{
    public PipelineHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct PipelineLayoutHandle
{
    public PipelineLayoutHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct SamplerHandle
{
    public SamplerHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DescriptorSetLayoutHandle
{
    public DescriptorSetLayoutHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DescriptorPoolHandle
{
    public DescriptorPoolHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DescriptorSetHandle
{
    public DescriptorSetHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct FramebufferHandle
{
    public FramebufferHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct RenderPassHandle
{
    public RenderPassHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct PipelineCacheHandle
{
    public PipelineCacheHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DescriptorUpdateTemplateHandle
{
    public DescriptorUpdateTemplateHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct SamplerYcbcrConversionHandle
{
    public SamplerYcbcrConversionHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct PrivateDataSlotHandle
{
    public PrivateDataSlotHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct CommandPoolHandle
{
    public CommandPoolHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct CommandBufferHandle
{
    public CommandBufferHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DeviceMemoryHandle
{
    public DeviceMemoryHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct BufferHandle
{
    public BufferHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct BufferViewHandle
{
    public BufferViewHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct ImageHandle
{
    public ImageHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct ImageViewHandle
{
    public ImageViewHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct FenceHandle
{
    public FenceHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct SemaphoreHandle
{
    public SemaphoreHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct EventHandle
{
    public EventHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct QueryPoolHandle
{
    public QueryPoolHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DebugReportCallbackEXTHandle
{
    public DebugReportCallbackEXTHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DebugUtilsMessengerEXTHandle
{
    public DebugUtilsMessengerEXTHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct ValidationCacheEXTHandle
{
    public ValidationCacheEXTHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DeferredOperationKHRHandle
{
    public DeferredOperationKHRHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct IndirectCommandsLayoutNVHandle
{
    public IndirectCommandsLayoutNVHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct IndirectCommandsLayoutEXTHandle
{
    public IndirectCommandsLayoutEXTHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct IndirectExecutionSetEXTHandle
{
    public IndirectExecutionSetEXTHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct AccelerationStructureKHRHandle
{
    public AccelerationStructureKHRHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct AccelerationStructureNVHandle
{
    public AccelerationStructureNVHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct MicromapEXTHandle
{
    public MicromapEXTHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct BufferCollectionFUCHSIAHandle
{
    public BufferCollectionFUCHSIAHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct PerformanceConfigurationINTELHandle
{
    public PerformanceConfigurationINTELHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct PipelineBinaryKHRHandle
{
    public PipelineBinaryKHRHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct CuModuleNVXHandle
{
    public CuModuleNVXHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct CuFunctionNVXHandle
{
    public CuFunctionNVXHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct OpticalFlowSessionNVHandle
{
    public OpticalFlowSessionNVHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct ShaderEXTHandle
{
    public ShaderEXTHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct TensorARMHandle
{
    public TensorARMHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct TensorViewARMHandle
{
    public TensorViewARMHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DataGraphPipelineSessionARMHandle
{
    public DataGraphPipelineSessionARMHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DisplayKHRHandle
{
    public DisplayKHRHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct DisplayModeKHRHandle
{
    public DisplayModeKHRHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct VideoSessionKHRHandle
{
    public VideoSessionKHRHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct VideoSessionParametersKHRHandle
{
    public VideoSessionParametersKHRHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct SemaphoreSciSyncPoolNVHandle
{
    public SemaphoreSciSyncPoolNVHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct CudaModuleNVHandle
{
    public CudaModuleNVHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct CudaFunctionNVHandle
{
    public CudaFunctionNVHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}

public readonly struct ExternalComputeQueueNVHandle
{
    public ExternalComputeQueueNVHandle(nint value) => Value = value;

    public nint Value { get; }
    public bool IsNull => Value == nint.Zero;
}


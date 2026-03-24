namespace GPU;

public enum CommandBufferLevel
{
    Primary = 0,
    Secondary = 1,
}

public enum StructureType
{
    ApplicationInfo = 0,
    InstanceCreateInfo = 1,
    DeviceQueueCreateInfo = 2,
    DeviceCreateInfo = 3,
    SubmitInfo = 4,
    MemoryAllocateInfo = 5,
    MappedMemoryRange = 6,
    BindSparseInfo = 7,
    FenceCreateInfo = 8,
    SemaphoreCreateInfo = 9,
    EventCreateInfo = 10,
    QueryPoolCreateInfo = 11,
    BufferCreateInfo = 12,
    BufferViewCreateInfo = 13,
    ImageCreateInfo = 14,
    ImageViewCreateInfo = 15,
    ShaderModuleCreateInfo = 16,
    PipelineCacheCreateInfo = 17,
    PipelineShaderStageCreateInfo = 18,
    GraphicsPipelineCreateInfo = 28,
    ComputePipelineCreateInfo = 29,
    PipelineLayoutCreateInfo = 30,
    SamplerCreateInfo = 31,
    DescriptorSetLayoutCreateInfo = 32,
    DescriptorPoolCreateInfo = 33,
    DescriptorSetAllocateInfo = 34,
    FramebufferCreateInfo = 37,
    RenderPassCreateInfo = 38,
    CommandPoolCreateInfo = 39,
    CommandBufferAllocateInfo = 40,
    CommandBufferBeginInfo = 42,
    RenderPassBeginInfo = 43,
    SwapchainCreateInfoKHR = 1000001000,
    PresentInfoKHR = 1000001001,
    DebugReportCallbackCreateInfoEXT = 1000011000,
    DescriptorUpdateTemplateCreateInfo = 1000085000,
    SamplerYcbcrConversionCreateInfo = 1000156000,
    DebugUtilsMessengerCreateInfoEXT = 1000128004,
    ValidationCacheCreateInfoEXT = 1000160000,
    PerformanceConfigurationAcquireInfoINTEL = 1000210000,
    PrivateDataSlotCreateInfo = 1000295000,
    VideoSessionCreateInfoKHR = 1000023000,
    VideoSessionParametersCreateInfoKHR = 1000023001,
    PipelineBinaryCreateInfoKHR = 1000485000,
    SemaphoreSciSyncPoolCreateInfoNV = 1000529000,
    ShaderCreateInfoEXT = 1000541000,
    IndirectCommandsLayoutCreateInfoEXT = 1000546000,
    IndirectExecutionSetCreateInfoEXT = 1000546001,
    DataGraphPipelineSessionCreateInfoARM = 1000569000,
    ExternalComputeQueueCreateInfoNV = 1000638000,
    IndirectCommandsLayoutCreateInfoNV = 1000277000,
    AccelerationStructureCreateInfoKHR = 1000150000,
    AccelerationStructureCreateInfoNV = 1000165000,
    MicromapCreateInfoEXT = 1000396000,
    BufferCollectionCreateInfoFUCHSIA = 1000366000,
    CuModuleCreateInfoNVX = 1000029000,
    CuFunctionCreateInfoNVX = 1000029001,
    OpticalFlowSessionCreateInfoNV = 1000464000,
    TensorCreateInfoARM = 1000460000,
    TensorViewCreateInfoARM = 1000460001,
    CudaModuleCreateInfoNV = 1000307000,
    CudaFunctionCreateInfoNV = 1000307001,
}

public enum SharingMode
{
    Exclusive = 0,
    Concurrent = 1,
}

public enum AttachmentLoadOp
{
    Load = 0,
    Clear = 1,
    DontCare = 2,
    None = 1000400000,
}

public enum AttachmentStoreOp
{
    Store = 0,
    DontCare = 1,
    None = 1000301000,
}

public enum ImageType
{
    Type1D = 0,
    Type2D = 1,
    Type3D = 2,
}

public enum ImageTiling
{
    Optimal = 0,
    Linear = 1,
    DrmFormatModifierEXT = 1000158000,
}

public enum ImageViewType
{
    Type1D = 0,
    Type2D = 1,
    Type3D = 2,
    Cube = 3,
    Type1DArray = 4,
    Type2DArray = 5,
    CubeArray = 6,
}

public enum ComponentSwizzle
{
    Identity = 0,
    Zero = 1,
    One = 2,
    R = 3,
    G = 4,
    B = 5,
    A = 6,
}

public enum Format
{
    Undefined = 0,
    R8Unorm = 9,
    R8G8Unorm = 16,
    R8G8B8A8Unorm = 37,
    B8G8R8A8Unorm = 44,
    R16Sfloat = 76,
    R16G16Sfloat = 83,
    R16G16B16A16Sfloat = 97,
    R32Sfloat = 100,
    R32G32Sfloat = 103,
    R32G32B32Sfloat = 106,
    R32G32B32A32Sfloat = 109,
    D16Unorm = 124,
    X8D24UnormPack32 = 125,
    D32Sfloat = 126,
    S8Uint = 127,
    D24UnormS8Uint = 129,
    D32SfloatS8Uint = 130,
}

public enum ImageLayout
{
    Undefined = 0,
    General = 1,
    ColorAttachmentOptimal = 2,
    DepthStencilAttachmentOptimal = 3,
    DepthStencilReadOnlyOptimal = 4,
    ShaderReadOnlyOptimal = 5,
    TransferSrcOptimal = 6,
    TransferDstOptimal = 7,
    Preinitialized = 8,
    PresentSrcKHR = 1000001002,
}

public enum PipelineBindPoint
{
    Graphics = 0,
    Compute = 1,
    RayTracingKHR = 1000165000,
    SubpassShadingHUAWEI = 1000369003,
}

public enum SampleCountFlagBits
{
    Count1 = 0x00000001,
    Count2 = 0x00000002,
    Count4 = 0x00000004,
    Count8 = 0x00000008,
    Count16 = 0x00000010,
    Count32 = 0x00000020,
    Count64 = 0x00000040,
}

public enum ShaderStageFlagBits
{
    Vertex = 0x00000001,
    TessellationControl = 0x00000002,
    TessellationEvaluation = 0x00000004,
    Geometry = 0x00000008,
    Fragment = 0x00000010,
    Compute = 0x00000020,
}

public enum SubpassContents
{
    Inline = 0,
    SecondaryCommandBuffers = 1,
    InlineAndSecondaryCommandBuffersKHR = 1000451000,
}

public enum CommandBufferResetFlagBits
{
    ReleaseResources = 0x00000001,
}

public enum CommandBufferUsageFlagBits
{
    OneTimeSubmit = 0x00000001,
    RenderPassContinue = 0x00000002,
    SimultaneousUse = 0x00000004,
}

public enum CommandPoolCreateFlagBits
{
    Transient = 0x00000001,
    ResetCommandBuffer = 0x00000002,
    Protected = 0x00000004,
}

public enum CommandPoolResetFlagBits
{
    ReleaseResources = 0x00000001,
}

public enum IndexType
{
    Uint16 = 0,
    Uint32 = 1,
    NoneKHR = 1000165000,
    Uint8KHR = 1000265000,
}

public enum QueryType
{
    Occlusion = 0,
    PipelineStatistics = 1,
    Timestamp = 2,
    TransformFeedbackStreamEXT = 1000028004,
    ResultStatusOnlyKHR = 1000023000,
}

public enum CompareOp
{
    Never = 0,
    Less = 1,
    Equal = 2,
    LessOrEqual = 3,
    Greater = 4,
    NotEqual = 5,
    GreaterOrEqual = 6,
    Always = 7,
}

public enum StencilOp
{
    Keep = 0,
    Zero = 1,
    Replace = 2,
    IncrementAndClamp = 3,
    DecrementAndClamp = 4,
    Invert = 5,
    IncrementAndWrap = 6,
    DecrementAndWrap = 7,
}

public enum StencilFaceFlagBits
{
    Front = 0x00000001,
    Back = 0x00000002,
    FrontAndBack = 0x00000003,
}

public enum CullModeFlagBits
{
    None = 0,
    Front = 0x00000001,
    Back = 0x00000002,
    FrontAndBack = 0x00000003,
}

public enum FrontFace
{
    CounterClockwise = 0,
    Clockwise = 1,
}

public enum PrimitiveTopology
{
    PointList = 0,
    LineList = 1,
    LineStrip = 2,
    TriangleList = 3,
    TriangleStrip = 4,
    TriangleFan = 5,
}

public enum PresentModeKHR
{
    ImmediateKHR = 0,
    MailboxKHR = 1,
    FifoKHR = 2,
    FifoRelaxedKHR = 3,
}

public enum ColorSpaceKHR
{
    SrgbNonlinearKHR = 0,
    DisplayP3NonlinearEXT = 1000104001,
    ExtendedSrgbLinearEXT = 1000104002,
    DciP3LinearEXT = 1000104003,
    DciP3NonlinearEXT = 1000104004,
    Bt709LinearEXT = 1000104005,
    Bt709NonlinearEXT = 1000104006,
    Bt2020LinearEXT = 1000104007,
}

public enum CompositeAlphaFlagBitsKHR
{
    Opaque = 0x00000001,
    PreMultiplied = 0x00000002,
    PostMultiplied = 0x00000004,
    Inherit = 0x00000008,
}

public enum BorderColor
{
    FloatTransparentBlack = 0,
    IntTransparentBlack = 1,
    FloatOpaqueBlack = 2,
    IntOpaqueBlack = 3,
    FloatOpaqueWhite = 4,
    IntOpaqueWhite = 5,
}

public enum DescriptorType
{
    Sampler = 0,
    CombinedImageSampler = 1,
    SampledImage = 2,
    StorageImage = 3,
    UniformTexelBuffer = 4,
    StorageTexelBuffer = 5,
    UniformBuffer = 6,
    StorageBuffer = 7,
    UniformBufferDynamic = 8,
    StorageBufferDynamic = 9,
    InputAttachment = 10,
}

public enum ObjectType
{
    Unknown = 0,
    Instance = 1,
    PhysicalDevice = 2,
    Device = 3,
    Queue = 4,
    Semaphore = 5,
    CommandBuffer = 6,
    Fence = 7,
    DeviceMemory = 8,
    Buffer = 9,
    Image = 10,
    Event = 11,
    QueryPool = 12,
    BufferView = 13,
    ImageView = 14,
    ShaderModule = 15,
    PipelineCache = 16,
    PipelineLayout = 17,
    RenderPass = 18,
    Pipeline = 19,
    DescriptorSetLayout = 20,
    Sampler = 21,
    DescriptorPool = 22,
    DescriptorSet = 23,
    Framebuffer = 24,
    CommandPool = 25,
    SurfaceKHR = 1000000000,
    SwapchainKHR = 1000001000,
    DebugReportCallbackEXT = 1000011000,
    DebugUtilsMessengerEXT = 1000128000,
}

public enum AccessFlagBits
{
    IndirectCommandRead = 0x00000001,
    IndexRead = 0x00000002,
    VertexAttributeRead = 0x00000004,
    UniformRead = 0x00000008,
    InputAttachmentRead = 0x00000010,
    ShaderRead = 0x00000020,
    ShaderWrite = 0x00000040,
    ColorAttachmentRead = 0x00000080,
    ColorAttachmentWrite = 0x00000100,
    DepthStencilAttachmentRead = 0x00000200,
    DepthStencilAttachmentWrite = 0x00000400,
    TransferRead = 0x00000800,
    TransferWrite = 0x00001000,
    HostRead = 0x00002000,
    HostWrite = 0x00004000,
    MemoryRead = 0x00008000,
    MemoryWrite = 0x00010000,
}

public enum AccessFlagBits2
{
    None = 0,
    IndirectCommandRead = 0x00000001,
    IndexRead = 0x00000002,
    VertexAttributeRead = 0x00000004,
    UniformRead = 0x00000008,
    InputAttachmentRead = 0x00000010,
    ShaderRead = 0x00000020,
    ShaderWrite = 0x00000040,
    ColorAttachmentRead = 0x00000080,
    ColorAttachmentWrite = 0x00000100,
    DepthStencilAttachmentRead = 0x00000200,
    DepthStencilAttachmentWrite = 0x00000400,
    TransferRead = 0x00000800,
    TransferWrite = 0x00001000,
    HostRead = 0x00002000,
    HostWrite = 0x00004000,
    MemoryRead = 0x00008000,
    MemoryWrite = 0x00010000,
}

public enum AccessFlagBits2KHR
{
    None = 0,
}

public enum ColorComponentFlagBits
{
    R = 0x00000001,
    G = 0x00000002,
    B = 0x00000004,
    A = 0x00000008,
}

public enum DependencyFlagBits
{
    ByRegion = 0x00000001,
    ViewLocal = 0x00000002,
    DeviceGroup = 0x00000004,
    FeedbackLoopEXT = 0x00000008,
}

public enum DescriptorPoolCreateFlagBits
{
    FreeDescriptorSet = 0x00000001,
    UpdateAfterBind = 0x00000002,
    HostOnlyVALVE = 0x00000004,
}

public enum DescriptorSetLayoutCreateFlagBits
{
    PushDescriptorKHR = 0x00000001,
    UpdateAfterBindPool = 0x00000002,
}

public enum FenceCreateFlagBits
{
    Signaled = 0x00000001,
}

public enum ImageCreateFlagBits
{
    SparseBinding = 0x00000001,
    SparseResidency = 0x00000002,
    SparseAliased = 0x00000004,
    MutableFormat = 0x00000008,
    CubeCompatible = 0x00000010,
    SplitInstanceBindRegions = 0x00000040,
    Array2DCompatible = 0x00000020,
    Alias = 0x00000400,
}

public enum ImageUsageFlagBits
{
    TransferSrc = 0x00000001,
    TransferDst = 0x00000002,
    Sampled = 0x00000004,
    Storage = 0x00000008,
    ColorAttachment = 0x00000010,
    DepthStencilAttachment = 0x00000020,
    TransientAttachment = 0x00000040,
    InputAttachment = 0x00000080,
}

public enum PipelineStageFlagBits
{
    TopOfPipe = 0x00000001,
    DrawIndirect = 0x00000002,
    VertexInput = 0x00000004,
    VertexShader = 0x00000008,
    FragmentShader = 0x00000080,
    EarlyFragmentTests = 0x00000100,
    LateFragmentTests = 0x00000200,
    ColorAttachmentOutput = 0x00000400,
    ComputeShader = 0x00000800,
    Transfer = 0x00001000,
    BottomOfPipe = 0x00002000,
    Host = 0x00004000,
    AllGraphics = 0x00008000,
    AllCommands = 0x00010000,
}

public enum PipelineStageFlagBits2
{
    None = 0,
}

public enum QueryControlFlagBits
{
    Precise = 0x00000001,
}

public enum QueryResultFlagBits
{
    Type64 = 0x00000001,
    Wait = 0x00000002,
    WithAvailability = 0x00000004,
    Partial = 0x00000008,
    WithStatusKHR = 0x00000010,
}

public enum DebugReportObjectTypeEXT
{
    Unknown = 0,
    Instance = 1,
    PhysicalDevice = 2,
    Device = 3,
    Queue = 4,
}

public enum DebugUtilsMessageSeverityFlagBitsEXT
{
    Verbose = 0x00000001,
    Info = 0x00000010,
    Warning = 0x00000100,
    Error = 0x00001000,
}

public enum DebugUtilsMessageTypeFlagBitsEXT
{
    General = 0x00000001,
    Validation = 0x00000002,
    Performance = 0x00000004,
    DeviceAddressBinding = 0x00000008,
}

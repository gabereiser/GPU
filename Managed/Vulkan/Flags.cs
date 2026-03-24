using System;

namespace GPU;

[Flags]
public enum SampleCountFlags : uint
{
    Count1 = 0x00000001,
    Count2 = 0x00000002,
    Count4 = 0x00000004,
    Count8 = 0x00000008,
    Count16 = 0x00000010,
    Count32 = 0x00000020,
    Count64 = 0x00000040,
}

[Flags]
public enum ShaderStageFlags : uint
{
    Vertex = 0x00000001,
    TessellationControl = 0x00000002,
    TessellationEvaluation = 0x00000004,
    Geometry = 0x00000008,
    Fragment = 0x00000010,
    Compute = 0x00000020,
    AllGraphics = 0x0000001F,
    All = 0x7FFFFFFF,
}

[Flags]
public enum CullModeFlags : uint
{
    None = 0,
    Front = 0x00000001,
    Back = 0x00000002,
    FrontAndBack = 0x00000003,
}

[Flags]
public enum ColorComponentFlags : uint
{
    R = 0x00000001,
    G = 0x00000002,
    B = 0x00000004,
    A = 0x00000008,
}

[Flags]
public enum ImageUsageFlags : uint
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

[Flags]
public enum ImageCreateFlags : uint
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

[Flags]
public enum BufferUsageFlags : uint
{
    TransferSrc = 0x00000001,
    TransferDst = 0x00000002,
    UniformTexelBuffer = 0x00000004,
    StorageTexelBuffer = 0x00000008,
    UniformBuffer = 0x00000010,
    StorageBuffer = 0x00000020,
    IndexBuffer = 0x00000040,
    VertexBuffer = 0x00000080,
    IndirectBuffer = 0x00000100,
}

[Flags]
public enum CommandPoolCreateFlags : uint
{
    Transient = 0x00000001,
    ResetCommandBuffer = 0x00000002,
    Protected = 0x00000004,
}

[Flags]
public enum DescriptorSetLayoutCreateFlags : uint
{
    PushDescriptorKHR = 0x00000001,
    UpdateAfterBindPool = 0x00000002,
}

[Flags]
public enum DescriptorPoolCreateFlags : uint
{
    FreeDescriptorSet = 0x00000001,
    UpdateAfterBind = 0x00000002,
    HostOnlyVALVE = 0x00000004,
}

[Flags]
public enum PipelineStageFlags : uint
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

[Flags]
public enum PipelineStageFlags2 : ulong
{
    None = 0,
    TopOfPipe = 0x00000001UL,
    DrawIndirect = 0x00000002UL,
    VertexInput = 0x00000004UL,
    VertexShader = 0x00000008UL,
    FragmentShader = 0x00000080UL,
    EarlyFragmentTests = 0x00000100UL,
    LateFragmentTests = 0x00000200UL,
    ColorAttachmentOutput = 0x00000400UL,
    ComputeShader = 0x00000800UL,
    Transfer = 0x00001000UL,
    BottomOfPipe = 0x00002000UL,
    Host = 0x00004000UL,
    AllGraphics = 0x00008000UL,
    AllCommands = 0x00010000UL,
}

[Flags]
public enum DependencyFlags : uint
{
    ByRegion = 0x00000001,
    ViewLocal = 0x00000002,
    DeviceGroup = 0x00000004,
    FeedbackLoopEXT = 0x00000008,
}

[Flags]
public enum QueryControlFlags : uint
{
    Precise = 0x00000001,
}

[Flags]
public enum QueryResultFlags : uint
{
    Type64 = 0x00000001,
    Wait = 0x00000002,
    WithAvailability = 0x00000004,
    Partial = 0x00000008,
    WithStatusKHR = 0x00000010,
}

[Flags]
public enum CommandBufferUsageFlags : uint
{
    OneTimeSubmit = 0x00000001,
    RenderPassContinue = 0x00000002,
    SimultaneousUse = 0x00000004,
}

[Flags]
public enum FenceCreateFlags : uint
{
    Signaled = 0x00000001,
}

[Flags]
public enum AccessFlags : uint
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

[Flags]
public enum AccessFlags2 : ulong
{
    None = 0,
}

[Flags]
public enum AccessFlags2KHR : ulong
{
    None = 0,
}

[Flags]
public enum CommandBufferResetFlags : uint
{
    ReleaseResources = 0x00000001,
}

[Flags]
public enum CommandPoolResetFlags : uint
{
    ReleaseResources = 0x00000001,
}

[Flags]
public enum CommandPoolTrimFlags : uint
{
    None = 0,
}

[Flags]
public enum CompositeAlphaFlagsKHR : uint
{
    Opaque = 0x00000001,
    PreMultiplied = 0x00000002,
    PostMultiplied = 0x00000004,
    Inherit = 0x00000008,
}

[Flags]
public enum ExternalMemoryHandleTypeFlagsNV : uint
{
    OpaqueWin32 = 0x00000001,
    OpaqueWin32Kmt = 0x00000002,
    OpaqueFd = 0x00000004,
    D3D11Image = 0x00000008,
    D3D11ImageKmt = 0x00000010,
}

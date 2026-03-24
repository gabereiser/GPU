using System.Runtime.InteropServices;

namespace GPU;

[StructLayout(LayoutKind.Sequential)]
public struct MemoryRequirements
{
    public DeviceSize Size;
    public DeviceSize Alignment;
    public uint MemoryTypeBits;
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryRequirements2
{
    public StructureType SType;
    public nint PNext;
    public MemoryRequirements MemoryRequirements;
}

[StructLayout(LayoutKind.Sequential)]
public struct BufferDeviceAddressInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint Buffer;
}

[StructLayout(LayoutKind.Sequential)]
public struct Offset3D
{
    public int X;
    public int Y;
    public int Z;
}

[StructLayout(LayoutKind.Sequential)]
public struct Viewport
{
    public float X;
    public float Y;
    public float Width;
    public float Height;
    public float MinDepth;
    public float MaxDepth;
}

[StructLayout(LayoutKind.Sequential)]
public struct ClearColorValue
{
    public float Float32_0;
    public float Float32_1;
    public float Float32_2;
    public float Float32_3;
}

[StructLayout(LayoutKind.Sequential)]
public struct ClearDepthStencilValue
{
    public float Depth;
    public uint Stencil;
}

[StructLayout(LayoutKind.Sequential)]
public struct ClearValue
{
    public ClearColorValue Color;
}

[StructLayout(LayoutKind.Sequential)]
public struct DebugUtilsLabelEXT
{
    public StructureType SType;
    public nint PNext;
    public nint PLabelName;
    public float Color_0;
    public float Color_1;
    public float Color_2;
    public float Color_3;
}

[StructLayout(LayoutKind.Sequential)]
public struct SubpassBeginInfo
{
    public StructureType SType;
    public nint PNext;
    public SubpassContents Contents;
}

[StructLayout(LayoutKind.Sequential)]
public struct SubpassEndInfo
{
    public StructureType SType;
    public nint PNext;
}

[StructLayout(LayoutKind.Sequential)]
public struct RenderingAttachmentInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint ImageView;
    public ImageLayout ImageLayout;
    public uint ResolveMode;
    public nuint ResolveImageView;
    public ImageLayout ResolveImageLayout;
    public uint LoadOp;
    public uint StoreOp;
    public ClearValue ClearValue;
}

[StructLayout(LayoutKind.Sequential)]
public struct RenderingInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public Rect2D RenderArea;
    public uint LayerCount;
    public uint ViewMask;
    public uint ColorAttachmentCount;
    public nint PColorAttachments;
    public nint PDepthAttachment;
    public nint PStencilAttachment;
}

[StructLayout(LayoutKind.Sequential)]
public struct MappedMemoryRange
{
    public StructureType SType;
    public nint PNext;
    public nuint Memory;
    public DeviceSize Offset;
    public DeviceSize Size;
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryMapInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint Memory;
    public DeviceSize Offset;
    public DeviceSize Size;
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryUnmapInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public nuint Memory;
}

[StructLayout(LayoutKind.Sequential)]
public struct SemaphoreSignalInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint Semaphore;
    public ulong Value;
}

[StructLayout(LayoutKind.Sequential)]
public struct SemaphoreWaitInfo
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint SemaphoreCount;
    public nint PSemaphores;
    public nint PValues;
}

[StructLayout(LayoutKind.Sequential)]
public struct SemaphoreSubmitInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint Semaphore;
    public ulong Value;
    public PipelineStageFlags2 StageMask;
    public uint DeviceIndex;
}

[StructLayout(LayoutKind.Sequential)]
public struct CommandBufferSubmitInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint CommandBuffer;
    public uint DeviceMask;
}

[StructLayout(LayoutKind.Sequential)]
public struct SubmitInfo2
{
    public StructureType SType;
    public nint PNext;
    public uint Flags;
    public uint WaitSemaphoreInfoCount;
    public nint PWaitSemaphoreInfos;
    public uint CommandBufferInfoCount;
    public nint PCommandBufferInfos;
    public uint SignalSemaphoreInfoCount;
    public nint PSignalSemaphoreInfos;
}

[StructLayout(LayoutKind.Sequential)]
public struct BindBufferMemoryInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint Buffer;
    public nuint Memory;
    public DeviceSize MemoryOffset;
}

[StructLayout(LayoutKind.Sequential)]
public struct BindImageMemoryInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint Image;
    public nuint Memory;
    public DeviceSize MemoryOffset;
}

[StructLayout(LayoutKind.Sequential)]
public struct BindDescriptorSetsInfo
{
    public StructureType SType;
    public nint PNext;
    public nint StageFlags;
    public nuint Layout;
    public uint FirstSet;
    public uint DescriptorSetCount;
    public nint PDescriptorSets;
    public uint DynamicOffsetCount;
    public nint PDynamicOffsets;
}

[StructLayout(LayoutKind.Sequential)]
public struct HostImageLayoutTransitionInfo
{
    public StructureType SType;
    public nint PNext;
    public nuint Image;
    public ImageLayout OldLayout;
    public ImageLayout NewLayout;
    public ImageSubresourceRange SubresourceRange;
}

[StructLayout(LayoutKind.Sequential)]
public struct StridedDeviceAddressRegionKHR
{
    public DeviceAddress DeviceAddress;
    public DeviceSize Stride;
    public DeviceSize Size;
}

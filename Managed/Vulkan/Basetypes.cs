namespace GPU;

public readonly struct Bool32
{
    public Bool32(uint value) => Value = value;

    public uint Value { get; }

    public static implicit operator Bool32(bool value) => new(value ? 1u : 0u);
    public static implicit operator bool(Bool32 value) => value.Value != 0;
}

public readonly struct DeviceAddress
{
    public DeviceAddress(ulong value) => Value = value;

    public ulong Value { get; }
}

public readonly struct DeviceSize
{
    public DeviceSize(ulong value) => Value = value;

    public ulong Value { get; }
}

public readonly struct Flags
{
    public Flags(uint value) => Value = value;

    public uint Value { get; }
}

public readonly struct Flags64
{
    public Flags64(ulong value) => Value = value;

    public ulong Value { get; }
}

public readonly struct SampleMask
{
    public SampleMask(uint value) => Value = value;

    public uint Value { get; }
}

public readonly struct RemoteAddressNV
{
    public RemoteAddressNV(ulong value) => Value = value;

    public ulong Value { get; }
}

public readonly struct AHardwareBuffer
{
    public AHardwareBuffer(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct ANativeWindow
{
    public ANativeWindow(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct CAMetalLayer
{
    public CAMetalLayer(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct IOSurfaceRef
{
    public IOSurfaceRef(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct MTLBuffer_id
{
    public MTLBuffer_id(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct MTLCommandQueue_id
{
    public MTLCommandQueue_id(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct MTLDevice_id
{
    public MTLDevice_id(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct MTLSharedEvent_id
{
    public MTLSharedEvent_id(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct MTLTexture_id
{
    public MTLTexture_id(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct OHBufferHandle
{
    public OHBufferHandle(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct OHNativeWindow
{
    public OHNativeWindow(nint handle) => Handle = handle;

    public nint Handle { get; }
}

public readonly struct OH_NativeBuffer
{
    public OH_NativeBuffer(nint handle) => Handle = handle;

    public nint Handle { get; }
}

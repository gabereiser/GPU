namespace GPU;

public sealed class MicromapEXT : IDisposable
{
    private MicromapEXTHandle _handle;
    internal MicromapEXT(MicromapEXTHandle handle) => _handle = handle;
    public bool IsDisposed => _handle.IsNull;
    public nuint VkHandle { get { ThrowIfDisposed(); unsafe { return Library.Api.gpuMicromapEXTGetVkHandle(_handle.Value); } } }
    public DeviceHandle DeviceHandle { get { ThrowIfDisposed(); unsafe { return new DeviceHandle(Library.Api.gpuMicromapEXTGetDevice(_handle.Value)); } } }
    public void Dispose() { if (_handle.IsNull) return; unsafe { Library.Api.gpuMicromapEXTDestroy(_handle.Value); } _handle = new MicromapEXTHandle(nint.Zero); }
    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

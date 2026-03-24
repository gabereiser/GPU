namespace GPU;

public sealed class BufferCollectionFUCHSIA : IDisposable
{
    private BufferCollectionFUCHSIAHandle _handle;
    internal BufferCollectionFUCHSIA(BufferCollectionFUCHSIAHandle handle) => _handle = handle;
    public bool IsDisposed => _handle.IsNull;
    public nuint VkHandle { get { ThrowIfDisposed(); unsafe { return Library.Api.gpuBufferCollectionFUCHSIAGetVkHandle(_handle.Value); } } }
    public DeviceHandle DeviceHandle { get { ThrowIfDisposed(); unsafe { return new DeviceHandle(Library.Api.gpuBufferCollectionFUCHSIAGetDevice(_handle.Value)); } } }
    public void Dispose() { if (_handle.IsNull) return; unsafe { Library.Api.gpuBufferCollectionFUCHSIADestroy(_handle.Value); } _handle = new BufferCollectionFUCHSIAHandle(nint.Zero); }
    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

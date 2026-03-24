namespace GPU;

public sealed class AccelerationStructureNV : IDisposable
{
    private AccelerationStructureNVHandle _handle;
    internal AccelerationStructureNV(AccelerationStructureNVHandle handle) => _handle = handle;
    public bool IsDisposed => _handle.IsNull;
    public nuint VkHandle { get { ThrowIfDisposed(); unsafe { return Library.Api.gpuAccelerationStructureNVGetVkHandle(_handle.Value); } } }
    public DeviceHandle DeviceHandle { get { ThrowIfDisposed(); unsafe { return new DeviceHandle(Library.Api.gpuAccelerationStructureNVGetDevice(_handle.Value)); } } }
    public void Dispose() { if (_handle.IsNull) return; unsafe { Library.Api.gpuAccelerationStructureNVDestroy(_handle.Value); } _handle = new AccelerationStructureNVHandle(nint.Zero); }
    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

namespace GPU;

public sealed class AccelerationStructureKHR : IDisposable
{
    private AccelerationStructureKHRHandle _handle;
    internal AccelerationStructureKHR(AccelerationStructureKHRHandle handle) => _handle = handle;
    public bool IsDisposed => _handle.IsNull;
    public nuint VkHandle { get { ThrowIfDisposed(); unsafe { return Library.Api.gpuAccelerationStructureKHRGetVkHandle(_handle.Value); } } }
    public DeviceHandle DeviceHandle { get { ThrowIfDisposed(); unsafe { return new DeviceHandle(Library.Api.gpuAccelerationStructureKHRGetDevice(_handle.Value)); } } }
    public void Dispose() { if (_handle.IsNull) return; unsafe { Library.Api.gpuAccelerationStructureKHRDestroy(_handle.Value); } _handle = new AccelerationStructureKHRHandle(nint.Zero); }
    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

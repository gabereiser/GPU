namespace GPU;

public sealed class PerformanceConfigurationINTEL : IDisposable
{
    private PerformanceConfigurationINTELHandle _handle;
    internal PerformanceConfigurationINTEL(PerformanceConfigurationINTELHandle handle) => _handle = handle;
    public bool IsDisposed => _handle.IsNull;
    public nuint VkHandle { get { ThrowIfDisposed(); unsafe { return Library.Api.gpuPerformanceConfigurationINTELGetVkHandle(_handle.Value); } } }
    public DeviceHandle DeviceHandle { get { ThrowIfDisposed(); unsafe { return new DeviceHandle(Library.Api.gpuPerformanceConfigurationINTELGetDevice(_handle.Value)); } } }
    public void Dispose() { if (_handle.IsNull) return; unsafe { Library.Api.gpuPerformanceConfigurationINTELRelease(_handle.Value); } _handle = new PerformanceConfigurationINTELHandle(nint.Zero); }
    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

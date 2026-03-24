namespace GPU;

public sealed class ExternalComputeQueueNV : IDisposable
{
    private ExternalComputeQueueNVHandle _handle;

    internal ExternalComputeQueueNV(ExternalComputeQueueNVHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuExternalComputeQueueNVGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuExternalComputeQueueNVGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuExternalComputeQueueNVDestroy(_handle.Value);
        }
        _handle = new ExternalComputeQueueNVHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

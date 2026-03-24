namespace GPU;

public sealed class PipelineBinaryKHR : IDisposable
{
    private PipelineBinaryKHRHandle _handle;

    internal PipelineBinaryKHR(PipelineBinaryKHRHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuPipelineBinaryKHRGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuPipelineBinaryKHRGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuPipelineBinaryKHRDestroy(_handle.Value);
        }
        _handle = new PipelineBinaryKHRHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

namespace GPU;

public sealed class VideoSessionParametersKHR : IDisposable
{
    private VideoSessionParametersKHRHandle _handle;

    internal VideoSessionParametersKHR(VideoSessionParametersKHRHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuVideoSessionParametersKHRGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuVideoSessionParametersKHRGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuVideoSessionParametersKHRDestroy(_handle.Value);
        }
        _handle = new VideoSessionParametersKHRHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

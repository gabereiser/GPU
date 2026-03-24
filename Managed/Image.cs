namespace GPU;

public sealed class Image : IDisposable
{
    private ImageHandle _handle;

    internal Image(ImageHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuImageGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuImageGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuImageDestroy(_handle.Value);
        }
        _handle = new ImageHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


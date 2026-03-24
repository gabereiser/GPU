namespace GPU;

public sealed class ImageView : IDisposable
{
    private ImageViewHandle _handle;

    internal ImageView(ImageViewHandle handle)
    {
        _handle = handle;
    }

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuImageViewGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuImageViewGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuImageViewDestroy(_handle.Value);
        }
        _handle = new ImageViewHandle(nint.Zero);
    }

    private void ThrowIfDisposed()
    {
        ObjectDisposedException.ThrowIf(_handle.IsNull, this);
    }
}


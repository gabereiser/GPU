namespace GPU;

public sealed class SwapchainKHR : IDisposable
{
    private SwapchainHandle _handle;

    internal SwapchainKHR(SwapchainHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuSwapchainKHRGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuSwapchainKHRGetDevice(_handle.Value));
            }
        }
    }

    public SurfaceHandle SurfaceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new SurfaceHandle(Library.Api.gpuSwapchainKHRGetSurface(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuSwapchainDestroy(_handle.Value);
        }
        _handle = new SwapchainHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

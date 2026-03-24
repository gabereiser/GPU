namespace GPU;

public sealed class Swapchain : IDisposable
{
    private SwapchainHandle _handle;

    internal Swapchain(SwapchainHandle handle)
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
                return Library.Api.gpuSwapchainGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuSwapchainGetDevice(_handle.Value));
            }
        }
    }

    public SurfaceHandle SurfaceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new SurfaceHandle(Library.Api.gpuSwapchainGetSurface(_handle.Value));
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

    private void ThrowIfDisposed()
    {
        ObjectDisposedException.ThrowIf(_handle.IsNull, this);
    }
}


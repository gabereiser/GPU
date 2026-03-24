namespace GPU;

public sealed class SurfaceKHR : IDisposable
{
    private SurfaceHandle _handle;

    internal SurfaceKHR(SurfaceHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuSurfaceKHRGetVkHandle(_handle.Value);
            }
        }
    }

    public InstanceHandle InstanceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new InstanceHandle(Library.Api.gpuSurfaceKHRGetInstance(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuSurfaceDestroy(_handle.Value);
        }
        _handle = new SurfaceHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

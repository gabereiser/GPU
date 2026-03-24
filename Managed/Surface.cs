namespace GPU;

public sealed class Surface : IDisposable
{
    private SurfaceHandle _handle;

    internal Surface(SurfaceHandle handle)
    {
        _handle = handle;
    }

    internal SurfaceHandle Handle => _handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposedForInterop();
            unsafe {
                return Library.Api.gpuSurfaceGetVkHandle(_handle.Value);
            }
        }
    }

    public InstanceHandle InstanceHandle
    {
        get
        {
            ThrowIfDisposedForInterop();
            unsafe {
                return new InstanceHandle(Library.Api.gpuSurfaceGetInstance(_handle.Value));
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

    internal void ThrowIfDisposedForInterop()
    {
        ObjectDisposedException.ThrowIf(_handle.IsNull, this);
    }
}


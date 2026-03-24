namespace GPU;

public sealed class Fence : IDisposable
{
    private FenceHandle _handle;

    internal Fence(FenceHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuFenceGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuFenceGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuFenceDestroy(_handle.Value);
        }
        _handle = new FenceHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


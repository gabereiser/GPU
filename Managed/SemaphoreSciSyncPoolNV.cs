namespace GPU;

public sealed class SemaphoreSciSyncPoolNV : IDisposable
{
    private SemaphoreSciSyncPoolNVHandle _handle;

    internal SemaphoreSciSyncPoolNV(SemaphoreSciSyncPoolNVHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuSemaphoreSciSyncPoolNVGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuSemaphoreSciSyncPoolNVGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuSemaphoreSciSyncPoolNVDestroy(_handle.Value);
        }
        _handle = new SemaphoreSciSyncPoolNVHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

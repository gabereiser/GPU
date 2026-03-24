namespace GPU;

public sealed class CudaModuleNV : IDisposable
{
    private CudaModuleNVHandle _handle;

    internal CudaModuleNV(CudaModuleNVHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuCudaModuleNVGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuCudaModuleNVGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuCudaModuleNVDestroy(_handle.Value);
        }
        _handle = new CudaModuleNVHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

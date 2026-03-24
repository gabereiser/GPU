namespace GPU;

public sealed class OpticalFlowSessionNV : IDisposable
{
    private OpticalFlowSessionNVHandle _handle;

    internal OpticalFlowSessionNV(OpticalFlowSessionNVHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuOpticalFlowSessionNVGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuOpticalFlowSessionNVGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuOpticalFlowSessionNVDestroy(_handle.Value);
        }
        _handle = new OpticalFlowSessionNVHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

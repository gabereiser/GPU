namespace GPU;

public sealed class PrivateDataSlotEXT : IDisposable
{
    private PrivateDataSlotHandle _handle;

    internal PrivateDataSlotEXT(PrivateDataSlotHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuPrivateDataSlotEXTGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuPrivateDataSlotEXTGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuPrivateDataSlotDestroy(_handle.Value);
        }
        _handle = new PrivateDataSlotHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

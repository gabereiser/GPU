namespace GPU;

public sealed class IndirectCommandsLayoutNV : IDisposable
{
    private IndirectCommandsLayoutNVHandle _handle;

    internal IndirectCommandsLayoutNV(IndirectCommandsLayoutNVHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuIndirectCommandsLayoutNVGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuIndirectCommandsLayoutNVGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuIndirectCommandsLayoutNVDestroy(_handle.Value);
        }
        _handle = new IndirectCommandsLayoutNVHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


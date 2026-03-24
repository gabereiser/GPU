namespace GPU;

public sealed class IndirectExecutionSetEXT : IDisposable
{
    private IndirectExecutionSetEXTHandle _handle;

    internal IndirectExecutionSetEXT(IndirectExecutionSetEXTHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuIndirectExecutionSetEXTGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuIndirectExecutionSetEXTGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuIndirectExecutionSetEXTDestroy(_handle.Value);
        }
        _handle = new IndirectExecutionSetEXTHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


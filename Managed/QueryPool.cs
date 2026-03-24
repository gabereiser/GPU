namespace GPU;

public sealed class QueryPool : IDisposable
{
    private QueryPoolHandle _handle;

    internal QueryPool(QueryPoolHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuQueryPoolGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuQueryPoolGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuQueryPoolDestroy(_handle.Value);
        }
        _handle = new QueryPoolHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


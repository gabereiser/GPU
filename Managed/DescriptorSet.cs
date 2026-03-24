namespace GPU;

public sealed class DescriptorSet : IDisposable
{
    private bool _invalidatedByPool;
    private DescriptorSetHandle _handle;

    internal DescriptorSet(DescriptorSetHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDescriptorSetGetVkHandle(_handle.Value);
            }
        }
    }

    public DescriptorPoolHandle PoolHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DescriptorPoolHandle(Library.Api.gpuDescriptorSetGetPool(_handle.Value));
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuDescriptorSetGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        if (!_invalidatedByPool) {
            unsafe {
                Library.Api.gpuDescriptorSetDestroy(_handle.Value);
            }
        }

        _handle = new DescriptorSetHandle(nint.Zero);
    }

    internal void InvalidateFromPool()
    {
        _invalidatedByPool = true;
        _handle = new DescriptorSetHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


namespace GPU;

public sealed class DescriptorSetLayout : IDisposable
{
    private DescriptorSetLayoutHandle _handle;

    internal DescriptorSetLayout(DescriptorSetLayoutHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDescriptorSetLayoutGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuDescriptorSetLayoutGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuDescriptorSetLayoutDestroy(_handle.Value);
        }
        _handle = new DescriptorSetLayoutHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


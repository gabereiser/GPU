namespace GPU;

public sealed class DescriptorUpdateTemplate : IDisposable
{
    private DescriptorUpdateTemplateHandle _handle;

    internal DescriptorUpdateTemplate(DescriptorUpdateTemplateHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDescriptorUpdateTemplateGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuDescriptorUpdateTemplateGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuDescriptorUpdateTemplateDestroy(_handle.Value);
        }
        _handle = new DescriptorUpdateTemplateHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


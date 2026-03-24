namespace GPU;

public sealed class SamplerYcbcrConversionKHR : IDisposable
{
    private SamplerYcbcrConversionHandle _handle;

    internal SamplerYcbcrConversionKHR(SamplerYcbcrConversionHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuSamplerYcbcrConversionKHRGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuSamplerYcbcrConversionKHRGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuSamplerYcbcrConversionDestroy(_handle.Value);
        }
        _handle = new SamplerYcbcrConversionHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

namespace GPU;

public sealed class PipelineCache : IDisposable
{
    private PipelineCacheHandle _handle;

    internal PipelineCache(PipelineCacheHandle handle) => _handle = handle;

    internal PipelineCacheHandle Handle => _handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuPipelineCacheGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuPipelineCacheGetDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuPipelineCacheDestroy(_handle.Value);
        }
        _handle = new PipelineCacheHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


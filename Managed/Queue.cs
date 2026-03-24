namespace GPU;

public sealed class Queue : IDisposable
{
    private QueueHandle _handle;

    internal Queue(QueueHandle handle)
    {
        _handle = handle;
    }

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuQueueGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuQueueGetDevice(_handle.Value));
            }
        }
    }

    public uint FamilyIndex
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuQueueGetFamilyIndex(_handle.Value);
            }
        }
    }

    public uint QueueIndex
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuQueueGetQueueIndex(_handle.Value);
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuQueueRelease(_handle.Value);
        }
        _handle = new QueueHandle(nint.Zero);
    }

    private void ThrowIfDisposed()
    {
        ObjectDisposedException.ThrowIf(_handle.IsNull, this);
    }
}


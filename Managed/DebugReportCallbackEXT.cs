namespace GPU;

public sealed class DebugReportCallbackEXT : IDisposable
{
    private DebugReportCallbackEXTHandle _handle;

    internal DebugReportCallbackEXT(DebugReportCallbackEXTHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDebugReportCallbackEXTGetVkHandle(_handle.Value);
            }
        }
    }

    public InstanceHandle InstanceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new InstanceHandle(Library.Api.gpuDebugReportCallbackEXTGetInstance(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuDebugReportCallbackEXTDestroy(_handle.Value);
        }
        _handle = new DebugReportCallbackEXTHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


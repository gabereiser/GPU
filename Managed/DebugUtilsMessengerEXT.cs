namespace GPU;

public sealed class DebugUtilsMessengerEXT : IDisposable
{
    private DebugUtilsMessengerEXTHandle _handle;

    internal DebugUtilsMessengerEXT(DebugUtilsMessengerEXTHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDebugUtilsMessengerEXTGetVkHandle(_handle.Value);
            }
        }
    }

    public InstanceHandle InstanceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new InstanceHandle(Library.Api.gpuDebugUtilsMessengerEXTGetInstance(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuDebugUtilsMessengerEXTDestroy(_handle.Value);
        }
        _handle = new DebugUtilsMessengerEXTHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


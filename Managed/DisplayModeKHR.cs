namespace GPU;

public sealed class DisplayModeKHR : IDisposable
{
    private DisplayModeKHRHandle _handle;

    internal DisplayModeKHR(DisplayModeKHRHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDisplayModeKHRGetVkHandle(_handle.Value);
            }
        }
    }

    public DisplayKHRHandle DisplayHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DisplayKHRHandle(Library.Api.gpuDisplayModeKHRGetDisplayKHR(_handle.Value));
            }
        }
    }

    public PhysicalDeviceHandle PhysicalDeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new PhysicalDeviceHandle(Library.Api.gpuDisplayModeKHRGetPhysicalDevice(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuDisplayModeKHRRelease(_handle.Value);
        }
        _handle = new DisplayModeKHRHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

namespace GPU;

public sealed class DisplayKHR : IDisposable
{
    private DisplayKHRHandle _handle;

    internal DisplayKHR(DisplayKHRHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDisplayKHRGetVkHandle(_handle.Value);
            }
        }
    }

    public PhysicalDeviceHandle PhysicalDeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new PhysicalDeviceHandle(Library.Api.gpuDisplayKHRGetPhysicalDevice(_handle.Value));
            }
        }
    }

    public uint GetModeCountKHR()
    {
        ThrowIfDisposed();
        unsafe {
            return Library.Api.gpuDisplayKHRGetModeCountKHR(_handle.Value);
        }
    }

    public DisplayModeKHR GetModeKHR(uint index)
    {
        ThrowIfDisposed();
        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuDisplayKHRGetModeKHR(_handle.Value, index, &handle);
            Library.ThrowIfFailed(result, "Failed to get display mode.");
            return new DisplayModeKHR(new DisplayModeKHRHandle(handle));
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuDisplayKHRRelease(_handle.Value);
        }
        _handle = new DisplayKHRHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}

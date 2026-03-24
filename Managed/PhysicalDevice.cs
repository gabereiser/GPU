namespace GPU;

public sealed class PhysicalDevice : IDisposable
{
    private PhysicalDeviceHandle _handle;

    internal PhysicalDevice(PhysicalDeviceHandle handle)
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
                return Library.Api.gpuPhysicalDeviceGetVkHandle(_handle.Value);
            }
        }
    }

    public InstanceHandle InstanceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new InstanceHandle(Library.Api.gpuPhysicalDeviceGetInstance(_handle.Value));
            }
        }
    }

    public uint GetDisplayCountKHR()
    {
        ThrowIfDisposed();
        unsafe {
            return Library.Api.gpuPhysicalDeviceGetDisplayCountKHR(_handle.Value);
        }
    }

    public DisplayKHR GetDisplayKHR(uint index)
    {
        ThrowIfDisposed();

        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuPhysicalDeviceGetDisplayKHR(_handle.Value, index, &handle);
            Library.ThrowIfFailed(result, "Failed to get display.");
            return new DisplayKHR(new DisplayKHRHandle(handle));
        }
    }

    internal Device CreateDevice(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceCore((void*)createInfo, (void*)allocator);
        }
    }

    public Device CreateDevice<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateDeviceCore(createInfoPtr, (void*)allocator);
            }
        }
    }

    public Device CreateDevice<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateDeviceCore(createInfoPtr, allocatorPtr);
            }
        }
    }

    internal unsafe Device CreateDeviceCore(void* createInfo, void* allocator)
    {
        ThrowIfDisposed();

        nint handle = nint.Zero;
        Result result = Library.Api.gpuDeviceCreate(_handle.Value, createInfo, allocator, &handle);
        Library.ThrowIfFailed(result, "Failed to create device.");
        return new Device(new DeviceHandle(handle));
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuPhysicalDeviceRelease(_handle.Value);
        }
        _handle = new PhysicalDeviceHandle(nint.Zero);
    }

    private void ThrowIfDisposed()
    {
        ObjectDisposedException.ThrowIf(_handle.IsNull, this);
    }
}


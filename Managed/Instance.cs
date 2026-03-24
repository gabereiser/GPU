namespace GPU;

public sealed class Instance : IDisposable
{
    private InstanceHandle _handle;

    internal Instance(InstanceHandle handle)
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
                return Library.Api.gpuInstanceGetVkHandle(_handle.Value);
            }
        }
    }

    public uint PhysicalDeviceCount
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuInstanceGetPhysicalDeviceCount(_handle.Value);
            }
        }
    }

    public PhysicalDevice GetPhysicalDevice(uint index)
    {
        ThrowIfDisposed();

        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuInstanceGetPhysicalDevice(_handle.Value, index, &handle);
            Library.ThrowIfFailed(result, "Failed to get physical device.");
            return new PhysicalDevice(new PhysicalDeviceHandle(handle));
        }
    }

    public Surface CreateSurfaceGlfw(nint glfwWindow, nint allocator = 0)
    {
        ThrowIfDisposed();

        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuSurfaceCreateGlfw(_handle.Value, glfwWindow, (void*)allocator, &handle);
            Library.ThrowIfFailed(result, "Failed to create surface.");
            return new Surface(new SurfaceHandle(handle));
        }
    }

    public SurfaceKHR CreateSurfaceKHRGlfw(nint glfwWindow, nint allocator = 0)
    {
        ThrowIfDisposed();

        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuSurfaceCreateGlfw(_handle.Value, glfwWindow, (void*)allocator, &handle);
            Library.ThrowIfFailed(result, "Failed to create surface KHR.");
            return new SurfaceKHR(new SurfaceHandle(handle));
        }
    }

    internal DebugReportCallbackEXT CreateDebugReportCallbackEXT(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDebugReportCallbackEXTCore((void*)createInfo, (void*)allocator);
        }
    }

    public DebugReportCallbackEXT CreateDebugReportCallbackEXT<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateDebugReportCallbackEXTCore(createInfoPtr, (void*)allocator);
            }
        }
    }

    public DebugReportCallbackEXT CreateDebugReportCallbackEXT<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateDebugReportCallbackEXTCore(createInfoPtr, allocatorPtr);
            }
        }
    }

    internal DebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDebugUtilsMessengerEXTCore((void*)createInfo, (void*)allocator);
        }
    }

    public DebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateDebugUtilsMessengerEXTCore(createInfoPtr, (void*)allocator);
            }
        }
    }

    public DebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateDebugUtilsMessengerEXTCore(createInfoPtr, allocatorPtr);
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuInstanceDestroy(_handle.Value);
        }
        _handle = new InstanceHandle(nint.Zero);
    }

    private void ThrowIfDisposed()
    {
        ObjectDisposedException.ThrowIf(_handle.IsNull, this);
    }

    private unsafe DebugReportCallbackEXT CreateDebugReportCallbackEXTCore(void* createInfo, void* allocator)
    {
        ThrowIfDisposed();

        nint handle = nint.Zero;
        Result result = Library.Api.gpuDebugReportCallbackEXTCreate(_handle.Value, createInfo, allocator, &handle);
        Library.ThrowIfFailed(result, "Failed to create debug report callback.");
        return new DebugReportCallbackEXT(new DebugReportCallbackEXTHandle(handle));
    }

    private unsafe DebugUtilsMessengerEXT CreateDebugUtilsMessengerEXTCore(void* createInfo, void* allocator)
    {
        ThrowIfDisposed();

        nint handle = nint.Zero;
        Result result = Library.Api.gpuDebugUtilsMessengerEXTCreate(_handle.Value, createInfo, allocator, &handle);
        Library.ThrowIfFailed(result, "Failed to create debug utils messenger.");
        return new DebugUtilsMessengerEXT(new DebugUtilsMessengerEXTHandle(handle));
    }
}


using System.Runtime.InteropServices;
using System.Text;

namespace GPU;

public static class Library
{
    private static readonly ApiState s_api = LoadApi();

    internal static NativeApi Api => s_api.Api;
    public static string LibraryPath => s_api.LibraryPath;

    public static uint GetApiVersion()
    {
        unsafe {
            return Api.gpuGetApiVersion();
        }
    }

    public static string? GetLastError()
    {
        return GetLastErrorCore();
    }

    public static string[] GetRequiredInstanceExtensions()
    {
        unsafe {
            byte** extensions = null;
            uint count = 0;
            int result = Api.gpuGetRequiredInstanceExtensions(&extensions, &count);
            if (result == 0) {
                throw new GpuException(GetLastErrorCore() ?? "Failed to get required instance extensions.", Result.ErrorInitializationFailed);
            }

            string[] values = new string[count];
            for (int i = 0; i < count; ++i) {
                values[i] = Marshal.PtrToStringUTF8((nint)extensions[i]) ?? string.Empty;
            }

            return values;
        }
    }

    public static FramebufferSize GetFramebufferSizeGlfw(nint glfwWindow)
    {
        unsafe {
            uint width = 0;
            uint height = 0;
            int result = Api.gpuGetFramebufferSizeGlfw(glfwWindow, &width, &height);
            if (result == 0) {
                throw new GpuException(GetLastErrorCore() ?? "Failed to get framebuffer size.", Result.ErrorInitializationFailed);
            }

            return new FramebufferSize(width, height);
        }
    }

    internal static Instance CreateInstance(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateInstanceCore((void*)createInfo, (void*)allocator);
        }
    }

    public static Instance CreateInstance<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateInstanceCore(createInfoPtr, (void*)allocator);
            }
        }
    }

    public static Instance CreateInstance<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateInstanceCore(createInfoPtr, allocatorPtr);
            }
        }
    }

    internal static unsafe Instance CreateInstanceCore(void* createInfo, void* allocator)
    {
        nint handle = nint.Zero;
        Result result = Api.gpuInstanceCreate(createInfo, allocator, &handle);
        ThrowIfFailed(result, "Failed to create instance.");
        return new Instance(new InstanceHandle(handle));
    }

    internal static void ThrowIfFailed(Result result, string fallbackMessage)
    {
        if (result == Result.Success) {
            return;
        }

        string message = GetLastErrorCore() ?? fallbackMessage;
        throw new GpuException(message, result);
    }

    private static unsafe string? GetLastErrorCore()
    {
        byte* message = Api.gpuGetLastError();
        return message == null ? null : Marshal.PtrToStringUTF8((nint)message);
    }

    private static ApiState LoadApi()
    {
        string libraryPath = GetDefaultLibraryName();
        nint moduleHandle = NativeLibrary.Load(libraryPath);
        unsafe {
            return new ApiState(libraryPath, new NativeApi(moduleHandle));
        }
    }

    private static string GetDefaultLibraryName()
    {
        if (OperatingSystem.IsWindows()) {
            return "GPU.dll";
        }

        if (OperatingSystem.IsMacOS()) {
            return "libGPU.dylib";
        }

        return "libGPU.so";
    }

    private readonly struct ApiState
    {
        public ApiState(string libraryPath, NativeApi api)
        {
            LibraryPath = libraryPath;
            Api = api;
        }

        public string LibraryPath { get; }
        public NativeApi Api { get; }
    }
}


# GPU

`GPU` is a native Vulkan wrapper library (thin C ABI) with a matching .NET layer. It forwards Vulkan structures to the Vulkan loader, so examples use Vulkan structs while calling through the `GPU` API.

The goal is simple: keep the API close to GPU, keep ownership rules explicit, and make the library usable from C# without inventing a new rendering model.

## What This Repo Contains

- A native C ABI for GPU-oriented work
- A broad object wrapper layer for GPU handles and lifetimes
- A generated GPU command surface in [gpu_vulkan.h](include/gpu/gpu_vulkan.h)
- A managed .NET wrapper in [Managed/GPU.Managed.csproj](Managed/GPU.Managed.csproj)

This project is not a renderer, engine, or scene framework. It is a low-level foundation for people who want a stable native boundary and a usable managed interop layer.

## Design Goals

- Stay close to GPU terminology and behavior
- Keep native ownership and destruction rules explicit
- Expose a thin managed layer instead of a second object model
- Cover the full GPU surface so platform-specific use cases remain possible
- Leave extension selection, feature negotiation, and environment setup to the application

That last point is important: this library exposes GPU, but it does not decide which extensions your application should enable. That responsibility belongs to the developer building the app for a specific machine, OS, driver, and device.

## Who This Is For

`GPU` is a good fit if you want:

- a native GPU seam for a .NET application
- a C ABI that is easy to bind
- a managed API that stays close to GPU concepts
- explicit control over GPU setup rather than a high-level abstraction

## Project Layout

- Public native API: [include/gpu/gpu.h](include/gpu/gpu.h)
- Generated GPU ABI surface: [include/gpu/gpu_vulkan.h](include/gpu/gpu_vulkan.h)
- Native implementation: [src](src)
- Managed wrapper: [Managed](Managed)
- Validation notes: [VALIDATION.md](VALIDATION.md)

## Building

You can build the project with any of the helper scripts in the repo root.

### Bash

```bash
./build.sh
./build.sh Debug
```

### Command Prompt

```bat
build.bat
build.bat Debug
```

### PowerShell

```powershell
.\build.ps1
.\build.ps1 Debug
```

All three support the same configurations:

- `Debug`
- `Release`
- `RelWithDebInfo`
- `MinSizeRel`

If you want to run CMake directly:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Native Usage Example (GPU Wrapper)

**Threading Model**
- `GpuInstance` creation and its associated physical‑device (adapter) enumeration must be performed on the main thread. This mirrors the GPU API’s recommendation that instance/device creation happen before any multithreaded work and simplifies driver initialization.
- After the instance, physical device, and logical device are created, all other wrapper calls (queue retrieval, command submission, etc.) are thread‑safe. Operations are serviced on a first‑come‑first‑served basis unless you explicitly synchronize with Vulkan semaphores or fences.
- The library’s reference counting is atomic, so `retain`/`drop` can be called from any thread.
- If you need stricter ordering, use your own synchronization primitives around queue submissions.



The native GPU API keeps GPU setup explicit.

// NOTE: The GPU wrapper only defines handle types (GPUInstance, GPUDevice, etc.).
// Creation‑info data is still provided via the original Vulkan structs (GpuApplicationInfo,
// GpuInstanceCreateInfo, GpuDeviceCreateInfo, …) which the wrapper forwards to the loader.
// No separate "GPU structs" exist in this library.

// Note: This example uses GPU structs because the GPU wrapper forwards them to the GPU loader.

```cpp
#include <gpu/gpu.h>
#include <gpu/gpu_structs.h>
#include <stdio.h>

int main() {
    // 1. Query the Vulkan API version that the wrapper targets.
    uint32_t apiVersion = gpuGetApiVersion();
    printf("GPU wrapper targets Vulkan API version %u\n", apiVersion);

    // 2. Retrieve required instance extensions (still GPU structs).
    const char** extensions = nullptr;
    uint32_t extensionCount = 0;
    if (!gpuGetRequiredInstanceExtensions(&extensions, &extensionCount)) {
        fprintf(stderr, "Failed to get required instance extensions\n");
        return 1;
    }
    printf("Required instance extensions (%u):\n", extensionCount);
    for (uint32_t i = 0; i < extensionCount; ++i) {
        printf("  %s\n", extensions[i]);
    }

    // 3. Create a Vulkan instance (still using GpuInstanceCreateInfo).
    GpuApplicationInfo appInfo = {};
    appInfo.sType = GPU_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "GPU Sample";
    appInfo.apiVersion = apiVersion;

    GpuInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType = GPU_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledExtensionCount = extensionCount;
    instanceInfo.ppEnabledExtensionNames = extensions;

    GPUInstance instance = nullptr;
    if (gpuInstanceCreate(&instanceInfo, nullptr, &instance) != GPU_SUCCESS) {
        fprintf(stderr, "Failed to create GPU instance\n");
        return 1;
    }
    printf("GPU instance created successfully.\n");

    // 4. Enumerate physical devices.
    uint32_t physCount = gpuInstanceGetPhysicalDeviceCount(instance);
    printf("Physical devices found: %u\n", physCount);
    if (physCount == 0) {
        gpuInstanceDestroy(instance);
        return 1;
    }
    GPUPhysicalDevice phys = nullptr;
    if (gpuInstanceGetPhysicalDevice(instance, 0, &phys) != GPU_SUCCESS) {
        fprintf(stderr, "Failed to get physical device\n");
        gpuInstanceDestroy(instance);
        return 1;
    }

    // 5. Create a device (still using GpuDeviceCreateInfo).
    float queuePriority = 1.0f;
    GpuDeviceQueueCreateInfo queueInfo = {};
    queueInfo.sType = GPU_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = 0; // assume first queue family supports graphics
    queueInfo.queueCount = 1;
    queueInfo.pQueuePriorities = &queuePriority;

    GpuDeviceCreateInfo deviceInfo = {};
    deviceInfo.sType = GPU_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.queueCreateInfoCount = 1;
    deviceInfo.pQueueCreateInfos = &queueInfo;

    GPUDevice device = nullptr;
    if (gpuDeviceCreate(phys, &deviceInfo, nullptr, &device) != GPU_SUCCESS) {
        fprintf(stderr, "Failed to create device\n");
        gpuPhysicalDeviceRelease(phys);
        gpuInstanceDestroy(instance);
        return 1;
    }
    printf("GPU device created successfully.\n");

    // 6. Get a queue.
    GPUQueue queue = nullptr;
    gpuDeviceGetQueue(device, 0, 0, &queue);
    if (!queue) {
        fprintf(stderr, "Failed to get queue\n");
    } else {
        printf("GPU queue obtained successfully.\n");

// The queue is now ready for command submission.
// Typical next steps:
//
// 1. Create a command pool (one per thread or per queue family):
//    GPUCommandPool cmdPool;
//    gpuCommandPoolCreate(device, 0, &cmdPool);
//
// 2. Allocate a command buffer from the pool:
//    GPUCommandBuffer cmd;
//    gpuCommandBufferAllocate(cmdPool, &cmd);
//
// 3. Record commands (begin, bind pipeline, draw, end, etc.):
//    gpuCmdBegin(cmd, ...);
//    gpuCmdBindPipeline(cmd, pipeline);
//    gpuCmdDraw(cmd, ...);
//    gpuCmdEnd(cmd);
//
// 4. Submit the command buffer to the queue (no explicit fence):
//    gpuQueueSubmit(queue, 1, &cmd, nullptr, nullptr);
//    // Wait for completion (queue‑idle):
//    gpuQueueWaitIdle(queue);
//
// // Alternative: use a fence and the GPU‑friendly wrapper:
// GPUFence fence = nullptr;
// gpuQueueSubmit(queue, 1, &cmd, nullptr, &fence);
// gpuDeviceWaitForFences(device, 1, &fence, GPU_TRUE, UINT64_MAX);
// gpuFenceDestroy(fence);


// 5. Clean‑up the command pool when done:
//    gpuCommandPoolDestroy(cmdPool);



    // Cleanup.
    gpuQueueRelease(queue);
    gpuDeviceDestroy(device);
    gpuPhysicalDeviceRelease(phys);
    gpuInstanceDestroy(instance);
    return 0;
}
```

## Managed Usage Example

The managed layer follows the same object graph, but exposes disposable wrappers for C#.

```csharp
using System;
using GPU;

class Program
{
    static void Main()
    {
        // Query the Vulkan version the wrapper targets
        uint apiVersion = Library.GetApiVersion();
        Console.WriteLine($"Vulkan API version: {apiVersion}");

        // Required instance extensions
        string[] extensions = Library.GetRequiredInstanceExtensions();
        Console.WriteLine("Instance extensions:");
        foreach (var ext in extensions) Console.WriteLine($"  {ext}");

        // Create the instance (struct layout mirrors native GPU structs)
        var appInfo = new GpuApplicationInfo
        {
            sType = GPU_STRUCTURE_TYPE_APPLICATION_INFO,
            pApplicationName = "ManagedDemo",
            apiVersion = apiVersion
        };
        var instInfo = new GpuInstanceCreateInfo
        {
            sType = GPU_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            pApplicationInfo = &appInfo,
            enabledExtensionCount = (uint)extensions.Length,
            ppEnabledExtensionNames = extensions
        };
        using var instance = Library.CreateInstance(ref instInfo);

        // Enumerate physical devices
        uint physCount = Library.InstanceGetPhysicalDeviceCount(instance.Handle);
        Console.WriteLine($"Physical devices: {physCount}");

        // Pick first device and create a logical device
        Library.InstanceGetPhysicalDevice(instance.Handle, 0, out var phys);
        var queueInfo = new GpuDeviceQueueCreateInfo
        {
            sType = GPU_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            queueFamilyIndex = 0,
            queueCount = 1,
            pQueuePriorities = stackalloc float[1] { 1.0f }
        };
        var devInfo = new GpuDeviceCreateInfo
        {
            sType = GPU_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            queueCreateInfoCount = 1,
            pQueueCreateInfos = &queueInfo
        };
        using var device = Library.CreateDevice(phys, ref devInfo);

        // Retrieve a queue
        Library.DeviceGetQueue(device.Handle, 0, 0, out var queue);
        Console.WriteLine($"Got queue: 0x{queue.ToString("X")}");
    }
}
```

### Managed API Overview

- The .NET wrapper lives in the **Managed** project and is built as a class library (`GPU.Managed.csproj`).
- All native handles are exposed as `IntPtr`/`UIntPtr` (e.g. `IntPtr Instance`, `IntPtr Device`).
- Lifetime is explicit: each wrapper class implements `IDisposable` and calls the corresponding `gpu*Drop`/`gpu*Destroy` in `Dispose`.
- Reference counting is performed by the native side, so you can safely share handles across threads; retain when storing a handle and drop when finished.
- Helper static methods (`Library.GetApiVersion`, `Library.GetRequiredInstanceExtensions`, etc.) wrap the most common native calls.

#### Minimal C# program

```csharp
using System;
using GPU;

class Program
{
    static void Main()
    {
        // Query the Vulkan version the wrapper targets
        uint apiVersion = Library.GetApiVersion();
        Console.WriteLine($"Vulkan API version: {apiVersion}");

        // Required instance extensions
        string[] extensions = Library.GetRequiredInstanceExtensions();
        Console.WriteLine("Instance extensions:");
        foreach (var ext in extensions) Console.WriteLine($"  {ext}");

        // Create the instance (struct layout mirrors native GPU structs)
        var appInfo = new GpuApplicationInfo
        {
            sType = GPU_STRUCTURE_TYPE_APPLICATION_INFO,
            pApplicationName = "ManagedDemo",
            apiVersion = apiVersion
        };
        var instInfo = new GpuInstanceCreateInfo
        {
            sType = GPU_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            pApplicationInfo = &appInfo,
            enabledExtensionCount = (uint)extensions.Length,
            ppEnabledExtensionNames = extensions
        };
        using var instance = Library.CreateInstance(ref instInfo);

        // Enumerate physical devices
        uint physCount = Library.InstanceGetPhysicalDeviceCount(instance.Handle);
        Console.WriteLine($"Physical devices: {physCount}");

        // Pick first device and create a logical device
        Library.InstanceGetPhysicalDevice(instance.Handle, 0, out var phys);
        var queueInfo = new GpuDeviceQueueCreateInfo
        {
            sType = GPU_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            queueFamilyIndex = 0,
            queueCount = 1,
            pQueuePriorities = stackalloc float[1] { 1.0f }
        };
        var devInfo = new GpuDeviceCreateInfo
        {
            sType = GPU_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            queueCreateInfoCount = 1,
            pQueueCreateInfos = &queueInfo
        };
        using var device = Library.CreateDevice(phys, ref devInfo);

        // Retrieve a queue
        Library.DeviceGetQueue(device.Handle, 0, 0, out var queue);
        Console.WriteLine($"Got queue: 0x{queue.ToString("X")}");
    }
}
```

*Note*: The marshaling helpers in `Managed/GpuMarshal.cs` handle conversion of unmanaged string arrays and pointer fields required by the native structs.

If you need to build UTF-8 strings or unmanaged arrays for GPU structs, see [Managed/GpuMarshal.cs](Managed/GpuMarshal.cs).

## Runtime Expectations

- The library exposes GPU functionality, including extension-heavy paths.
- Your application is responsible for enabling the correct instance and device extensions.
- Your application is also responsible for choosing the right platform-specific GPU features for the target environment.
- If code calls a GPU command that is not actually available through the loader, the library now fails loudly instead of silently continuing.

That behavior is intentional. This library helps with interop and lifetime management, but it does not try to guess the correct GPU configuration for the end user.

## Status

The native wrapper layer, generated GPU ABI layer, and managed wrapper all build successfully in this repo.

For managed-layer notes, see [Managed/README.md](Managed/README.md).

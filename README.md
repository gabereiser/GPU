# GPU

`GPU` is a native Vulkan wrapper library with a matching .NET layer.

The goal is simple: keep the API close to Vulkan, keep ownership rules explicit, and make the library usable from C# without inventing a new rendering model.

## What This Repo Contains

- A native C ABI for Vulkan-oriented work
- A broad object wrapper layer for Vulkan handles and lifetimes
- A generated Vulkan command surface in [gpu_vulkan.h](include/gpu/gpu_vulkan.h)
- A managed .NET wrapper in [Managed/GPU.Managed.csproj](Managed/GPU.Managed.csproj)

This project is not a renderer, engine, or scene framework. It is a low-level foundation for people who want a stable native boundary and a usable managed interop layer.

## Design Goals

- Stay close to Vulkan terminology and behavior
- Keep native ownership and destruction rules explicit
- Expose a thin managed layer instead of a second object model
- Cover the full Vulkan surface so platform-specific use cases remain possible
- Leave extension selection, feature negotiation, and environment setup to the application

That last point is important: this library exposes Vulkan, but it does not decide which extensions your application should enable. That responsibility belongs to the developer building the app for a specific machine, OS, driver, and device.

## Who This Is For

`GPU` is a good fit if you want:

- a native Vulkan seam for a .NET application
- a C ABI that is easy to bind
- a managed API that stays close to Vulkan concepts
- explicit control over GPU setup rather than a high-level abstraction

## Project Layout

- Public native API: [include/gpu/gpu.h](include/gpu/gpu.h)
- Generated Vulkan ABI surface: [include/gpu/gpu_vulkan.h](include/gpu/gpu_vulkan.h)
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

## Native Usage Example

The native API keeps Vulkan setup explicit.

```cpp
#include <gpu/gpu.h>
#include <vulkan/vulkan.h>

int main() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "GPU Sample";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "None";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = gpuGetApiVersion();

    const char** extensions = nullptr;
    uint32_t extensionCount = 0;
    if (!gpuGetRequiredInstanceExtensions(&extensions, &extensionCount)) {
        return 1;
    }

    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledExtensionCount = extensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = extensions;

    GPUInstance instance = nullptr;
    if (gpuInstanceCreate(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
        return 1;
    }

    const uint32_t physicalDeviceCount = gpuInstanceGetPhysicalDeviceCount(instance);
    if (physicalDeviceCount == 0) {
        gpuInstanceDestroy(instance);
        return 1;
    }

    GPUPhysicalDevice physicalDevice = nullptr;
    if (gpuInstanceGetPhysicalDevice(instance, 0, &physicalDevice) != VK_SUCCESS) {
        gpuInstanceDestroy(instance);
        return 1;
    }

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = 0;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;

    GPUDevice device = nullptr;
    if (gpuDeviceCreate(physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
        gpuPhysicalDeviceRelease(physicalDevice);
        gpuInstanceDestroy(instance);
        return 1;
    }

    GPUQueue queue = nullptr;
    gpuDeviceGetQueue(device, 0, 0, &queue);

    gpuQueueRelease(queue);
    gpuDeviceDestroy(device);
    gpuPhysicalDeviceRelease(physicalDevice);
    gpuInstanceDestroy(instance);
    return 0;
}
```

## Managed Usage Example

The managed layer follows the same object graph, but exposes disposable wrappers for C#.

```csharp
using GPU;

public static class Sample
{
    public static void Run(VkInstanceCreateInfo instanceCreateInfo, VkDeviceCreateInfo deviceCreateInfo)
    {
        using Instance instance = Library.CreateInstance(instanceCreateInfo);
        using PhysicalDevice physicalDevice = instance.GetPhysicalDevice(0);
        using Device device = physicalDevice.CreateDevice(deviceCreateInfo);
        using Queue queue = device.GetQueue(0, 0);

        _ = instance.VkHandle;
        _ = physicalDevice.VkHandle;
        _ = device.VkHandle;
        _ = queue.VkHandle;
    }
}
```

If you need to build UTF-8 strings or unmanaged arrays for Vulkan structs, see [Managed/GpuMarshal.cs](Managed/GpuMarshal.cs).

## Runtime Expectations

- The library exposes Vulkan functionality, including extension-heavy paths.
- Your application is responsible for enabling the correct instance and device extensions.
- Your application is also responsible for choosing the right platform-specific Vulkan features for the target environment.
- If code calls a Vulkan command that is not actually available through the loader, the library now fails loudly instead of silently continuing.

That behavior is intentional. This library helps with interop and lifetime management, but it does not try to guess the correct Vulkan configuration for the end user.

## Status

The native wrapper layer, generated Vulkan ABI layer, and managed wrapper all build successfully in this repo.

For managed-layer notes, see [Managed/README.md](Managed/README.md).

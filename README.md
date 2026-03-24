# GPU

`GPU` is a Vulkan-shaped native GPU ABI with a safe-shaped managed wrapper layer.

It exists to solve one specific problem cleanly:

- native code owns the low-level GPU boundary
- managed code gets a predictable, high-performance interop surface
- both sides stay close to Vulkan instead of inventing a new rendering model

## What It Is

`GPU` is not a renderer, scene graph, or engine framework.

It is:

- a C ABI for Vulkan-oriented GPU work
- a broad object/lifecycle surface that mirrors Vulkan handles and ownership patterns
- a small amount of GLFW/Vulkan bootstrap glue where that reduces interop friction
- a managed `GPU` wrapper for .NET that keeps the public surface usable from safe C#

The design target is simple:

- object and handle families are exposed as `GPUFoo` natively and `GPU.Foo` in managed code
- Vulkan structs, enums, flags, and result codes stay Vulkan-shaped where the ABI still passes Vulkan data directly

## What It Does

The native layer provides:

- instances
- physical devices
- devices and queues
- surfaces and swapchains
- memory, buffers, images, and image views
- command pools and command buffers
- synchronization objects
- pipelines, shader modules, render passes, framebuffers, and descriptors
- extension and specialized object families carried across the same ABI surface
- the generated raw Vulkan command ABI in [gpu_vulkan.h](/C:/Users/gabe/projects/GPU/include/gpu/gpu_vulkan.h)

The managed layer provides:

- process-wide native library loading
- cached unmanaged function pointers
- disposable proxy objects over native opaque handles
- safe-shaped public entrypoints for consumers
- a managed API that stays close to the native ABI instead of hiding it

## Why It Exists

Large managed systems still need a disciplined native GPU seam.

This repo exists so that:

- engine code can stay in C#
- the Vulkan boundary can still be owned explicitly
- the interop contract can stay stable and low-level
- developers can reason about the GPU side using familiar Vulkan concepts
- the same seam can be useful for games, scientific tools, government systems, education, and other high-performance .NET workloads

The core idea is not "replace Vulkan."

The core idea is:

give Vulkan a clean native home, then let managed code meet it through a thin, trustworthy boundary.

## Design Principles

- `GPU` should feel like Vulkan with the object-facing `Vk` prefix removed.
- The native layer should be thin, systematic, and unsurprising.
- The managed layer should be a proxy layer, not a competing object model.
- Object names and file layout should stay validation-friendly and easy to audit.
- Platform details belong to the consumer and the target build, not to the core ABI shape.

## Layering

- Native `GPU` library:
  broad Vulkan-facing C ABI plus a small set of bootstrap fixtures
- Managed `GPU` wrapper:
  delegate loading, safe public entrypoints, and disposable proxy objects for .NET

## Example: C++

This is the native style: explicit create info, explicit lifetime, explicit object graph.

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

## Example: C#

This is the managed style: same object graph, same Vulkan-shaped structs, but a safe public GPU API.

Assumption:
your application provides Vulkan struct definitions from your own bindings or generated interop types.

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

If you need to prepare UTF-8 strings or unmanaged arrays for Vulkan structures, the managed layer also includes helpers in [GpuMarshal.cs](/C:/Users/gabe/projects/GPU/Managed/GpuMarshal.cs).

Notes:

- the managed public API is safe-shaped, but Vulkan struct construction is still explicit by design
- the managed layer keeps low-level interop details inside the library
- object disposal is deterministic through `IDisposable`

## Who This Is For

This project is a good fit when you want:

- a native GPU seam for a managed engine
- Vulkan-shaped behavior without a giant abstraction layer
- a C ABI that is easy to bind from C#
- a foundation layer other systems can build on

## Repo Highlights

- Native ABI header: [gpu.h](/C:/Users/gabe/projects/GPU/include/gpu/gpu.h)
- Generated raw Vulkan ABI layer: [gpu_vulkan.h](/C:/Users/gabe/projects/GPU/include/gpu/gpu_vulkan.h)
- Managed wrapper project: [GPU.Managed.csproj](/C:/Users/gabe/projects/GPU/Managed/GPU.Managed.csproj)
- Validation contract: [VALIDATION.md](/C:/Users/gabe/projects/GPU/VALIDATION.md)

## Status

The object/lifecycle wrapper surface is aligned with the validation contract in [VALIDATION.md](/C:/Users/gabe/projects/GPU/VALIDATION.md), and the managed wrapper builds successfully as [GPU.Managed.dll](/C:/Users/gabe/projects/GPU/Managed/bin/Debug/net8.0/GPU.Managed.dll).

This is foundational infrastructure:

plain ABI, Vulkan shape, managed reach.

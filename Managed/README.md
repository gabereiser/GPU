# GPU.Managed

`GPU.Managed` is the C# proxy layer for the native `GPU` library.

Current goals:

- load the native library once per process
- cache unmanaged function pointers
- expose thin disposable wrappers over the native opaque handles
- stay close to the native ABI and Vulkan object model
- provide safe-shaped managed entrypoints over the native ABI
- keep the public API usable from safe C#

Current scope:

- all native lifecycle objects declared in `include/gpu/gpu.h`
- typed `in T` creation overloads for the managed lifecycle wrappers where the native ABI accepts create-info structs
- small marshalling helpers for UTF-8 strings and unmanaged arrays in `GpuMarshal.cs`

Current status:

- the lifecycle/object proxy layer is present and builds
- the full generated managed Vulkan command/type surface is not checked into the repo yet

The managed layer keeps the low-level interop core internal and unsafe, while exposing a safe-shaped public API for consumers. Pointer-valued Vulkan parameters are still represented explicitly where Vulkan itself requires pointer semantics.

# GPU.Managed

`GPU.Managed` is the C# proxy layer for the native `GPU` library, which forwards Vulkan structs to the Vulkan loader. The managed API therefore works with the same Vulkan structures while providing a safe, disposable wrapper.

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

---

### Shader compilation

The library ships with `gpuCompileShader` and `gpuFreeShaderBinary`, enabling runtime compilation of GLSL/HLSL source to SPIR‑V.

```csharp
using GPU;

// Compile a fragment shader
var (spirv, ok) = ShaderCompiler.CompileShader(
    GPUShaderLanguage.GLSL,
    ShaderStageFlagBits.VK_SHADER_STAGE_FRAGMENT_BIT,
    @"
    #version 460
    layout(location = 0) out vec4 outColor;
    void main() { outColor = vec4(1,0,0,1); }
    "
);

if (ok)
{
    var module = ShaderModule.Create(deviceHandle, spirv);
    // use `module` when building pipelines
}
```

The helper takes a C# `string`, converts it to UTF‑8, copies the native SPIR‑V buffer into a managed `byte[]`, and frees the native allocation automatically.

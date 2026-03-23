# GPU

`GPU` is a native library whose only concern is exposing Vulkan-shaped fixtures for C#.

The goal is not to build a renderer, engine, or framework. The goal is to provide a thin, familiar, C ABI over Vulkan so a managed wrapper can call into it cleanly through native function delegates.

## Project Goals

- Mirror Vulkan's mental model as closely as possible.
- Preserve familiar concepts such as instances, physical devices, devices, queues, command pools, command buffers, swapchains, semaphores, fences, pipelines, and descriptor sets.
- Keep the API surface low-level and predictable so Vulkan developers can look at `GPU` and immediately recognize the shape.
- Provide a stable C ABI intended for C# interop.
- Let the C# layer own the higher-level ergonomics while the native layer stays disciplined and close to Vulkan.

## Design Direction

- `GPU` should feel like Vulkan with the `Vk` prefix removed.
- The native layer should be thin and systematic, not an abstraction-heavy wrapper.
- Exported functions should be named and organized consistently.
- Data types and object lifecycles should remain close to Vulkan wherever practical.
- GLFW may be used where platform integration is needed, but Vulkan is the center of gravity.

## Non-Goals

- No game engine architecture.
- No scene graph or rendering framework.
- No unrelated subsystems in the native boundary.
- No convenience layer that hides Vulkan's object model.
- No expansion into audio or other non-Vulkan domains.

## Intended Layering

- Native `GPU` library: Vulkan-focused C ABI and platform fixtures.
- Managed C# wrapper: delegate loading, idiomatic bindings, and managed ergonomics.

## Guiding Principle

If someone familiar with Vulkan reads this project, the best reaction should be:

`"Hey, that looks familiar."`

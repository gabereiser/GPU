using System.Collections.Generic;

namespace GPU;

public sealed class CommandPool : IDisposable
{
    private readonly object _childrenGate = new();
    private readonly List<WeakReference<CommandBuffer>> _commandBuffers = [];
    private CommandPoolHandle _handle;

    internal CommandPool(CommandPoolHandle handle) => _handle = handle;

    internal CommandPoolHandle Handle => _handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuCommandPoolGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuCommandPoolGetDevice(_handle.Value));
            }
        }
    }

    public CommandBuffer CreateCommandBuffer(CommandBufferLevel level)
    {
        ThrowIfDisposed();
        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuCommandBufferCreate(_handle.Value, (int)level, &handle);
            Library.ThrowIfFailed(result, "Failed to create command buffer.");
            CommandBuffer commandBuffer = new(new CommandBufferHandle(handle));
            Track(commandBuffer);
            return commandBuffer;
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        InvalidateChildren();

        unsafe {
            Library.Api.gpuCommandPoolDestroy(_handle.Value);
        }
        _handle = new CommandPoolHandle(nint.Zero);
    }

    private void Track(CommandBuffer commandBuffer)
    {
        lock (_childrenGate) {
            _commandBuffers.Add(new WeakReference<CommandBuffer>(commandBuffer));
        }
    }

    private void InvalidateChildren()
    {
        lock (_childrenGate) {
            foreach (WeakReference<CommandBuffer> weakReference in _commandBuffers) {
                if (weakReference.TryGetTarget(out CommandBuffer? commandBuffer)) {
                    commandBuffer.InvalidateFromPool();
                }
            }
            _commandBuffers.Clear();
        }
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


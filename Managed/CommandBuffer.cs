namespace GPU;

public sealed class CommandBuffer : IDisposable
{
    private bool _invalidatedByPool;
    private CommandBufferHandle _handle;

    internal CommandBuffer(CommandBufferHandle handle) => _handle = handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuCommandBufferGetVkHandle(_handle.Value);
            }
        }
    }

    public CommandPoolHandle CommandPoolHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new CommandPoolHandle(Library.Api.gpuCommandBufferGetCommandPool(_handle.Value));
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        if (!_invalidatedByPool) {
            unsafe {
                Library.Api.gpuCommandBufferDestroy(_handle.Value);
            }
        }

        _handle = new CommandBufferHandle(nint.Zero);
    }

    internal void InvalidateFromPool()
    {
        _invalidatedByPool = true;
        _handle = new CommandBufferHandle(nint.Zero);
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


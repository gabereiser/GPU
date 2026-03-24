using System.Collections.Generic;

namespace GPU;

public sealed class DescriptorPool : IDisposable
{
    private readonly object _childrenGate = new();
    private readonly List<WeakReference<DescriptorSet>> _descriptorSets = [];
    private DescriptorPoolHandle _handle;

    internal DescriptorPool(DescriptorPoolHandle handle) => _handle = handle;

    internal DescriptorPoolHandle Handle => _handle;

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDescriptorPoolGetVkHandle(_handle.Value);
            }
        }
    }

    public DeviceHandle DeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new DeviceHandle(Library.Api.gpuDescriptorPoolGetDevice(_handle.Value));
            }
        }
    }

    internal DescriptorSet AllocateDescriptorSet(nint allocateInfo)
    {
        ThrowIfDisposed();
        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuDescriptorSetAllocate(_handle.Value, (void*)allocateInfo, &handle);
            Library.ThrowIfFailed(result, "Failed to allocate descriptor set.");
            DescriptorSet descriptorSet = new(new DescriptorSetHandle(handle));
            Track(descriptorSet);
            return descriptorSet;
        }
    }

    public DescriptorSet AllocateDescriptorSet<TAllocateInfo>(in TAllocateInfo allocateInfo)
        where TAllocateInfo : unmanaged
    {
        unsafe {
            fixed (TAllocateInfo* allocateInfoPtr = &allocateInfo) {
                return AllocateDescriptorSet((nint)allocateInfoPtr);
            }
        }
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        InvalidateChildren();

        unsafe {
            Library.Api.gpuDescriptorPoolDestroy(_handle.Value);
        }
        _handle = new DescriptorPoolHandle(nint.Zero);
    }

    private void Track(DescriptorSet descriptorSet)
    {
        lock (_childrenGate) {
            _descriptorSets.Add(new WeakReference<DescriptorSet>(descriptorSet));
        }
    }

    private void InvalidateChildren()
    {
        lock (_childrenGate) {
            foreach (WeakReference<DescriptorSet> weakReference in _descriptorSets) {
                if (weakReference.TryGetTarget(out DescriptorSet? descriptorSet)) {
                    descriptorSet.InvalidateFromPool();
                }
            }
            _descriptorSets.Clear();
        }
    }

    private void ThrowIfDisposed() => ObjectDisposedException.ThrowIf(_handle.IsNull, this);
}


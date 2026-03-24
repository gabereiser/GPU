namespace GPU;

public sealed class Device : IDisposable
{
    private DeviceHandle _handle;

    internal Device(DeviceHandle handle)
    {
        _handle = handle;
    }

    public bool IsDisposed => _handle.IsNull;

    public nuint VkHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return Library.Api.gpuDeviceGetVkHandle(_handle.Value);
            }
        }
    }

    public PhysicalDeviceHandle PhysicalDeviceHandle
    {
        get
        {
            ThrowIfDisposed();
            unsafe {
                return new PhysicalDeviceHandle(Library.Api.gpuDeviceGetPhysicalDevice(_handle.Value));
            }
        }
    }

    public Queue GetQueue(uint familyIndex, uint queueIndex)
    {
        ThrowIfDisposed();

        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuDeviceGetQueue(_handle.Value, familyIndex, queueIndex, &handle);
            Library.ThrowIfFailed(result, "Failed to get queue.");
            return new Queue(new QueueHandle(handle));
        }
    }

    internal Swapchain CreateSwapchain(Surface surface, nint createInfo, nint allocator = 0)
    {
        ThrowIfDisposed();
        ArgumentNullException.ThrowIfNull(surface);
        surface.ThrowIfDisposedForInterop();

        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuSwapchainCreate(
                _handle.Value,
                surface.Handle.Value,
                (void*)createInfo,
                (void*)allocator,
                &handle);
            Library.ThrowIfFailed(result, "Failed to create swapchain.");
            return new Swapchain(new SwapchainHandle(handle));
        }
    }

    public Swapchain CreateSwapchain<TCreateInfo>(Surface surface, in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateSwapchain(surface, (nint)createInfoPtr, allocator);
            }
        }
    }

    public Swapchain CreateSwapchain<TCreateInfo, TAllocator>(Surface surface, in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateSwapchain(surface, (nint)createInfoPtr, (nint)allocatorPtr);
            }
        }
    }

    public SwapchainKHR CreateSwapchainKHR<TCreateInfo>(Surface surface, in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateSwapchainKHR(surface, (nint)createInfoPtr, allocator);
            }
        }
    }

    public SwapchainKHR CreateSwapchainKHR<TCreateInfo, TAllocator>(Surface surface, in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateSwapchainKHR(surface, (nint)createInfoPtr, (nint)allocatorPtr);
            }
        }
    }

    internal SwapchainKHR CreateSwapchainKHR(Surface surface, nint createInfo, nint allocator = 0)
    {
        ThrowIfDisposed();
        ArgumentNullException.ThrowIfNull(surface);
        surface.ThrowIfDisposedForInterop();

        unsafe {
            nint handle = nint.Zero;
            Result result = Library.Api.gpuSwapchainCreate(
                _handle.Value,
                surface.Handle.Value,
                (void*)createInfo,
                (void*)allocator,
                &handle);
            Library.ThrowIfFailed(result, "Failed to create swapchain KHR.");
            return new SwapchainKHR(new SwapchainHandle(handle));
        }
    }

    internal ShaderModule CreateShaderModule(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuShaderModuleCreate, handle => new ShaderModule(new ShaderModuleHandle(handle)), "Failed to create shader module.");
        }
    }

    public ShaderModule CreateShaderModule<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuShaderModuleCreate, handle => new ShaderModule(new ShaderModuleHandle(handle)), "Failed to create shader module.");
        }
    }

    public ShaderModule CreateShaderModule<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuShaderModuleCreate, handle => new ShaderModule(new ShaderModuleHandle(handle)), "Failed to create shader module.");
        }
    }

    internal PipelineLayout CreatePipelineLayout(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuPipelineLayoutCreate, handle => new PipelineLayout(new PipelineLayoutHandle(handle)), "Failed to create pipeline layout.");
        }
    }

    public PipelineLayout CreatePipelineLayout<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuPipelineLayoutCreate, handle => new PipelineLayout(new PipelineLayoutHandle(handle)), "Failed to create pipeline layout.");
        }
    }

    public PipelineLayout CreatePipelineLayout<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuPipelineLayoutCreate, handle => new PipelineLayout(new PipelineLayoutHandle(handle)), "Failed to create pipeline layout.");
        }
    }

    internal Sampler CreateSampler(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuSamplerCreate, handle => new Sampler(new SamplerHandle(handle)), "Failed to create sampler.");
        }
    }

    public Sampler CreateSampler<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuSamplerCreate, handle => new Sampler(new SamplerHandle(handle)), "Failed to create sampler.");
        }
    }

    public Sampler CreateSampler<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuSamplerCreate, handle => new Sampler(new SamplerHandle(handle)), "Failed to create sampler.");
        }
    }

    internal DescriptorSetLayout CreateDescriptorSetLayout(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuDescriptorSetLayoutCreate, handle => new DescriptorSetLayout(new DescriptorSetLayoutHandle(handle)), "Failed to create descriptor set layout.");
        }
    }

    public DescriptorSetLayout CreateDescriptorSetLayout<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuDescriptorSetLayoutCreate, handle => new DescriptorSetLayout(new DescriptorSetLayoutHandle(handle)), "Failed to create descriptor set layout.");
        }
    }

    public DescriptorSetLayout CreateDescriptorSetLayout<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuDescriptorSetLayoutCreate, handle => new DescriptorSetLayout(new DescriptorSetLayoutHandle(handle)), "Failed to create descriptor set layout.");
        }
    }

    internal DescriptorPool CreateDescriptorPool(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuDescriptorPoolCreate, handle => new DescriptorPool(new DescriptorPoolHandle(handle)), "Failed to create descriptor pool.");
        }
    }

    public DescriptorPool CreateDescriptorPool<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuDescriptorPoolCreate, handle => new DescriptorPool(new DescriptorPoolHandle(handle)), "Failed to create descriptor pool.");
        }
    }

    public DescriptorPool CreateDescriptorPool<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuDescriptorPoolCreate, handle => new DescriptorPool(new DescriptorPoolHandle(handle)), "Failed to create descriptor pool.");
        }
    }

    internal Framebuffer CreateFramebuffer(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuFramebufferCreate, handle => new Framebuffer(new FramebufferHandle(handle)), "Failed to create framebuffer.");
        }
    }

    public Framebuffer CreateFramebuffer<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuFramebufferCreate, handle => new Framebuffer(new FramebufferHandle(handle)), "Failed to create framebuffer.");
        }
    }

    public Framebuffer CreateFramebuffer<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuFramebufferCreate, handle => new Framebuffer(new FramebufferHandle(handle)), "Failed to create framebuffer.");
        }
    }

    internal RenderPass CreateRenderPass(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuRenderPassCreate, handle => new RenderPass(new RenderPassHandle(handle)), "Failed to create render pass.");
        }
    }

    public RenderPass CreateRenderPass<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuRenderPassCreate, handle => new RenderPass(new RenderPassHandle(handle)), "Failed to create render pass.");
        }
    }

    public RenderPass CreateRenderPass<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuRenderPassCreate, handle => new RenderPass(new RenderPassHandle(handle)), "Failed to create render pass.");
        }
    }

    internal PipelineCache CreatePipelineCache(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuPipelineCacheCreate, handle => new PipelineCache(new PipelineCacheHandle(handle)), "Failed to create pipeline cache.");
        }
    }

    public PipelineCache CreatePipelineCache<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuPipelineCacheCreate, handle => new PipelineCache(new PipelineCacheHandle(handle)), "Failed to create pipeline cache.");
        }
    }

    public PipelineCache CreatePipelineCache<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuPipelineCacheCreate, handle => new PipelineCache(new PipelineCacheHandle(handle)), "Failed to create pipeline cache.");
        }
    }

    internal Pipeline CreateGraphicsPipeline(PipelineCache? pipelineCache, nint createInfo, nint allocator = 0)
    {
        ThrowIfDisposed();

        unsafe {
            nint handle = nint.Zero;
            nint cacheHandle = pipelineCache?.Handle.Value ?? 0;
            Result result = Library.Api.gpuPipelineCreateGraphics(_handle.Value, cacheHandle, (void*)createInfo, (void*)allocator, &handle);
            Library.ThrowIfFailed(result, "Failed to create graphics pipeline.");
            return new Pipeline(new PipelineHandle(handle));
        }
    }

    public Pipeline CreateGraphicsPipeline<TCreateInfo>(PipelineCache? pipelineCache, in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateGraphicsPipeline(pipelineCache, (nint)createInfoPtr, allocator);
            }
        }
    }

    public Pipeline CreateGraphicsPipeline<TCreateInfo, TAllocator>(PipelineCache? pipelineCache, in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateGraphicsPipeline(pipelineCache, (nint)createInfoPtr, (nint)allocatorPtr);
            }
        }
    }

    internal Pipeline CreateComputePipeline(PipelineCache? pipelineCache, nint createInfo, nint allocator = 0)
    {
        ThrowIfDisposed();

        unsafe {
            nint handle = nint.Zero;
            nint cacheHandle = pipelineCache?.Handle.Value ?? 0;
            Result result = Library.Api.gpuPipelineCreateCompute(_handle.Value, cacheHandle, (void*)createInfo, (void*)allocator, &handle);
            Library.ThrowIfFailed(result, "Failed to create compute pipeline.");
            return new Pipeline(new PipelineHandle(handle));
        }
    }

    public Pipeline CreateComputePipeline<TCreateInfo>(PipelineCache? pipelineCache, in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateComputePipeline(pipelineCache, (nint)createInfoPtr, allocator);
            }
        }
    }

    public Pipeline CreateComputePipeline<TCreateInfo, TAllocator>(PipelineCache? pipelineCache, in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateComputePipeline(pipelineCache, (nint)createInfoPtr, (nint)allocatorPtr);
            }
        }
    }

    internal DescriptorUpdateTemplate CreateDescriptorUpdateTemplate(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuDescriptorUpdateTemplateCreate, handle => new DescriptorUpdateTemplate(new DescriptorUpdateTemplateHandle(handle)), "Failed to create descriptor update template.");
        }
    }

    public DescriptorUpdateTemplate CreateDescriptorUpdateTemplate<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuDescriptorUpdateTemplateCreate, handle => new DescriptorUpdateTemplate(new DescriptorUpdateTemplateHandle(handle)), "Failed to create descriptor update template.");
        }
    }

    public DescriptorUpdateTemplate CreateDescriptorUpdateTemplate<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuDescriptorUpdateTemplateCreate, handle => new DescriptorUpdateTemplate(new DescriptorUpdateTemplateHandle(handle)), "Failed to create descriptor update template.");
        }
    }

    public DescriptorUpdateTemplateKHR CreateDescriptorUpdateTemplateKHR<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuDescriptorUpdateTemplateCreate, handle => new DescriptorUpdateTemplateKHR(new DescriptorUpdateTemplateHandle(handle)), "Failed to create descriptor update template KHR.");
        }
    }

    public DescriptorUpdateTemplateKHR CreateDescriptorUpdateTemplateKHR<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuDescriptorUpdateTemplateCreate, handle => new DescriptorUpdateTemplateKHR(new DescriptorUpdateTemplateHandle(handle)), "Failed to create descriptor update template KHR.");
        }
    }

    internal SamplerYcbcrConversion CreateSamplerYcbcrConversion(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuSamplerYcbcrConversionCreate, handle => new SamplerYcbcrConversion(new SamplerYcbcrConversionHandle(handle)), "Failed to create sampler YCbCr conversion.");
        }
    }

    public SamplerYcbcrConversion CreateSamplerYcbcrConversion<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuSamplerYcbcrConversionCreate, handle => new SamplerYcbcrConversion(new SamplerYcbcrConversionHandle(handle)), "Failed to create sampler YCbCr conversion.");
        }
    }

    public SamplerYcbcrConversion CreateSamplerYcbcrConversion<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuSamplerYcbcrConversionCreate, handle => new SamplerYcbcrConversion(new SamplerYcbcrConversionHandle(handle)), "Failed to create sampler YCbCr conversion.");
        }
    }

    public SamplerYcbcrConversionKHR CreateSamplerYcbcrConversionKHR<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuSamplerYcbcrConversionCreate, handle => new SamplerYcbcrConversionKHR(new SamplerYcbcrConversionHandle(handle)), "Failed to create sampler YCbCr conversion KHR.");
        }
    }

    public SamplerYcbcrConversionKHR CreateSamplerYcbcrConversionKHR<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuSamplerYcbcrConversionCreate, handle => new SamplerYcbcrConversionKHR(new SamplerYcbcrConversionHandle(handle)), "Failed to create sampler YCbCr conversion KHR.");
        }
    }

    internal PrivateDataSlot CreatePrivateDataSlot(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuPrivateDataSlotCreate, handle => new PrivateDataSlot(new PrivateDataSlotHandle(handle)), "Failed to create private data slot.");
        }
    }

    public PrivateDataSlot CreatePrivateDataSlot<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuPrivateDataSlotCreate, handle => new PrivateDataSlot(new PrivateDataSlotHandle(handle)), "Failed to create private data slot.");
        }
    }

    public PrivateDataSlot CreatePrivateDataSlot<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuPrivateDataSlotCreate, handle => new PrivateDataSlot(new PrivateDataSlotHandle(handle)), "Failed to create private data slot.");
        }
    }

    public PrivateDataSlotEXT CreatePrivateDataSlotEXT<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuPrivateDataSlotCreate, handle => new PrivateDataSlotEXT(new PrivateDataSlotHandle(handle)), "Failed to create private data slot EXT.");
        }
    }

    public PrivateDataSlotEXT CreatePrivateDataSlotEXT<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuPrivateDataSlotCreate, handle => new PrivateDataSlotEXT(new PrivateDataSlotHandle(handle)), "Failed to create private data slot EXT.");
        }
    }

    internal CommandPool CreateCommandPool(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuCommandPoolCreate, handle => new CommandPool(new CommandPoolHandle(handle)), "Failed to create command pool.");
        }
    }

    public CommandPool CreateCommandPool<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuCommandPoolCreate, handle => new CommandPool(new CommandPoolHandle(handle)), "Failed to create command pool.");
        }
    }

    public CommandPool CreateCommandPool<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuCommandPoolCreate, handle => new CommandPool(new CommandPoolHandle(handle)), "Failed to create command pool.");
        }
    }

    internal DeviceMemory CreateDeviceMemory(nint allocateInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(allocateInfo, allocator, Library.Api.gpuDeviceMemoryCreate, handle => new DeviceMemory(new DeviceMemoryHandle(handle)), "Failed to create device memory.");
        }
    }

    public DeviceMemory CreateDeviceMemory<TAllocateInfo>(in TAllocateInfo allocateInfo, nint allocator = 0)
        where TAllocateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in allocateInfo, allocator, Library.Api.gpuDeviceMemoryCreate, handle => new DeviceMemory(new DeviceMemoryHandle(handle)), "Failed to create device memory.");
        }
    }

    public DeviceMemory CreateDeviceMemory<TAllocateInfo, TAllocator>(in TAllocateInfo allocateInfo, in TAllocator allocator)
        where TAllocateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in allocateInfo, in allocator, Library.Api.gpuDeviceMemoryCreate, handle => new DeviceMemory(new DeviceMemoryHandle(handle)), "Failed to create device memory.");
        }
    }

    internal Buffer CreateBuffer(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuBufferCreate, handle => new Buffer(new BufferHandle(handle)), "Failed to create buffer.");
        }
    }

    public Buffer CreateBuffer<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuBufferCreate, handle => new Buffer(new BufferHandle(handle)), "Failed to create buffer.");
        }
    }

    public Buffer CreateBuffer<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuBufferCreate, handle => new Buffer(new BufferHandle(handle)), "Failed to create buffer.");
        }
    }

    internal BufferView CreateBufferView(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuBufferViewCreate, handle => new BufferView(new BufferViewHandle(handle)), "Failed to create buffer view.");
        }
    }

    public BufferView CreateBufferView<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuBufferViewCreate, handle => new BufferView(new BufferViewHandle(handle)), "Failed to create buffer view.");
        }
    }

    public BufferView CreateBufferView<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuBufferViewCreate, handle => new BufferView(new BufferViewHandle(handle)), "Failed to create buffer view.");
        }
    }

    internal Image CreateImage(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuImageCreate, handle => new Image(new ImageHandle(handle)), "Failed to create image.");
        }
    }

    public Image CreateImage<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuImageCreate, handle => new Image(new ImageHandle(handle)), "Failed to create image.");
        }
    }

    public Image CreateImage<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuImageCreate, handle => new Image(new ImageHandle(handle)), "Failed to create image.");
        }
    }

    internal ImageView CreateImageView(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateImageViewCore((void*)createInfo, (void*)allocator);
        }
    }

    public ImageView CreateImageView<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo) {
                return CreateImageViewCore(createInfoPtr, (void*)allocator);
            }
        }
    }

    public ImageView CreateImageView<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TCreateInfo* createInfoPtr = &createInfo)
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateImageViewCore(createInfoPtr, allocatorPtr);
            }
        }
    }

    internal Fence CreateFence(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuFenceCreate, handle => new Fence(new FenceHandle(handle)), "Failed to create fence.");
        }
    }

    public Fence CreateFence<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuFenceCreate, handle => new Fence(new FenceHandle(handle)), "Failed to create fence.");
        }
    }

    public Fence CreateFence<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuFenceCreate, handle => new Fence(new FenceHandle(handle)), "Failed to create fence.");
        }
    }

    internal Semaphore CreateSemaphore(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuSemaphoreCreate, handle => new Semaphore(new SemaphoreHandle(handle)), "Failed to create semaphore.");
        }
    }

    public Semaphore CreateSemaphore<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuSemaphoreCreate, handle => new Semaphore(new SemaphoreHandle(handle)), "Failed to create semaphore.");
        }
    }

    public Semaphore CreateSemaphore<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuSemaphoreCreate, handle => new Semaphore(new SemaphoreHandle(handle)), "Failed to create semaphore.");
        }
    }

    internal Event CreateEvent(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuEventCreate, handle => new Event(new EventHandle(handle)), "Failed to create event.");
        }
    }

    public Event CreateEvent<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuEventCreate, handle => new Event(new EventHandle(handle)), "Failed to create event.");
        }
    }

    public Event CreateEvent<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuEventCreate, handle => new Event(new EventHandle(handle)), "Failed to create event.");
        }
    }

    internal QueryPool CreateQueryPool(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuQueryPoolCreate, handle => new QueryPool(new QueryPoolHandle(handle)), "Failed to create query pool.");
        }
    }

    public QueryPool CreateQueryPool<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuQueryPoolCreate, handle => new QueryPool(new QueryPoolHandle(handle)), "Failed to create query pool.");
        }
    }

    public QueryPool CreateQueryPool<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuQueryPoolCreate, handle => new QueryPool(new QueryPoolHandle(handle)), "Failed to create query pool.");
        }
    }

    internal unsafe ImageView CreateImageViewCore(void* createInfo, void* allocator)
    {
        ThrowIfDisposed();

        nint handle = nint.Zero;
        Result result = Library.Api.gpuImageViewCreate(_handle.Value, createInfo, allocator, &handle);
        Library.ThrowIfFailed(result, "Failed to create image view.");
        return new ImageView(new ImageViewHandle(handle));
    }

    public void Dispose()
    {
        if (_handle.IsNull) {
            return;
        }

        unsafe {
            Library.Api.gpuDeviceDestroy(_handle.Value);
        }
        _handle = new DeviceHandle(nint.Zero);
    }

    private void ThrowIfDisposed()
    {
        ObjectDisposedException.ThrowIf(_handle.IsNull, this);
    }

    private unsafe TChild CreateDeviceChild<TChild>(
        nint createInfo,
        nint allocator,
        delegate* unmanaged<nint, void*, void*, nint*, Result> create,
        Func<nint, TChild> factory,
        string errorMessage)
    {
        ThrowIfDisposed();

        nint handle = nint.Zero;
        Result result = create(_handle.Value, (void*)createInfo, (void*)allocator, &handle);
        Library.ThrowIfFailed(result, errorMessage);
        return factory(handle);
    }

    private unsafe TChild CreateDeviceChild<TChild, TCreateInfo>(
        in TCreateInfo createInfo,
        nint allocator,
        delegate* unmanaged<nint, void*, void*, nint*, Result> create,
        Func<nint, TChild> factory,
        string errorMessage)
        where TCreateInfo : unmanaged
    {
        fixed (TCreateInfo* createInfoPtr = &createInfo) {
            return CreateDeviceChild((nint)createInfoPtr, allocator, create, factory, errorMessage);
        }
    }

    private unsafe TChild CreateDeviceChild<TChild, TCreateInfo, TAllocator>(
        in TCreateInfo createInfo,
        in TAllocator allocator,
        delegate* unmanaged<nint, void*, void*, nint*, Result> create,
        Func<nint, TChild> factory,
        string errorMessage)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        fixed (TCreateInfo* createInfoPtr = &createInfo)
        fixed (TAllocator* allocatorPtr = &allocator) {
            return CreateDeviceChild((nint)createInfoPtr, (nint)allocatorPtr, create, factory, errorMessage);
        }
    }

    internal ValidationCacheEXT CreateValidationCacheEXT(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(
                createInfo,
                allocator,
                Library.Api.gpuValidationCacheEXTCreate,
                handle => new ValidationCacheEXT(new ValidationCacheEXTHandle(handle)),
                "Failed to create validation cache.");
        }
    }

    public ValidationCacheEXT CreateValidationCacheEXT<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(
                in createInfo,
                allocator,
                Library.Api.gpuValidationCacheEXTCreate,
                handle => new ValidationCacheEXT(new ValidationCacheEXTHandle(handle)),
                "Failed to create validation cache.");
        }
    }

    public ValidationCacheEXT CreateValidationCacheEXT<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(
                in createInfo,
                in allocator,
                Library.Api.gpuValidationCacheEXTCreate,
                handle => new ValidationCacheEXT(new ValidationCacheEXTHandle(handle)),
                "Failed to create validation cache.");
        }
    }

    internal DeferredOperationKHR CreateDeferredOperationKHR(nint allocator = 0)
    {
        unsafe {
            ThrowIfDisposed();
            nint handle = nint.Zero;
            Result result = Library.Api.gpuDeferredOperationKHRCreate(_handle.Value, (void*)allocator, &handle);
            Library.ThrowIfFailed(result, "Failed to create deferred operation.");
            return new DeferredOperationKHR(new DeferredOperationKHRHandle(handle));
        }
    }

    public DeferredOperationKHR CreateDeferredOperationKHR()
    {
        return CreateDeferredOperationKHR(0);
    }

    public DeferredOperationKHR CreateDeferredOperationKHR<TAllocator>(in TAllocator allocator)
        where TAllocator : unmanaged
    {
        unsafe {
            fixed (TAllocator* allocatorPtr = &allocator) {
                return CreateDeferredOperationKHR((nint)allocatorPtr);
            }
        }
    }

    internal IndirectCommandsLayoutNV CreateIndirectCommandsLayoutNV(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuIndirectCommandsLayoutNVCreate, handle => new IndirectCommandsLayoutNV(new IndirectCommandsLayoutNVHandle(handle)), "Failed to create indirect commands layout NV.");
        }
    }

    public IndirectCommandsLayoutNV CreateIndirectCommandsLayoutNV<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuIndirectCommandsLayoutNVCreate, handle => new IndirectCommandsLayoutNV(new IndirectCommandsLayoutNVHandle(handle)), "Failed to create indirect commands layout NV.");
        }
    }

    public IndirectCommandsLayoutNV CreateIndirectCommandsLayoutNV<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuIndirectCommandsLayoutNVCreate, handle => new IndirectCommandsLayoutNV(new IndirectCommandsLayoutNVHandle(handle)), "Failed to create indirect commands layout NV.");
        }
    }

    internal IndirectCommandsLayoutEXT CreateIndirectCommandsLayoutEXT(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuIndirectCommandsLayoutEXTCreate, handle => new IndirectCommandsLayoutEXT(new IndirectCommandsLayoutEXTHandle(handle)), "Failed to create indirect commands layout EXT.");
        }
    }

    public IndirectCommandsLayoutEXT CreateIndirectCommandsLayoutEXT<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuIndirectCommandsLayoutEXTCreate, handle => new IndirectCommandsLayoutEXT(new IndirectCommandsLayoutEXTHandle(handle)), "Failed to create indirect commands layout EXT.");
        }
    }

    public IndirectCommandsLayoutEXT CreateIndirectCommandsLayoutEXT<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuIndirectCommandsLayoutEXTCreate, handle => new IndirectCommandsLayoutEXT(new IndirectCommandsLayoutEXTHandle(handle)), "Failed to create indirect commands layout EXT.");
        }
    }

    internal IndirectExecutionSetEXT CreateIndirectExecutionSetEXT(nint createInfo, nint allocator = 0)
    {
        unsafe {
            return CreateDeviceChild(createInfo, allocator, Library.Api.gpuIndirectExecutionSetEXTCreate, handle => new IndirectExecutionSetEXT(new IndirectExecutionSetEXTHandle(handle)), "Failed to create indirect execution set EXT.");
        }
    }

    public IndirectExecutionSetEXT CreateIndirectExecutionSetEXT<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuIndirectExecutionSetEXTCreate, handle => new IndirectExecutionSetEXT(new IndirectExecutionSetEXTHandle(handle)), "Failed to create indirect execution set EXT.");
        }
    }

    public IndirectExecutionSetEXT CreateIndirectExecutionSetEXT<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe {
            return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuIndirectExecutionSetEXTCreate, handle => new IndirectExecutionSetEXT(new IndirectExecutionSetEXTHandle(handle)), "Failed to create indirect execution set EXT.");
        }
    }

    internal AccelerationStructureKHR CreateAccelerationStructureKHR(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuAccelerationStructureKHRCreate, handle => new AccelerationStructureKHR(new AccelerationStructureKHRHandle(handle)), "Failed to create acceleration structure KHR."); }
    }

    public AccelerationStructureKHR CreateAccelerationStructureKHR<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuAccelerationStructureKHRCreate, handle => new AccelerationStructureKHR(new AccelerationStructureKHRHandle(handle)), "Failed to create acceleration structure KHR."); }
    }

    public AccelerationStructureKHR CreateAccelerationStructureKHR<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuAccelerationStructureKHRCreate, handle => new AccelerationStructureKHR(new AccelerationStructureKHRHandle(handle)), "Failed to create acceleration structure KHR."); }
    }

    internal AccelerationStructureNV CreateAccelerationStructureNV(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuAccelerationStructureNVCreate, handle => new AccelerationStructureNV(new AccelerationStructureNVHandle(handle)), "Failed to create acceleration structure NV."); }
    }

    public AccelerationStructureNV CreateAccelerationStructureNV<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuAccelerationStructureNVCreate, handle => new AccelerationStructureNV(new AccelerationStructureNVHandle(handle)), "Failed to create acceleration structure NV."); }
    }

    public AccelerationStructureNV CreateAccelerationStructureNV<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuAccelerationStructureNVCreate, handle => new AccelerationStructureNV(new AccelerationStructureNVHandle(handle)), "Failed to create acceleration structure NV."); }
    }

    internal MicromapEXT CreateMicromapEXT(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuMicromapEXTCreate, handle => new MicromapEXT(new MicromapEXTHandle(handle)), "Failed to create micromap EXT."); }
    }

    public MicromapEXT CreateMicromapEXT<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuMicromapEXTCreate, handle => new MicromapEXT(new MicromapEXTHandle(handle)), "Failed to create micromap EXT."); }
    }

    public MicromapEXT CreateMicromapEXT<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuMicromapEXTCreate, handle => new MicromapEXT(new MicromapEXTHandle(handle)), "Failed to create micromap EXT."); }
    }

    internal BufferCollectionFUCHSIA CreateBufferCollectionFUCHSIA(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuBufferCollectionFUCHSIACreate, handle => new BufferCollectionFUCHSIA(new BufferCollectionFUCHSIAHandle(handle)), "Failed to create buffer collection FUCHSIA."); }
    }

    public BufferCollectionFUCHSIA CreateBufferCollectionFUCHSIA<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuBufferCollectionFUCHSIACreate, handle => new BufferCollectionFUCHSIA(new BufferCollectionFUCHSIAHandle(handle)), "Failed to create buffer collection FUCHSIA."); }
    }

    public BufferCollectionFUCHSIA CreateBufferCollectionFUCHSIA<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuBufferCollectionFUCHSIACreate, handle => new BufferCollectionFUCHSIA(new BufferCollectionFUCHSIAHandle(handle)), "Failed to create buffer collection FUCHSIA."); }
    }

    internal PerformanceConfigurationINTEL AcquirePerformanceConfigurationINTEL(nint acquireInfo)
    {
        unsafe {
            ThrowIfDisposed();
            nint handle = nint.Zero;
            Result result = Library.Api.gpuPerformanceConfigurationINTELAcquire(_handle.Value, (void*)acquireInfo, &handle);
            Library.ThrowIfFailed(result, "Failed to acquire performance configuration INTEL.");
            return new PerformanceConfigurationINTEL(new PerformanceConfigurationINTELHandle(handle));
        }
    }

    public PerformanceConfigurationINTEL AcquirePerformanceConfigurationINTEL<TAcquireInfo>(in TAcquireInfo acquireInfo)
        where TAcquireInfo : unmanaged
    {
        unsafe {
            fixed (TAcquireInfo* acquireInfoPtr = &acquireInfo) {
                return AcquirePerformanceConfigurationINTEL((nint)acquireInfoPtr);
            }
        }
    }

    internal PipelineBinaryKHR CreatePipelineBinaryKHR(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuPipelineBinaryKHRCreate, handle => new PipelineBinaryKHR(new PipelineBinaryKHRHandle(handle)), "Failed to create pipeline binary KHR."); }
    }

    public PipelineBinaryKHR CreatePipelineBinaryKHR<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuPipelineBinaryKHRCreate, handle => new PipelineBinaryKHR(new PipelineBinaryKHRHandle(handle)), "Failed to create pipeline binary KHR."); }
    }

    public PipelineBinaryKHR CreatePipelineBinaryKHR<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuPipelineBinaryKHRCreate, handle => new PipelineBinaryKHR(new PipelineBinaryKHRHandle(handle)), "Failed to create pipeline binary KHR."); }
    }

    internal CuModuleNVX CreateCuModuleNVX(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuCuModuleNVXCreate, handle => new CuModuleNVX(new CuModuleNVXHandle(handle)), "Failed to create CUDA module NVX."); }
    }

    public CuModuleNVX CreateCuModuleNVX<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuCuModuleNVXCreate, handle => new CuModuleNVX(new CuModuleNVXHandle(handle)), "Failed to create CUDA module NVX."); }
    }

    public CuModuleNVX CreateCuModuleNVX<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuCuModuleNVXCreate, handle => new CuModuleNVX(new CuModuleNVXHandle(handle)), "Failed to create CUDA module NVX."); }
    }

    internal CuFunctionNVX CreateCuFunctionNVX(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuCuFunctionNVXCreate, handle => new CuFunctionNVX(new CuFunctionNVXHandle(handle)), "Failed to create CUDA function NVX."); }
    }

    public CuFunctionNVX CreateCuFunctionNVX<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuCuFunctionNVXCreate, handle => new CuFunctionNVX(new CuFunctionNVXHandle(handle)), "Failed to create CUDA function NVX."); }
    }

    public CuFunctionNVX CreateCuFunctionNVX<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuCuFunctionNVXCreate, handle => new CuFunctionNVX(new CuFunctionNVXHandle(handle)), "Failed to create CUDA function NVX."); }
    }

    internal OpticalFlowSessionNV CreateOpticalFlowSessionNV(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuOpticalFlowSessionNVCreate, handle => new OpticalFlowSessionNV(new OpticalFlowSessionNVHandle(handle)), "Failed to create optical flow session NV."); }
    }

    public OpticalFlowSessionNV CreateOpticalFlowSessionNV<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuOpticalFlowSessionNVCreate, handle => new OpticalFlowSessionNV(new OpticalFlowSessionNVHandle(handle)), "Failed to create optical flow session NV."); }
    }

    public OpticalFlowSessionNV CreateOpticalFlowSessionNV<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuOpticalFlowSessionNVCreate, handle => new OpticalFlowSessionNV(new OpticalFlowSessionNVHandle(handle)), "Failed to create optical flow session NV."); }
    }

    internal ShaderEXT CreateShaderEXT(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuShaderEXTCreate, handle => new ShaderEXT(new ShaderEXTHandle(handle)), "Failed to create shader EXT."); }
    }

    public ShaderEXT CreateShaderEXT<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuShaderEXTCreate, handle => new ShaderEXT(new ShaderEXTHandle(handle)), "Failed to create shader EXT."); }
    }

    public ShaderEXT CreateShaderEXT<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuShaderEXTCreate, handle => new ShaderEXT(new ShaderEXTHandle(handle)), "Failed to create shader EXT."); }
    }

    internal TensorARM CreateTensorARM(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuTensorARMCreate, handle => new TensorARM(new TensorARMHandle(handle)), "Failed to create tensor ARM."); }
    }

    public TensorARM CreateTensorARM<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuTensorARMCreate, handle => new TensorARM(new TensorARMHandle(handle)), "Failed to create tensor ARM."); }
    }

    public TensorARM CreateTensorARM<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuTensorARMCreate, handle => new TensorARM(new TensorARMHandle(handle)), "Failed to create tensor ARM."); }
    }

    internal TensorViewARM CreateTensorViewARM(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuTensorViewARMCreate, handle => new TensorViewARM(new TensorViewARMHandle(handle)), "Failed to create tensor view ARM."); }
    }

    public TensorViewARM CreateTensorViewARM<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuTensorViewARMCreate, handle => new TensorViewARM(new TensorViewARMHandle(handle)), "Failed to create tensor view ARM."); }
    }

    public TensorViewARM CreateTensorViewARM<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuTensorViewARMCreate, handle => new TensorViewARM(new TensorViewARMHandle(handle)), "Failed to create tensor view ARM."); }
    }

    internal DataGraphPipelineSessionARM CreateDataGraphPipelineSessionARM(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuDataGraphPipelineSessionARMCreate, handle => new DataGraphPipelineSessionARM(new DataGraphPipelineSessionARMHandle(handle)), "Failed to create data graph pipeline session ARM."); }
    }

    public DataGraphPipelineSessionARM CreateDataGraphPipelineSessionARM<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuDataGraphPipelineSessionARMCreate, handle => new DataGraphPipelineSessionARM(new DataGraphPipelineSessionARMHandle(handle)), "Failed to create data graph pipeline session ARM."); }
    }

    public DataGraphPipelineSessionARM CreateDataGraphPipelineSessionARM<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuDataGraphPipelineSessionARMCreate, handle => new DataGraphPipelineSessionARM(new DataGraphPipelineSessionARMHandle(handle)), "Failed to create data graph pipeline session ARM."); }
    }

    internal VideoSessionKHR CreateVideoSessionKHR(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuVideoSessionKHRCreate, handle => new VideoSessionKHR(new VideoSessionKHRHandle(handle)), "Failed to create video session KHR."); }
    }

    public VideoSessionKHR CreateVideoSessionKHR<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuVideoSessionKHRCreate, handle => new VideoSessionKHR(new VideoSessionKHRHandle(handle)), "Failed to create video session KHR."); }
    }

    public VideoSessionKHR CreateVideoSessionKHR<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuVideoSessionKHRCreate, handle => new VideoSessionKHR(new VideoSessionKHRHandle(handle)), "Failed to create video session KHR."); }
    }

    internal VideoSessionParametersKHR CreateVideoSessionParametersKHR(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuVideoSessionParametersKHRCreate, handle => new VideoSessionParametersKHR(new VideoSessionParametersKHRHandle(handle)), "Failed to create video session parameters KHR."); }
    }

    public VideoSessionParametersKHR CreateVideoSessionParametersKHR<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuVideoSessionParametersKHRCreate, handle => new VideoSessionParametersKHR(new VideoSessionParametersKHRHandle(handle)), "Failed to create video session parameters KHR."); }
    }

    public VideoSessionParametersKHR CreateVideoSessionParametersKHR<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuVideoSessionParametersKHRCreate, handle => new VideoSessionParametersKHR(new VideoSessionParametersKHRHandle(handle)), "Failed to create video session parameters KHR."); }
    }

    internal SemaphoreSciSyncPoolNV CreateSemaphoreSciSyncPoolNV(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuSemaphoreSciSyncPoolNVCreate, handle => new SemaphoreSciSyncPoolNV(new SemaphoreSciSyncPoolNVHandle(handle)), "Failed to create semaphore sci sync pool NV."); }
    }

    public SemaphoreSciSyncPoolNV CreateSemaphoreSciSyncPoolNV<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuSemaphoreSciSyncPoolNVCreate, handle => new SemaphoreSciSyncPoolNV(new SemaphoreSciSyncPoolNVHandle(handle)), "Failed to create semaphore sci sync pool NV."); }
    }

    public SemaphoreSciSyncPoolNV CreateSemaphoreSciSyncPoolNV<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuSemaphoreSciSyncPoolNVCreate, handle => new SemaphoreSciSyncPoolNV(new SemaphoreSciSyncPoolNVHandle(handle)), "Failed to create semaphore sci sync pool NV."); }
    }

    internal CudaModuleNV CreateCudaModuleNV(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuCudaModuleNVCreate, handle => new CudaModuleNV(new CudaModuleNVHandle(handle)), "Failed to create CUDA module NV."); }
    }

    public CudaModuleNV CreateCudaModuleNV<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuCudaModuleNVCreate, handle => new CudaModuleNV(new CudaModuleNVHandle(handle)), "Failed to create CUDA module NV."); }
    }

    public CudaModuleNV CreateCudaModuleNV<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuCudaModuleNVCreate, handle => new CudaModuleNV(new CudaModuleNVHandle(handle)), "Failed to create CUDA module NV."); }
    }

    internal CudaFunctionNV CreateCudaFunctionNV(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuCudaFunctionNVCreate, handle => new CudaFunctionNV(new CudaFunctionNVHandle(handle)), "Failed to create CUDA function NV."); }
    }

    public CudaFunctionNV CreateCudaFunctionNV<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuCudaFunctionNVCreate, handle => new CudaFunctionNV(new CudaFunctionNVHandle(handle)), "Failed to create CUDA function NV."); }
    }

    public CudaFunctionNV CreateCudaFunctionNV<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuCudaFunctionNVCreate, handle => new CudaFunctionNV(new CudaFunctionNVHandle(handle)), "Failed to create CUDA function NV."); }
    }

    internal ExternalComputeQueueNV CreateExternalComputeQueueNV(nint createInfo, nint allocator = 0)
    {
        unsafe { return CreateDeviceChild(createInfo, allocator, Library.Api.gpuExternalComputeQueueNVCreate, handle => new ExternalComputeQueueNV(new ExternalComputeQueueNVHandle(handle)), "Failed to create external compute queue NV."); }
    }

    public ExternalComputeQueueNV CreateExternalComputeQueueNV<TCreateInfo>(in TCreateInfo createInfo, nint allocator = 0)
        where TCreateInfo : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, allocator, Library.Api.gpuExternalComputeQueueNVCreate, handle => new ExternalComputeQueueNV(new ExternalComputeQueueNVHandle(handle)), "Failed to create external compute queue NV."); }
    }

    public ExternalComputeQueueNV CreateExternalComputeQueueNV<TCreateInfo, TAllocator>(in TCreateInfo createInfo, in TAllocator allocator)
        where TCreateInfo : unmanaged
        where TAllocator : unmanaged
    {
        unsafe { return CreateDeviceChild(in createInfo, in allocator, Library.Api.gpuExternalComputeQueueNVCreate, handle => new ExternalComputeQueueNV(new ExternalComputeQueueNVHandle(handle)), "Failed to create external compute queue NV."); }
    }
}


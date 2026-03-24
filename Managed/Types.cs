namespace GPU;

public readonly struct FramebufferSize
{
    public FramebufferSize(uint width, uint height)
    {
        Width = width;
        Height = height;
    }

    public uint Width { get; }
    public uint Height { get; }
}

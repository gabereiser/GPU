namespace GPU;

public sealed class GpuException : Exception
{
    public GpuException(string message, Result result)
        : base(message)
    {
        Result = result;
    }

    public Result Result { get; }
}


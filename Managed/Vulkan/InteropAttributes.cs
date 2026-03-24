namespace GPU;

[System.AttributeUsage(System.AttributeTargets.Field, AllowMultiple = false)]
public sealed class NativePointerAttribute : System.Attribute
{
    public NativePointerAttribute(System.Type? pointeeType = null)
    {
        PointeeType = pointeeType;
    }

    public System.Type? PointeeType { get; }

    public string? LengthExpression { get; init; }
}

[System.AttributeUsage(System.AttributeTargets.Field, AllowMultiple = false)]
public sealed class FixedCountAttribute : System.Attribute
{
    public FixedCountAttribute(int count)
    {
        Count = count;
    }

    public int Count { get; }
}

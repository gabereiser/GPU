using System.Runtime.InteropServices;
using System.Text;

namespace GPU;

public static class GpuMarshal
{
    public static GpuUtf8String String(string? value)
    {
        return new GpuUtf8String(value);
    }

    public static GpuUtf8StringArray StringArray(ReadOnlySpan<string> values)
    {
        return new GpuUtf8StringArray(values);
    }

    public static GpuUnmanagedArray<T> Array<T>(ReadOnlySpan<T> values)
        where T : unmanaged
    {
        return new GpuUnmanagedArray<T>(values);
    }
}

public sealed class GpuUtf8String : IDisposable
{
    private nint _pointer;

    public GpuUtf8String(string? value)
    {
        if (string.IsNullOrEmpty(value)) {
            _pointer = nint.Zero;
            ByteLength = 0;
            return;
        }

        int byteCount = Encoding.UTF8.GetByteCount(value);
        _pointer = Marshal.AllocHGlobal(byteCount + 1);
        unsafe {
            Span<byte> buffer = new((void*)_pointer, byteCount + 1);
            int written = Encoding.UTF8.GetBytes(value, buffer);
            buffer[written] = 0;
            ByteLength = written;
        }
    }

    public nint Pointer => _pointer;
    public int ByteLength { get; }
    public bool IsEmpty => _pointer == nint.Zero;

    public void Dispose()
    {
        if (_pointer == nint.Zero) {
            return;
        }

        Marshal.FreeHGlobal(_pointer);
        _pointer = nint.Zero;
    }
}

public sealed class GpuUtf8StringArray : IDisposable
{
    private GpuUtf8String[]? _strings;
    private nint _pointer;

    public GpuUtf8StringArray(ReadOnlySpan<string> values)
    {
        Count = (uint)values.Length;
        if (values.IsEmpty) {
            return;
        }

        _strings = new GpuUtf8String[values.Length];
        for (int i = 0; i < values.Length; ++i) {
            _strings[i] = new GpuUtf8String(values[i]);
        }

        _pointer = Marshal.AllocHGlobal(IntPtr.Size * values.Length);
        nint[] pointers = new nint[values.Length];
        for (int i = 0; i < _strings.Length; ++i) {
            pointers[i] = _strings[i].Pointer;
        }
        Marshal.Copy(pointers, 0, _pointer, values.Length);
    }

    public nint Pointer => _pointer;
    public uint Count { get; }
    public bool IsEmpty => _pointer == nint.Zero;

    public void Dispose()
    {
        if (_strings is not null) {
            foreach (GpuUtf8String value in _strings) {
                value.Dispose();
            }
            _strings = null;
        }

        if (_pointer == nint.Zero) {
            return;
        }

        Marshal.FreeHGlobal(_pointer);
        _pointer = nint.Zero;
    }
}

public sealed class GpuUnmanagedArray<T> : IDisposable
    where T : unmanaged
{
    private nint _pointer;

    public GpuUnmanagedArray(ReadOnlySpan<T> values)
    {
        Count = (uint)values.Length;
        if (values.IsEmpty) {
            return;
        }

        int sizeInBytes = Marshal.SizeOf<T>() * values.Length;
        _pointer = Marshal.AllocHGlobal(sizeInBytes);

        unsafe {
            values.CopyTo(new Span<T>((void*)_pointer, values.Length));
        }
    }

    public nint Pointer => _pointer;
    public uint Count { get; }
    public bool IsEmpty => _pointer == nint.Zero;

    public void Dispose()
    {
        if (_pointer == nint.Zero) {
            return;
        }

        Marshal.FreeHGlobal(_pointer);
        _pointer = nint.Zero;
    }
}


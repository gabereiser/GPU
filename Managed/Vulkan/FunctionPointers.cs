namespace GPU;

public unsafe delegate nint PFN_gpuAllocationFunction(
    nint pUserData,
    nuint size,
    nuint alignment,
    uint allocationScope);

public unsafe delegate void PFN_gpuFreeFunction(
    nint pUserData,
    nint pMemory);

public unsafe delegate nint PFN_gpuReallocationFunction(
    nint pUserData,
    nint pOriginal,
    nuint size,
    nuint alignment,
    uint allocationScope);

public unsafe delegate void PFN_gpuInternalAllocationNotification(
    nint pUserData,
    nuint size,
    uint allocationType,
    uint allocationScope);

public unsafe delegate void PFN_gpuInternalFreeNotification(
    nint pUserData,
    nuint size,
    uint allocationType,
    uint allocationScope);

public unsafe delegate nint PFN_gpuDebugReportCallbackEXT(
    uint flags,
    uint objectType,
    ulong @object,
    nuint location,
    int messageCode,
    nint pLayerPrefix,
    nint pMessage,
    nint pUserData);

public unsafe delegate uint PFN_gpuDebugUtilsMessengerCallbackEXT(
    uint messageSeverity,
    uint messageTypes,
    nint pCallbackData,
    nint pUserData);

public unsafe delegate void PFN_gpuDeviceMemoryReportCallbackEXT(
    nint pCallbackData,
    nint pUserData);

public unsafe delegate void PFN_gpuFaultCallbackFunction(
    nint pFaultData);

public unsafe delegate nint PFN_gpuGetInstanceProcAddrLUNARG(
    nint instance,
    nint pName);

public unsafe delegate nint PFN_gpuVoidFunction();

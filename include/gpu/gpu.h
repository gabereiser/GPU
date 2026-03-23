#pragma once

#include <stdint.h>

#if defined(_WIN32)
#if defined(GPU_BUILD)
#define GPU_API __declspec(dllexport)
#else
#define GPU_API __declspec(dllimport)
#endif
#define GPU_CALL __cdecl
#else
#define GPU_API
#define GPU_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* GPUHandle;
typedef void (*GPUFunction)(void);

GPU_API uint32_t GPU_CALL gpuGetApiVersion(void);
GPU_API GPUFunction GPU_CALL gpuGetInstanceProcAddr(GPUHandle instance, const char* name);
GPU_API const char* GPU_CALL gpuGetLastError(void);
GPU_API int32_t GPU_CALL gpuGetRequiredInstanceExtensions(const char*** extensions, uint32_t* count);

#ifdef __cplusplus
}
#endif

#pragma once

/*
 * Minimal GPU‑named structures that mirror the Vulkan creation‑info structs.
 * They contain only the fields needed for the README example and are
 * directly forwarded to the underlying Vulkan loader via the GPU wrapper.
 * No Vulkan‑prefixed symbols appear in user code.
 */
#include <stdint.h>

/* Structure type identifiers – values match the Vulkan spec. */
#define GPU_STRUCTURE_TYPE_APPLICATION_INFO        0u
#define GPU_STRUCTURE_TYPE_INSTANCE_CREATE_INFO    1u
#define GPU_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO 2u
#define GPU_STRUCTURE_TYPE_DEVICE_CREATE_INFO      3u

typedef struct GpuApplicationInfo {
    uint32_t    sType;
    const char* pApplicationName;
    uint32_t    applicationVersion;
    const char* pEngineName;
    uint32_t    engineVersion;
    uint32_t    apiVersion;
} GpuApplicationInfo;

typedef struct GpuInstanceCreateInfo {
    uint32_t    sType;
    const GpuApplicationInfo* pApplicationInfo;
    uint32_t    enabledExtensionCount;
    const char* const* ppEnabledExtensionNames;
} GpuInstanceCreateInfo;

typedef struct GpuDeviceQueueCreateInfo {
    uint32_t sType;
    uint32_t queueFamilyIndex;
    uint32_t queueCount;
    const float* pQueuePriorities;
} GpuDeviceQueueCreateInfo;

typedef struct GpuDeviceCreateInfo {
    uint32_t sType;
    uint32_t queueCreateInfoCount;
    const GpuDeviceQueueCreateInfo* pQueueCreateInfos;
} GpuDeviceCreateInfo;

#include "gpu/gpu.h"

#include "Internal/Error.h"

extern "C" {

GPU_API uint32_t GPU_CALL gpuGetApiVersion(void) {
    gpu::internal::clearLastError();
    return VK_HEADER_VERSION_COMPLETE;
}

GPU_API const char* GPU_CALL gpuGetLastError(void) {
    return gpu::internal::getLastError();
}



}  // extern "C"

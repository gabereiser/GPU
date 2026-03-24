#include "Internal/Error.h"

namespace {

thread_local const char* g_lastError = nullptr;

}  // namespace

namespace gpu::internal {

void clearLastError() {
    g_lastError = nullptr;
}

void setLastError(const char* message) {
    g_lastError = message;
}

const char* getLastError() {
    return g_lastError;
}

}  // namespace gpu::internal

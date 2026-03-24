#pragma once

namespace gpu::internal {

void clearLastError();
void setLastError(const char* message);
const char* getLastError();

}  // namespace gpu::internal

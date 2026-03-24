#include "Queue.h"

#include "Device.h"

void gpuQueueRetain(GPUQueue queue) {
    if (queue != nullptr) {
        ++queue->refCount;
    }
}

void gpuQueueDrop(GPUQueue queue) {
    if (queue == nullptr) {
        return;
    }

    if (queue->refCount > 0) {
        --queue->refCount;
    }

    if (queue->refCount == 0) {
        gpuDeviceDrop(queue->device);
        delete queue;
    }
}

extern "C" {

GPU_API VkQueue GPU_CALL gpuQueueGetVkHandle(GPUQueue queue) {
    return queue != nullptr && !queue->destroyRequested ? queue->handle : VK_NULL_HANDLE;
}

GPU_API GPUDevice GPU_CALL gpuQueueGetDevice(GPUQueue queue) {
    return queue != nullptr && !queue->destroyRequested ? queue->device : nullptr;
}

GPU_API uint32_t GPU_CALL gpuQueueGetFamilyIndex(GPUQueue queue) {
    return queue != nullptr && !queue->destroyRequested ? queue->familyIndex : 0;
}

GPU_API uint32_t GPU_CALL gpuQueueGetQueueIndex(GPUQueue queue) {
    return queue != nullptr && !queue->destroyRequested ? queue->queueIndex : 0;
}

GPU_API void GPU_CALL gpuQueueRelease(GPUQueue queue) {
    if (queue == nullptr || queue->destroyRequested) {
        return;
    }

    queue->destroyRequested = true;
    gpuQueueDrop(queue);
}

}  // extern "C"

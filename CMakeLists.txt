cmake_minimum_required(VERSION 3.16)

project(GPU LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(dependencies/Vulkan-Headers)
add_subdirectory(dependencies/Vulkan-Loader)
add_subdirectory(dependencies/glfw)

set(GPU_GENERATOR ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate_vulkan_abi.py)
set(VK_XML ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Vulkan-Headers/registry/vk.xml)
set(GPU_GENERATED_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/gpu/gpu_vulkan.h)
set(GPU_GENERATED_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Vulkan.cpp)


add_custom_target(generate_gpu_vulkan_abi
    DEPENDS ${GPU_GENERATED_HEADER} ${GPU_GENERATED_SOURCE}
)

add_library(${PROJECT_NAME} SHARED
    src/GPU.cpp
    src/Instance.cpp
    src/PhysicalDevice.cpp
    src/Device.cpp
    src/Queue.cpp
    src/CommandPool.cpp
    src/CommandBuffer.cpp
    src/DeviceMemory.cpp
    src/Buffer.cpp
    src/BufferView.cpp
    src/Image.cpp
    src/ImageView.cpp
    src/ShaderModule.cpp
    src/Pipeline.cpp
    src/PipelineLayout.cpp
    src/Sampler.cpp
    src/DescriptorSetLayout.cpp
    src/DescriptorPool.cpp
    src/DescriptorSet.cpp
    src/Fence.cpp
    src/Semaphore.cpp
    src/Event.cpp
    src/QueryPool.cpp
    src/Framebuffer.cpp
    src/RenderPass.cpp
    src/PipelineCache.cpp
    src/DescriptorUpdateTemplate.cpp
    src/SamplerYcbcrConversion.cpp
    src/PrivateDataSlot.cpp
    src/Surface.cpp
    src/Swapchain.cpp
    src/Internal/Error.cpp
    src/Internal/GlfwState.cpp
    src/DebugReportCallbackEXT.cpp
    src/DebugUtilsMessengerEXT.cpp
    src/ValidationCacheEXT.cpp
    src/DeferredOperationKHR.cpp
    src/IndirectCommandsLayoutNV.cpp
    src/IndirectCommandsLayoutEXT.cpp
    src/IndirectExecutionSetEXT.cpp
    src/AccelerationStructureKHR.cpp
    src/AccelerationStructureNV.cpp
    src/MicromapEXT.cpp
    src/BufferCollectionFUCHSIA.cpp
    src/PerformanceConfigurationINTEL.cpp
    src/PipelineBinaryKHR.cpp
    src/CuModuleNVX.cpp
    src/CuFunctionNVX.cpp
    src/OpticalFlowSessionNV.cpp
    src/ShaderEXT.cpp
    src/TensorARM.cpp
    src/TensorViewARM.cpp
    src/DataGraphPipelineSessionARM.cpp
    src/DisplayKHR.cpp
    src/DisplayModeKHR.cpp
    src/VideoSessionKHR.cpp
    src/VideoSessionParametersKHR.cpp
    src/SemaphoreSciSyncPoolNV.cpp
    src/CudaModuleNV.cpp
    src/CudaFunctionNV.cpp
    src/ExternalComputeQueueNV.cpp
    ${GPU_GENERATED_SOURCE}
)

add_dependencies(${PROJECT_NAME} generate_gpu_vulkan_abi)

target_compile_definitions(${PROJECT_NAME} PRIVATE GPU_BUILD)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Vulkan-Headers/include
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    vulkan
    glfw
)

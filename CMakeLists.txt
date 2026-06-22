cmake_minimum_required(VERSION 3.16)

project(GPU LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Disable optional optimizer that requires external SPIRV-Tools
set(ENABLE_OPT 0)
set(SHADERC_SKIP_TESTS ON)
set(SHADERC_SKIP_EXAMPLES ON)
add_subdirectory(dependencies/Vulkan-Headers)
add_subdirectory(dependencies/Vulkan-Loader)

set(ENABLE_SPIRV ON)
add_subdirectory(dependencies/glslang)






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

    src/Swapchain.cpp
    src/Internal/Error.cpp

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
    src/Surface.cpp

)

target_sources(${PROJECT_NAME} PRIVATE src/ShaderCompiler/ShaderCompiler.cpp
    dependencies/glslang/glslang/ResourceLimits/ResourceLimits.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    GPU_BUILD
    GPU_USE_GLSLANG
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Vulkan-Headers/include
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    vulkan
    glslang
)

# Test program to verify shader compilation
# add_executable(shader_compile_test test/ShaderCompileTest.cpp)
# Link against the GPU library and shaderc_shared (which pulls glslang, etc.)
# target_link_libraries(shader_compile_test PRIVATE ${PROJECT_NAME})
# Ensure Vulkan headers are found via include directories from earlier


cmake_minimum_required(VERSION 3.16)

project(GPU LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add dependency subdirectories
add_subdirectory(dependencies/Vulkan-Headers)
add_subdirectory(dependencies/Vulkan-Loader)
add_subdirectory(dependencies/glfw)

# Add library
add_library(${PROJECT_NAME} SHARED
    src/gpu.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GPU_BUILD)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Vulkan-Headers/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    vulkan
    glfw
)

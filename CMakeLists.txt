cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(vkRenderer
  VERSION 1.0
  LANGUAGES CXX
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(AddShader)

set (THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)
add_subdirectory(${THIRDPARTY_DIR})

set(headers 
    ${CMAKE_SOURCE_DIR}/src/Application.h
    ${CMAKE_SOURCE_DIR}/src/Util.h
)

set(sources
    ${CMAKE_SOURCE_DIR}/src/Application.cpp
    ${CMAKE_SOURCE_DIR}/src/Util.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

set(shaders
    ${CMAKE_BINARY_DIR}/shaders/vert.spv
    ${CMAKE_BINARY_DIR}/shaders/frag.spv
)

add_shader(vertex ${CMAKE_SOURCE_DIR}/assets/shaders/shader.vert ${CMAKE_BINARY_DIR}/shaders/vert.spv)
add_shader(fragment ${CMAKE_SOURCE_DIR}/assets/shaders/shader.frag ${CMAKE_BINARY_DIR}/shaders/frag.spv)

add_executable(vkRenderer ${headers} ${sources} ${shaders})

set_target_properties(vkRenderer
    PROPERTIES
    CXX_STANDARD 17
    OUTPUT_NAME "main"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_include_directories(vkRenderer
    PRIVATE ${THIRDPARTY_DIR}/glad/include
    PRIVATE ${THIRDPARTY_DIR}/glfw/include
)

target_link_libraries(vkRenderer
    PRIVATE glad
    PRIVATE glfw
)

target_compile_definitions(vkRenderer
    PRIVATE DEBUG
    PRIVATE GLFW_INCLUDE_NONE
)
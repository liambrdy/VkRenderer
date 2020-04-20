project(glad)

add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vulkan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/vk_platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/vulkan.h
)

target_include_directories(glad
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
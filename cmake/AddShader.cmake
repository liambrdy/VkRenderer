function(add_shader SHADER_STAGE INPUT_FILE OUTPUT_FILE)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)
    add_custom_command(
        OUTPUT ${OUTPUT_FILE}
        COMMAND glslc -fshader-stage=${SHADER_STAGE} ${INPUT_FILE} -o ${OUTPUT_FILE}
        MAIN_DEPENDENCY ${INPUT_FILE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endfunction()
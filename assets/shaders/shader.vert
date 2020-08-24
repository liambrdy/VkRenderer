#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec4 a_Color;

layout (location = 0) out vec4 v_Color;

void main()
{
    gl_Position = vec4(a_Position, 0.0, 1.0);
    v_Color = a_Color;
}
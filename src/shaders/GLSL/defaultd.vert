#version 410 core

uniform dmat4 model_matrix;
uniform dmat4 projection_matrix;

layout(location = 0) in dvec4 position;
layout(location = 1) in vec4 color;

out vec4 vs_gs_color;

void main() 
{
    vs_gs_color = color;
    gl_Position = vec4(projection_matrix * (model_matrix * position));
}
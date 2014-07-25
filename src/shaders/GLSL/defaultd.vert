#version 410 core

uniform dmat4 model_matrix;
uniform dmat4 projection_matrix;

layout(location = 0) in dvec4 position;
layout(location = 1) in dvec4 color;

out dvec4 vs_fs_color;

void main() 
{
    vs_fs_color = color;
    gl_Position = projection_matrix * (model_matrix * position);
}
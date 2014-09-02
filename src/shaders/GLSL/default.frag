#version 410 core

in vec4 vs_gs_color;
out vec4 final_color;

void main() 
{
    final_color = vs_gs_color;
}
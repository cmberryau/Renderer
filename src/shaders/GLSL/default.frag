#version 410 core

in vec4 gs_fs_color;
out vec4 final_color;

void main() 
{
    final_color = gs_fs_color;
}
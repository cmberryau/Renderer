#version 410 core

in vec4 vs_fs_color;

out vec4 final_color;

void main() 
{
    final_color = vs_fs_color;
}
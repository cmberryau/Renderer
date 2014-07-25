#version 410 core

in dvec4 vs_fs_color;

out dvec4 final_color;

void main() 
{
    final_color = vs_fs_color;
}
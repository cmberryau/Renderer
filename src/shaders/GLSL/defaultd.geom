#version 410 core

layout(points) in;
layout(points, max_vertices = 1) out;

in vec4 vs_gs_color[];
out vec4 gs_fs_color;

void main() 
{
    gs_fs_color = vs_gs_color[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    EndPrimitive();    
}
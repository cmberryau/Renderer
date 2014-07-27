#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 vs_gs_color[];
out vec4 gs_fs_color;

void main() 
{
    gs_fs_color = vs_gs_color[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gs_fs_color = vs_gs_color[1];
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gs_fs_color = vs_gs_color[2];
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}
#version 410 core

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

layout(location = 0) in vec4 position;

out vec4 vs_fs_color;

void main() 
{
    if(model_matrix[3][1] == 0.5)
        vs_fs_color = vec4(0.0, 1.0, 0.0, 1.0);
    else
        vs_fs_color = vec4(1.0, 0.0, 0.0, 1.0);
    
    gl_Position = projection_matrix * (model_matrix * position);
}
#version 410 core

uniform mat4 model_matrix;

layout(location = 0) in vec4 position;

void main() 
{
    gl_Position = position * model_matrix;
}
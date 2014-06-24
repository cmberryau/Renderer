#version 410 core

<<<<<<< HEAD
layout(location = 0) in vec4 vPosition;

void main()
{
    gl_Position = vPosition;
=======
uniform mat4 model_matrix;

layout(location = 0) in vec4 position;

void main() 
{
    gl_Position = position;
>>>>>>> FETCH_HEAD
}
attribute vec4 position;
attribute vec3 normal;
attribute vec4 color;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

varying vec4 vs_gs_color;

void main()
{
    vs_gs_color = vec4(0.0, 1.0, 0.0, 1.0);
    gl_Position = projection_matrix * (model_matrix * position);
}

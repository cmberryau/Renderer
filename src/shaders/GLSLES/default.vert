attribute vec4 position;
attribute vec3 normal;
attribute vec4 color;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

varying vec4 vs_gs_color;

void main()
{
    vec4 world_position = model_matrix * position;
    vec3 world_normal = normalize(vec3(model_matrix * vec4(normal, 0.0)));
    vec3 light_vec = normalize(vec3(0.0, 0.0, 0.0) - world_position.xyz);

    float ndotl = dot(world_normal.xyz, light_vec);

    vs_gs_color = color * ndotl;
    gl_Position = projection_matrix * world_position;
}

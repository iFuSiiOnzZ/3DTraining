#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out VS_OUT
{
    vec2 uv;
    vec3 vertex;
    vec3 normal;
} vs_out;

///////////////////////////////////////////////////////////////////////////////

uniform mat4 viewMatrix, modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vs_out.uv = uv;
    vs_out.vertex = vec3(modelMatrix * vec4(vertex, 1.0));
    vs_out.normal = vec3(transpose(inverse(modelMatrix)) * vec4(normal, 0.0));

    gl_Position = projectionMatrix * viewMatrix * vec4(vs_out.vertex, 1.0);
}

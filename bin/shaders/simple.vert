#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 viewMatrix, modelMatrix;
uniform mat4 projectionMatrix;

out vec2 texUV;
out vec3 fragPos;
out vec3 fragNormal;

void main()
{
    texUV = uv;
    fragPos = vec3(modelMatrix * vec4(vertex, 1.0));
    fragNormal = vec3(transpose(inverse(modelMatrix)) * vec4(normal, 0.0));

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
}

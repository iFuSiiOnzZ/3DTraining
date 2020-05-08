#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out VS_OUT
{
    vec2 uv;
    vec3 vertex;
    vec3 normal;

    vec4 vertexLightSpace;
    mat3 TBN;
} vs_out;

///////////////////////////////////////////////////////////////////////////////

uniform mat4 projViewMatrix, modelMatrix;
uniform mat4 lightSpaceMatrix;

void main()
{
    mat4 glNormalMatrix = transpose(inverse(modelMatrix));

    vs_out.uv = uv;
    vs_out.normal = vec3(glNormalMatrix * vec4(normal, 0.0));

    vec3 B = vec3(glNormalMatrix * vec4(bitangent, 0.0));
    vec3 T = vec3(glNormalMatrix * vec4(tangent, 0.0));
    vs_out.TBN = mat3(normalize(T), normalize(B), normalize(vs_out.normal));

    vs_out.vertex = vec3(modelMatrix * vec4(vertex, 1.0));
    vs_out.vertexLightSpace = lightSpaceMatrix * vec4(vs_out.vertex, 1.0);

    gl_Position = projViewMatrix * vec4(vs_out.vertex, 1.0);
}

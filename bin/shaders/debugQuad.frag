#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D depthMap;
uniform float zNear;
uniform float zFar;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));
}

void main()
{
    float depthValue = texture(depthMap, TexCoord).r;
    FragColor = vec4(vec3(depthValue+0.2), 1.0);
}

#version 330

layout(location = 0) in vec3 glVertex;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

out vec3 texCoord;

void main()
{
    vec4 glPos = projectionMatrix * viewMatrix * modelMatrix * vec4(glVertex, 1.0f);
    texCoord = vec3(glVertex.x, -glVertex.yz);
    gl_Position = glPos.xyww;
}
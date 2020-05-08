#version 330 core

layout (location = 0) in vec3 inVertex;

///////////////////////////////////////////////////////////////////////////////

out vec4 vertex;

uniform mat4 modelMatrix;
uniform mat4 projViewMatrix;

void main()
{
    vertex = modelMatrix * vec4(inVertex, 1.0);
    gl_Position = projViewMatrix * vertex;
}

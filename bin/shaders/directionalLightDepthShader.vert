#version 330 core
layout (location = 0) in vec3 vertex;

///////////////////////////////////////////////////////////////////////////////

uniform mat4 modelMatrix;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = lightSpaceMatrix * modelMatrix * vec4(vertex, 1.0);
}

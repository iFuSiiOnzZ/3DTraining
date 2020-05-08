#version 330 core

///////////////////////////////////////////////////////////////////////////////

uniform vec3 cameraPos;
uniform float zFar;

in vec4 vertex;

void main()
{
    float lightDistance = length(vertex.xyz - cameraPos);
    gl_FragDepth = lightDistance / zFar;
}

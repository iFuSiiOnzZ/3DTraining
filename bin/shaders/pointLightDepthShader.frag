#version 330 core

///////////////////////////////////////////////////////////////////////////////

uniform vec3 lightPos;
uniform float zFar;

in vec4 vertex;

void main()
{
    float lightDistance = length(vertex.xyz - lightPos);
    gl_FragDepth = lightDistance / zFar;
}

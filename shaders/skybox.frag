#version 330

in  vec3    texCoord;
out vec4    fragColor;

uniform samplerCube cubeMap;   

void main()
{
	fragColor = texture(cubeMap, texCoord);
}

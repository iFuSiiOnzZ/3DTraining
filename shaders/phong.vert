#version 330

layout (location = 0) in vec3 glVertex;
layout (location = 1) in vec3 glNormal;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

uniform vec4 l_Pos;
uniform vec4 c_Pos;

uniform vec4 l_Amb;
uniform vec4 l_Diff;
uniform vec4 l_Spec;

out vec4 N;
out vec4 V;

out vec4 L;
out vec4 C;

void main()
{
	//For the normals
	mat3 glNormalMatrix = transpose(inverse(mat3(viewMatrix)));

	//Transform vertex and normal to viewMatrix
	N = vec4(glNormalMatrix * mat3(modelMatrix) * glNormal, 1.0f);
	V = viewMatrix * modelMatrix * vec4(glVertex, 1.0f);

	//Transform light and camara position to viewMatrix
	L = viewMatrix * l_Pos;
	C = viewMatrix * c_Pos;
	
	//Vertex transform
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(glVertex, 1.0f);
}

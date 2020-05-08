#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

///////////////////////////////////////////////////////////////////////////////

uniform mat4 lightSpaceMatrix[6];
out vec4 vertex;

void main()
{
    for(int cubeFace = 0; cubeFace < 6; ++cubeFace)
    {
        gl_Layer = cubeFace;

        vertex = gl_in[0].gl_Position;
        gl_Position = lightSpaceMatrix[cubeFace] * vertex;
        EmitVertex();

        vertex = gl_in[1].gl_Position;
        gl_Position = lightSpaceMatrix[cubeFace] * vertex;
        EmitVertex();

        vertex = gl_in[2].gl_Position;
        gl_Position = lightSpaceMatrix[cubeFace] * vertex;
        EmitVertex();

        EndPrimitive();
    }
}

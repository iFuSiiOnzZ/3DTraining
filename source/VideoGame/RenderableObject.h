#pragma once

#include "Common/Math/Matrix/Matrix.h"
#include "Common/Math/Vector/Vector.h"
#include <vector>

class CRenderableVertex;
class CShaderProgram;
class CTexture;

struct CRenderableObject
{
    CMatrix4f transform;
    CVector3f Ka, Kd, Ks;
    CRenderableVertex *mesh;
    CTexture *TKa, *TKd, *TKs, *Bump;

    float Ns, Ni, d;
    int illumModel;

    CRenderableObject();
    ~CRenderableObject();

    void bind(CShaderProgram &shaderProgram);
    void unbind(CShaderProgram &shaderProgram);
    void render();

    static std::vector<CRenderableObject> *loadObject(const char *filename);
    static void free(std::vector<CRenderableObject> *obj);
};

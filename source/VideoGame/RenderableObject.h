#pragma once

#include "Common/Math/Vector/Vector.h"
#include <vector>

class CRenderableVertex;
class CShaderProgram;
class CTexture;

struct CRenderableObject
{
    CTexture *TKa, *TKd, *TKs;
    CRenderableVertex *mesh;
    CVector3f Ka, Kd, Ks;

    float Ns, Ni, d;
    int illumModel;

    CRenderableObject();
    ~CRenderableObject();

    void bind(CShaderProgram &shaderProgram);
    void unbind();
    void render();

    static std::vector<CRenderableObject> *loadObject(const char *filename);
    static void free(std::vector<CRenderableObject> *obj);
};

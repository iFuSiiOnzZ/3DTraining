#pragma once

#include <Windows.h>
#include <gl\glew.h>
#include <gl\wglew.h>

#include "./Common/Math/Vector/Vector.h"

namespace CDebugRender
{
    void DrawLine       (const CVector3f &start, const CVector3f &end, const CVector3f &color);
    void DrawGrid       (int nLines, float sz, const CVector3f &color);
    void DrawAxis       (const CVector3f &origin, float sz);

    void DrawCube       (const CVector3f &pos, const CVector3f &color = CVector3f(1.0f, 1.0f, 1.0f));
    void RenderQuad     ();

    int TakeScreenShot  (const char *filename);

};

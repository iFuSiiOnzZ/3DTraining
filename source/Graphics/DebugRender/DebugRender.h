#pragma once

#include <Windows.h>
#include <gl\glew.h>
#include <gl\wglew.h>

#include "./Common/Math/Vector/Vector.h"

namespace CDebugRender
{
    void DrawLine       (const CVector4f &start, const CVector4f &end, const CVector4f &color);
    void DrawGrid       (int nLines, float sz, const CVector4f &color);
    void DrawAxis       (const CVector4f &origin, float sz);

    void DrawCube       (float x, float y, float z);
    void RenderQuad     ();

    int TakeScreenShot  (const char *filename);

};

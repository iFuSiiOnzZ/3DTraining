#pragma once

#include <Windows.h>
#include <gl\glew.h>
#include <gl\wglew.h>

#include "./Common/Math/Vector/Vector.h"

class CDebugRender
{
    private:

    public:
        CDebugRender        (void);
        ~CDebugRender       (void);

        void DrawLine       (const CVector4f &start, const CVector4f &end, const CVector4f &color);
        void DrawGrid       (int nLines, float sz, CVector4f &color);
        void DrawAxis       (const CVector4f &origin, float sz);
};

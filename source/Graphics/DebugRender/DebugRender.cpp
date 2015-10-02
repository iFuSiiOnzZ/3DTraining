#include "./DebugRender.h"

CDebugRender::CDebugRender(void)
{
}

CDebugRender::~CDebugRender(void)
{
}

void CDebugRender::DrawLine(const CVector4f &start, const CVector4f &end, const CVector4f &color)
{
    float v[6] = { start.x, start.y, start.z, end.x, end.y, end.z };
    float c[6] = { color.x, color.y, color.z, color.x, color.y, color.z };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, v);
    glColorPointer(3, GL_FLOAT, 0, c);

    glDrawArrays(GL_LINES, 0, 2);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void CDebugRender::DrawAxis(const CVector4f &origin, float sz)
{
    DrawLine(origin, CVector4f(sz, 0.0f, 0.0f) + origin, CVector4f(1.0f, 0.0f, 0.0f));
    DrawLine(origin, CVector4f(0.0f, sz, 0.0f) + origin, CVector4f(0.0f, 1.0f, 0.0f));
    DrawLine(origin, CVector4f(0.0f, 0.0f, sz) + origin, CVector4f(0.0f, 0.0f, 1.0f));
}
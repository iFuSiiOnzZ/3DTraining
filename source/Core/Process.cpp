#include "./Process.h"

CProcess::CProcess(CGraphicsManager *graphicsManager)
{
    m_pGraphicsManager = graphicsManager;
}

void CProcess::Release(const S_PLATFORM *) { }
void CProcess::Init(const S_PLATFORM *) { }

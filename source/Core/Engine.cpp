#include "./Engine.h"
#include "./Process.h"

CEngine::CEngine(CProcess *process)
{
    m_pProcess = process;
}

void CEngine::Release(void)
{
    m_pProcess->Release();
}

void CEngine::Init(void)
{
    m_pProcess->Init();
}

void CEngine::Update(const S_PLATFORM *platform)
{
    m_pProcess->Update(platform);
}

void CEngine::Render(void)
{
    m_pProcess->Render();
}

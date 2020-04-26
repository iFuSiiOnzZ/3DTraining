#include "./Engine.h"
#include "./Process.h"

CEngine::CEngine(CProcess *process)
{
    m_pProcess = process;
}

void CEngine::Release(const S_PLATFORM *platform)
{
    m_pProcess->Release(platform);
}

void CEngine::Init(const S_PLATFORM *platform)
{
    m_pProcess->Init(platform);
}

void CEngine::Update(const S_PLATFORM *platform)
{
    m_pProcess->Update(platform);
}

void CEngine::Render(const S_PLATFORM *platform)
{
    m_pProcess->Render(platform);
}

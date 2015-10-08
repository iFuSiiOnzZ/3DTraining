#include "./Engine.h"
#include "./Process.h"

CEngine::CEngine(CProcess *l_pProcess)
{
    m_pProcess = l_pProcess;
}

CEngine::~CEngine(void)
{

}

void CEngine::Release(void)
{
    m_pProcess->Release();
}

void CEngine::Init(void)
{
    m_pProcess->Init();
}

void CEngine::Update(void)
{
    m_pProcess->Update();
}

void CEngine::Render(void)
{
    m_pProcess->Render();
}
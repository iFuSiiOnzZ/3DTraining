#include "./InputManager.h"

CInputManager::CInputManager(int sWidth, int sHeight, HWND &hWnd) : m_MouseInput(sWidth, sHeight, hWnd), m_KeyboardInput()
{

}

CInputManager::~CInputManager()
{
}

void CInputManager::Execute(void)
{
    Update();
}

void CInputManager::AddKey(const std::string &l_KeyName, unsigned int key)
{
    CRWWriteAutoLock l_Lock(m_RWLock);
	m_KeyboardInput.AddKey(l_KeyName, key);
}

void CInputManager::Update(void)
{
    CRWWriteAutoLock l_Lock(m_RWLock);
	m_KeyboardInput.Update();
    m_MouseInput.Update();
}

bool CInputManager::isKeyPressed(const std::string &keyName)
{
    CRWReadAutoLock l_Lock(m_RWLock);
	return(m_KeyboardInput.isKeyPressed(keyName));
}

int CInputManager::GetDeltaX(void)
{
    CRWReadAutoLock l_Lock(m_RWLock);
    return m_MouseInput.GetDeltaX();
}

int CInputManager::GetDeltaY(void)
{
    CRWReadAutoLock l_Lock(m_RWLock);
    return m_MouseInput.GetDeltaY();
}

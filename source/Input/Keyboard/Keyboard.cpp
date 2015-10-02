#include "./Keyboard.h"
#include "Common/TaskPool/Utils/ThreadLock.h"

CKeyboard::CKeyboard(void)
{
}

CKeyboard::~CKeyboard(void)
{
}

void CKeyboard::Execute(void)
{
    Update();
}

void CKeyboard::AddKey(const std::string &l_Name, unsigned int l_Key)
{
    CRWWriteAutoLock l_Lock(m_RWLock);
    m_KeyMap.add(l_Name, std::pair<unsigned int, bool>(l_Key, false));
}

void CKeyboard::Update(void)
{	
    CRWReadAutoLock l_Lock(m_RWLock);
    KeyMapType::HashMapType &l_HashMap = m_KeyMap.getHashMap();
    
    for(KeyMapType::HashMapType::iterator it = l_HashMap.begin(); it != l_HashMap.end(); it++)
	{
		it->Value.second = (GetAsyncKeyState(it->Value.first) & 0x8000) != 0;
	}
}

bool CKeyboard::isKeyPressed(const std::string &l_Name)
{
    CRWReadAutoLock l_Lock(m_RWLock);
    KeyMapType::MapEntryType *l_Key = m_KeyMap.find(l_Name);
    return (l_Key != NULL) ? l_Key->Value.second : false;
}

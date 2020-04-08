#include "./Keyboard.h"
#include "Common/TaskPool/Utils/ThreadLock.h"

void CKeyboard::Execute(void)
{
    Update();
}

void CKeyboard::AddKey(const std::string &name, unsigned int key)
{
    m_KeyMap.Add(name, std::pair<unsigned int, bool>(key, false));
}

void CKeyboard::Update(void)
{
    KeyMapType::HashMapType &hashMap = m_KeyMap.GetHashMap();

    for(KeyMapType::HashMapType::iterator it = hashMap.begin(); it != hashMap.end(); it++)
    {
        it->Value.second = (GetAsyncKeyState(it->Value.first) & 0x8000) != 0;
    }
}

bool CKeyboard::isKeyPressed(const std::string &l_Name)
{
    KeyMapType::MapEntryType *key = m_KeyMap.find(l_Name);
    return (key != NULL) ? key->Value.second : false;
}

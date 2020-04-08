#pragma once

#include <string>
#include <Windows.h>

#include "Common/TaskPool/Task.h"
#include "Common/Utils/HashMap.h"
#include "Common/TaskPool/Utils/RWLock.h"

class CKeyboard : public CTask
{
    public:
        typedef HashMap<std::pair<int, bool>> KeyMapType;

    private:
        KeyMapType m_KeyMap;

    public:

        void Update         (void);
        void Execute        (void);

        void AddKey         (const std::string &, unsigned int);
        bool isKeyPressed   (const std::string &);
};

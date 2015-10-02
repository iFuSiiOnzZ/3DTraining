#pragma once
#include <Windows.h>
#include "./Mutex.h"

class CConditionVarible
{
    public:
        CConditionVarible  (void);
        ~CConditionVarible (void);

        void Sleep   (CMutex &l_Mutex);

        void Wake    (void);
        void WakeAll (void);

        CONDITION_VARIABLE m_ConditionVariable;
};

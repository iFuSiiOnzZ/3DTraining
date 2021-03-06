#pragma once
#ifndef AH_RWLOCK_
#define AH_RWLOCK_

#include "./Mutex.h"
#include "./ConditionVariable.h"

class CRWLock
{
    private:
        CMutex m_Mutex;
        CConditionVarible m_Writers;
        CConditionVarible m_Readers;

        int m_ActiveReaders;
        int m_ActiveWriters;
        int m_WritersWaiting;

    public:
        CRWLock  (void);
        ~CRWLock (void);

        void ReadLock    (void);
        void ReadUnLock  (void);

        void WriteLock   (void);
        void WriteUnLock (void);
};

#endif

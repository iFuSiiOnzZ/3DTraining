#pragma once

#include "./Mutex.h"
#include "./RWLock.h"

class CAutoLock
{
    private:
        CMutex *m_pLock;

    public:
        CAutoLock  (CMutex &l_Lock);
        ~CAutoLock (void);
};

class COptionalAutoLock
{
    private:
        CMutex *m_pLock;
        bool m_bAcquired;

    public:
        COptionalAutoLock  (CMutex &l_Lock, bool l_bAcquired);
        ~COptionalAutoLock (void);

        void Adquire (void);
        void Release (void);
};

class CRWReadAutoLock
{
    private:
        CRWLock *m_pLock;

    public:
        CRWReadAutoLock  (CRWLock &l_Lock);
        ~CRWReadAutoLock (void);
};

class CRWWriteAutoLock
{
    private:
        CRWLock *m_pLock;

    public:
        CRWWriteAutoLock  (CRWLock &l_Lock);
        ~CRWWriteAutoLock (void);
};

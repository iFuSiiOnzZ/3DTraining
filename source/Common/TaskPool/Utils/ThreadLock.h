#pragma once

#include "./Mutex.h"
#include "./RWLock.h"

class CAutoLock
{
    private:
        CMutex *m_pLock;

    public:
        CAutoLock  (CMutex &lock);
        ~CAutoLock (void);
};

class COptionalAutoLock
{
    private:
        CMutex *m_pLock;
        bool m_bAcquired;

    public:
        COptionalAutoLock  (CMutex &lock, bool acquired);
        ~COptionalAutoLock (void);

        void Adquire (void);
        void Release (void);
};

class CRWReadAutoLock
{
    private:
        CRWLock *m_pLock;

    public:
        CRWReadAutoLock  (CRWLock &lock);
        ~CRWReadAutoLock (void);
};

class CRWWriteAutoLock
{
    private:
        CRWLock *m_pLock;

    public:
        CRWWriteAutoLock  (CRWLock &lock);
        ~CRWWriteAutoLock (void);
};

#include "./ThreadLock.h"

CAutoLock::CAutoLock(CMutex &lock) : m_pLock(&lock)
{
    m_pLock->Lock();
}

CAutoLock::~CAutoLock(void)
{
    m_pLock->UnLock();
}

COptionalAutoLock::COptionalAutoLock(CMutex &lock, bool acquired) : m_pLock(&lock), m_bAcquired(false)
{
    if(acquired) Adquire();
}

COptionalAutoLock::~COptionalAutoLock()
{
    Release();
}

void COptionalAutoLock::Adquire()
{
    if(!m_bAcquired)
    {
        m_pLock->Lock();
        m_bAcquired = true;
    }
}

void COptionalAutoLock::Release()
{
    if(m_bAcquired)
    {
        m_pLock->UnLock();
        m_bAcquired = false;
    }
}

CRWReadAutoLock::CRWReadAutoLock(CRWLock &lock) : m_pLock(&lock)
{
    m_pLock->ReadLock();
}

CRWReadAutoLock::~CRWReadAutoLock()
{
    m_pLock->ReadUnLock();
}

CRWWriteAutoLock::CRWWriteAutoLock(CRWLock &lock) : m_pLock(&lock)
{
    m_pLock->WriteLock();
}

CRWWriteAutoLock::~CRWWriteAutoLock()
{
    m_pLock->WriteUnLock();
}

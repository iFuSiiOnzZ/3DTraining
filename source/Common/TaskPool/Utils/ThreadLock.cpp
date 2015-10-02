#include "./ThreadLock.h"

CAutoLock::CAutoLock(CMutex &l_Lock) : m_pLock(&l_Lock)
{
    m_pLock->Lock();
}

CAutoLock::~CAutoLock(void)
{
    m_pLock->UnLock();
}

COptionalAutoLock::COptionalAutoLock(CMutex &l_Lock, bool l_bAcquired) : m_pLock(&l_Lock), m_bAcquired(false)
{
    if(l_bAcquired) Adquire();
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

CRWReadAutoLock::CRWReadAutoLock(CRWLock &l_Lock) : m_pLock(&l_Lock)
{
    m_pLock->ReadLock();
}

CRWReadAutoLock::~CRWReadAutoLock()
{
    m_pLock->ReadUnLock();
}

CRWWriteAutoLock::CRWWriteAutoLock(CRWLock &l_Lock) : m_pLock(&l_Lock)
{
    m_pLock->WriteLock();
}

CRWWriteAutoLock::~CRWWriteAutoLock()
{
    m_pLock->WriteUnLock();
}

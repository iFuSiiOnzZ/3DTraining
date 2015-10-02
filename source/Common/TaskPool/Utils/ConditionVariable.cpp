#include "./ConditionVariable.h"

CConditionVarible::CConditionVarible()
{
    InitializeConditionVariable(&m_ConditionVariable);
}

CConditionVarible::~CConditionVarible()
{
}

void CConditionVarible::Sleep(CMutex &l_Mutex)
{
    SleepConditionVariableCS(&m_ConditionVariable, &l_Mutex.m_CriticalSection, INFINITE);
}

void CConditionVarible::Wake(void)
{
    WakeConditionVariable(&m_ConditionVariable);
}

void CConditionVarible::WakeAll(void)
{
    WakeAllConditionVariable(&m_ConditionVariable);
}
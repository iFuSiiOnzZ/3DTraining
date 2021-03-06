#pragma once
#include <list>
#include <Windows.h>

#include "./Task.h"
#include "./Utils/Mutex.h"
#include "./Utils/ConditionVariable.h"

class CPool
{
    private:
        std::list<CTask *>  m_pTasks;
        HANDLE              *m_pThreadsHandle;

        unsigned int        m_NumOfTreads;
        bool                m_ThreadRun;

        CMutex              m_Mutex;
        CConditionVarible   m_CondVar;
        CConditionVarible   m_CondVarTaskFinished;

    public:
        CPool  (void);
        ~CPool (void);

        void                Init            (unsigned int numThreads = 0);
        void                AddTask         (CTask *task);

        void                ThreadStop      (void);
        void                WaitForWorkers  (void);

        DWORD                MainThread     (void);
        static DWORD WINAPI  ThreadStart    (void *param);
};

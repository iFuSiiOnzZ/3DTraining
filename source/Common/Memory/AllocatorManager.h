#pragma once

#include "./Allocator.h"
#include "./LinearAllocator.h"
#include "./FreeListAllocator.h"
#include "Common/Utils/Singleton.h"

class CAllocatorManager : public CSingleton<CAllocatorManager>
{
    private:
        void *m_pLinearAllocatorMem;
        void *m_pFreeListAllocatorMem;

    private:
        CAllocatorManager(const CAllocatorManager &);
        CAllocatorManager &operator=(const CAllocatorManager &);

    public:
        CAllocatorManager();
        ~CAllocatorManager();

        CLinearAllocator    *linearAllocator;
        CFreeListAllocator  *freeListAllocator;
};

#define ALLOCATOR_LINEAR    CAllocatorManager::GetSingletonPtr()->linearAllocator
#define ALLOCATOR_FREE_LIST CAllocatorManager::GetSingletonPtr()->freeListAllocator

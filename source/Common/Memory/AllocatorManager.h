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

    public:
        CAllocatorManager();
        ~CAllocatorManager();

        CLinearAllocator    *m_pLinearAllocator;
        CFreeListAllocator  *m_pFreeListAllocator;
};

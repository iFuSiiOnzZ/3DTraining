#pragma once
#include "Allocator.h"

class CLinearAllocator : public CAllocator
{
    private:
        void *m_CurrentAddress;

    public:
        CLinearAllocator(size_t size, void *memAddress);
        ~CLinearAllocator();

        void *Allocate(size_t size, size_t alignment);
        void  Deallocate(void *memAddress);
        void  Reset(void);
};

#pragma once
#include "Allocator.h"

class CStackAllocator : public CAllocator
{
    private:
        void *m_CurrentAddress;

        struct AllocHeader
        {
            size_t m_OffsetPos;
        };

    public:
        CStackAllocator(size_t size, void *memAddress);
        ~CStackAllocator();

        void *Allocate(size_t size, size_t alignment);
        void  Deallocate(void *memAddress);
};

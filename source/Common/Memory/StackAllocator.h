#pragma once
#include "Allocator.h"

class CStackAllocator : public CAllocator
{
    private:
        void *m_CurrentAddress;

        struct AllocHeader
        {
            unsigned int m_OffsetPos;
        };

    public:
        CStackAllocator(unsigned int l_Size, void *l_MemAddress);
        ~CStackAllocator();

        void *Allocate(unsigned int l_Size, unsigned int l_Alignment);
        void  Deallocate(void *l_MemAddress);
};

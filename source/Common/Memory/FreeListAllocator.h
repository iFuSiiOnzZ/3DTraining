#pragma once
#include "Allocator.h"

class CFreeListAllocator : public CAllocator
{
    private:
        struct AllocHeader
        {
            size_t m_Size;
            size_t m_Alignment;
        };

        struct FreeBlock
        {
            size_t m_Size;
            FreeBlock *m_Next;
        };

        struct FreeBlock *m_FreeBlocks;

    public:
        CFreeListAllocator(size_t size, void *memAddress);
        ~CFreeListAllocator();

        void *Allocate(size_t size, size_t alignment);
        void  Deallocate(void *memAddress);
};

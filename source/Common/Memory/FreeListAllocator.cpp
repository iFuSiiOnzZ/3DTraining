#include "FreeListAllocator.h"
#include <stdio.h>

CFreeListAllocator::CFreeListAllocator(size_t size, void *memAddress) : CAllocator(size, memAddress)
{
    m_FreeBlocks = (struct FreeBlock *) memAddress;

    m_FreeBlocks->m_Size = size;
    m_FreeBlocks->m_Next = 0;
}

CFreeListAllocator::~CFreeListAllocator()
{
    m_FreeBlocks = 0;
}

void *CFreeListAllocator::Allocate(size_t size, size_t alignment)
{
    size_t offset = 0, totalSize = 0;
    struct FreeBlock *prevBlock = 0, *freeBlock = m_FreeBlocks;

    while (freeBlock != 0)
    {
        offset = alignOffsetWithHeader(freeBlock, alignment, sizeof(struct AllocHeader));
        totalSize = size + offset;

        if(freeBlock->m_Size > totalSize) break;

        prevBlock = freeBlock;
        freeBlock = freeBlock->m_Next;
    }

    if (freeBlock == 0)
    {
        return 0;
    }

    if (freeBlock->m_Size - totalSize <= sizeof(struct FreeBlock))
    {
        totalSize = freeBlock->m_Size;

        if(prevBlock != 0) prevBlock->m_Next = freeBlock->m_Next;
        else m_FreeBlocks = freeBlock->m_Next;
    }
    else
    {
        struct FreeBlock *l_NextFreeBlock = (struct FreeBlock *) ((size_t) freeBlock + totalSize);
        l_NextFreeBlock->m_Size = freeBlock->m_Size - totalSize;
        l_NextFreeBlock->m_Next = freeBlock->m_Next;

        if(prevBlock != 0) prevBlock->m_Next = l_NextFreeBlock;
        else m_FreeBlocks = l_NextFreeBlock;
    }

    size_t newMemAddress = (size_t) freeBlock + offset;
    struct AllocHeader *allocHeader = (struct AllocHeader *) (newMemAddress - sizeof(struct AllocHeader));

    allocHeader->m_Size = size + offset;
    allocHeader->m_Alignment = offset;

    m_UsedMemory += size + offset;
    m_NumAllocations++;

    return (void *) (newMemAddress);
}

void CFreeListAllocator::Deallocate(void *memAddress)
{
    if(memAddress == 0) return;
    struct AllocHeader *allocHeader = (struct AllocHeader *) ((size_t) memAddress - sizeof(struct AllocHeader));

    size_t blockStart = (size_t) memAddress - allocHeader->m_Alignment;
    size_t blockEnd = blockStart + allocHeader->m_Size;

    struct FreeBlock *prevBlock = 0;
    struct FreeBlock *freeBlock = m_FreeBlocks;

    while(freeBlock != 0 && (size_t) freeBlock < blockEnd)
    {
        prevBlock = freeBlock;
        freeBlock = freeBlock->m_Next;
    }

    if(prevBlock == nullptr)
    {
        prevBlock = (FreeBlock*) blockStart;
        prevBlock->m_Size = allocHeader->m_Size;
        prevBlock->m_Next = m_FreeBlocks;

        m_FreeBlocks = prevBlock;
    }
    else if((size_t) prevBlock + prevBlock->m_Size == blockStart)
    {
        prevBlock->m_Size += allocHeader->m_Size;
    }
    else
    {
        FreeBlock* temp = (FreeBlock*) blockStart;
        temp->m_Size = allocHeader->m_Size;
        temp->m_Next = prevBlock->m_Next;
        prevBlock->m_Next = temp;

        prevBlock = temp;
    }

    if( prevBlock != NULL && (size_t) freeBlock == blockEnd)
    {
        prevBlock->m_Size += freeBlock->m_Size;
        prevBlock->m_Next = freeBlock->m_Next;
    }

    m_UsedMemory -= allocHeader->m_Size;
    m_NumAllocations--;
}

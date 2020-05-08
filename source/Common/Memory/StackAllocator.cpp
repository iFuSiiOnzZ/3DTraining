#include "StackAllocator.h"
#include <assert.h>

CStackAllocator::CStackAllocator(size_t size, void *memAddress) : CAllocator(size, memAddress)
{
    m_CurrentAddress = memAddress;
}

CStackAllocator::~CStackAllocator()
{
    m_CurrentAddress = 0;
}

void *CStackAllocator::Allocate(size_t size, size_t alignment)
{
    size_t offset = alignOffsetWithHeader(m_CurrentAddress, alignment, sizeof(struct AllocHeader));
    size_t totalSize = offset + size;

    if(m_UsedMemory + totalSize > m_Size) return 0;
    size_t newMemAddress = (size_t) m_CurrentAddress + offset;

    struct AllocHeader *allocHeader = (struct AllocHeader *) ((size_t) newMemAddress - sizeof(struct AllocHeader));
    allocHeader->m_OffsetPos = (size_t) m_CurrentAddress - (size_t) m_MemAddress;

    m_CurrentAddress = (void *) (newMemAddress + size);
    m_UsedMemory += totalSize;
    m_NumAllocations++;

    return (void *) newMemAddress;
}

void CStackAllocator::Deallocate(void* memAddress)
{
    struct AllocHeader *allocHeader = (struct AllocHeader *) ((size_t) memAddress - sizeof(struct AllocHeader));
    m_UsedMemory -= (size_t) m_CurrentAddress - ((size_t) m_MemAddress + allocHeader->m_OffsetPos);

    m_CurrentAddress = (void *) ((size_t) m_MemAddress + allocHeader->m_OffsetPos);
    m_NumAllocations--;
}

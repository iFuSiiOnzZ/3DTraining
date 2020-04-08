#include "LinearAllocator.h"

CLinearAllocator::CLinearAllocator(size_t size, void *memAddress) : CAllocator(size, memAddress)
{
    m_CurrentAddress = memAddress;
}

CLinearAllocator::~CLinearAllocator()
{
    m_CurrentAddress = 0;
}

void *CLinearAllocator::Allocate(size_t size, size_t alignment)
{
    size_t offset = alignOffset(m_CurrentAddress, alignment);
    size_t totalSize = offset + size;

    if(m_UsedMemory + totalSize > m_Size) return 0;
    size_t newMemAddress = (size_t) m_CurrentAddress + offset;

    m_CurrentAddress = (void *) (newMemAddress + size);
    m_UsedMemory += totalSize;
    m_NumAllocations++;

    return (void *) newMemAddress;
}

void CLinearAllocator::Deallocate(void *)
{
}

void CLinearAllocator::Reset(void)
{
    m_CurrentAddress = m_MemAddress;
    m_NumAllocations = 0;
    m_UsedMemory = 0;
}

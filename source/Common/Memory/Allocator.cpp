#include "Allocator.h"

CAllocator::CAllocator(size_t size, void *memAddress)
{
    m_Size = size;
    m_MemAddress = memAddress;

    m_UsedMemory = 0;
    m_NumAllocations = 0;
}

CAllocator::~CAllocator()
{
    m_Size = 0;
    m_MemAddress = nullptr;

    m_UsedMemory = 0;
    m_NumAllocations = 0;
}

size_t CAllocator::GetSize(void)
{
    return m_Size;
}

size_t CAllocator::GetUsedMemory(void)
{
    return m_UsedMemory;
}

size_t CAllocator::GetNumAllocations(void)
{
    return m_NumAllocations;
}

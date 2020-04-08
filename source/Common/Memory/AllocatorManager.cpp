#include "./AllocatorManager.h"

#define B   (size_t)1
#define KB  (size_t)1024 * B
#define MB  (size_t)1024 * KB
#define GB  (size_t)1024 * MB

#define LINEAR_SIZE (size_t)16 * MB
#define FREE_LIST_SIZE (size_t)2 * GB

CAllocatorManager::CAllocatorManager()
{
    m_pLinearAllocatorMem = (void *)malloc(LINEAR_SIZE + sizeof(CLinearAllocator));
    m_pFreeListAllocatorMem = (void *)malloc(FREE_LIST_SIZE + sizeof(CFreeListAllocator));

    linearAllocator = (CLinearAllocator*)m_pLinearAllocatorMem;
    freeListAllocator = (CFreeListAllocator*)m_pFreeListAllocatorMem;

    new (linearAllocator) CLinearAllocator(LINEAR_SIZE, (char *)m_pLinearAllocatorMem + sizeof(CLinearAllocator));
    new (freeListAllocator) CFreeListAllocator(FREE_LIST_SIZE, (char *)m_pLinearAllocatorMem + sizeof(CFreeListAllocator));
}

CAllocatorManager::~CAllocatorManager()
{
    free(m_pLinearAllocatorMem);
    free(m_pFreeListAllocatorMem);
}

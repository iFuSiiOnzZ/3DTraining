#pragma once
#include <new>
#include <cmath>

class CAllocator
{
    protected:
        size_t m_UsedMemory;
        size_t m_NumAllocations;

        size_t m_Size;
        void   *m_MemAddress;

    private:

    public:
        CAllocator(size_t size, void *memAddress);
        virtual ~CAllocator();

        virtual void *Allocate(size_t size, size_t aligment) = 0;
        virtual void  Deallocate(void *memAddress) = 0;

        size_t GetSize(void);
        size_t GetUsedMemory(void);
        size_t GetNumAllocations(void);

        template <class T, class... ArgsType> T *MakeNew(ArgsType... Args) { return new (Allocate(sizeof(T), __alignof(T))) T(Args...); }
        template <class T> void  MakeDelete(T *classPtr) { if(classPtr){classPtr->~T(); Deallocate(classPtr);} }

        template <class T> T *New(void) { return (T *) Allocate(sizeof(T), __alignof(T)); }
        void Delete(void *memAddress) { Deallocate(memAddress); }
};

inline size_t alignOffset(void *address, size_t alignment)
{
    size_t offset = alignment - ((size_t) address & (alignment - 1));
    return (offset == alignment) ? 0 : offset;
}

inline size_t alignOffsetWithHeader(void *address, size_t alignment, size_t headerSize)
{
    size_t offset = alignOffset(address, alignment);
    if(headerSize > offset) offset += alignment * (unsigned int) ceil((float) (headerSize - offset) / (float)alignment);

    return offset;
}

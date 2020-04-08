#include "./MemLeaks.h"

#define MEMORY_FILE_COUNT 1024
#define MEMORY_FILE_LENGTH 256

static char _vFile[MEMORY_FILE_COUNT][MEMORY_FILE_LENGTH] = { 0 };
static unsigned int _nFile = 0;

bool MemLeaks::MemoryBegin()
{
    _CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(194);

    return true;
}

bool MemLeaks::MemoryEnd()
{
    return true;
}

const char* MemLeaks::FileString(const char* sFile)
{
    char *pFile = 0;
    unsigned int iFile = 0;

    while (iFile < _nFile)
    {
        pFile = _vFile[iFile++];
        if(strcmp(pFile, sFile) == 0) break;
    }

    if (iFile == _nFile)
    {
        pFile = _vFile[_nFile++];
        strncpy_s(pFile, _countof(_vFile[_nFile]), sFile, MEMORY_FILE_LENGTH);

        if (_nFile == MEMORY_FILE_COUNT ) _nFile = 0;
    }

    return pFile;
}

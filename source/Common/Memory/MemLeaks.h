#pragma once

#include <stdlib.h>
#include <crtdbg.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, MemLeaks::FileString(__FILE__), __LINE__)

namespace  MemLeaks
{
    extern bool         MemoryEnd();
    extern bool         MemoryBegin();
    extern const char   *FileString(const char* sFile);
}

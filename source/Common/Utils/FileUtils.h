#pragma once

#include <string>

bool FileGetContent(const std::string &l_FilePath, std::string &l_OutFileContent)
{
    FILE *l_pFile = NULL;
    char l_pFileContent[256] = { 0 };

    if (fopen_s(&l_pFile, l_FilePath.c_str(), "rt") != 0)
    {
        return false;
    }

    while (fgets(l_pFileContent, 256, l_pFile))
    {
        l_OutFileContent.append(l_pFileContent);
    }

    fclose(l_pFile);
    return true;
}

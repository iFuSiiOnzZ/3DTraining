#pragma once

#include <string>

static bool FileGetContent(const std::string &filePath, std::string &outFileContent)
{
    FILE *fileHandler = NULL;
    char fileContent[256] = { 0 };

    if (fopen_s(&fileHandler, filePath.c_str(), "rt") != 0)
    {
        return false;
    }

    while (fgets(fileContent, 256, fileHandler))
    {
        outFileContent.append(fileContent);
    }

    fclose(fileHandler);
    return true;
}

static std::string BaseName(const std::string &path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

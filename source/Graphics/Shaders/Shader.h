#pragma once

#include <Windows.h>
#include <gl/glew.h>

#include <cstring>
#include <string>

class CShader
{
    private:
        unsigned int m_ShaderHandler;
        unsigned int m_ShaderType;

        std::string m_InfoLog;
        std::string m_FileName;

        bool mIsLoaded;

    public:
        CShader  (void);
        ~CShader (void);

        unsigned int     GetShaderHandler       (void);
        unsigned int     GetShaderType          (void); 

        bool             LoadShader             (char *shaderPath, unsigned int shaderType);

        std::string      GetError               (void);
        bool             isLoaded               (void);
};


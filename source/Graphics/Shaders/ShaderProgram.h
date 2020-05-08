#pragma once

#include <Windows.h>
#include <gl/glew.h>

#include <cstring>
#include <string>

#include <vector>
#include <string>

#include "./Shader.h"

class CShaderProgram
{
    private:
        std::string  m_InfoLog;
        unsigned int m_ProgramHandler;

        std::vector<CShader *> m_pVertexShader;
        std::vector<CShader *> m_pFragmentShader;

    public:
        CShaderProgram  (void);
        ~CShaderProgram (void);

        std::string getError             (void);
        bool        Link                 (void);
        void        Release              (void);

        CShader     *getVertexShader     (unsigned int i);
        CShader     *getFragmentShader   (unsigned int i);

        CShader     *NewVertexShader     (void);
        CShader     *NewGeometryShader   (void);
        CShader     *NewFragmentShader   (void);

        int         getLocation         (const std::string &uName);

        void        ActiveProgram       (void);
        void        ReleaseProgram       (void);

        void        setUniformValue     (const std::string &uName, float uValue);
        void        setUniformValue     (const std::string &uName, int uValue);

        void        setUniformVector4f  (const std::string &uName, const float *uValue);
        void        setUniformVector3f  (const std::string &uName, const float *uValue);
        void        setUniformVector3f  (const std::string &uName, float x, float y, float z);
        void        setUniformMatrix4   (const std::string &uName, bool transpose, const float *uValue);
};

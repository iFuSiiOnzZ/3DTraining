#include "./ShaderProgram.h"
#include "Common/Memory/AllocatorManager.h"

CShaderProgram::CShaderProgram(void)
{
    m_ProgramHandler = glCreateProgram();
}

CShaderProgram::~CShaderProgram(void)
{

}

void CShaderProgram::Release()
{
    for (unsigned int i = 0; i < m_pVertexShader.size(); i++)
    {
        glDetachShader(m_ProgramHandler, m_pVertexShader[i]->GetShaderHandler());
        m_pVertexShader[i]->ReleaseShader();

        CAllocatorManager::GetSingletonPtr()->freeListAllocator->MakeDelete(m_pVertexShader[i]);
    }

    for (unsigned int i = 0; i < m_pFragmentShader.size(); i++)
    {
        glDetachShader(m_ProgramHandler, m_pFragmentShader[i]->GetShaderHandler());
        m_pFragmentShader[i]->ReleaseShader();

        CAllocatorManager::GetSingletonPtr()->freeListAllocator->MakeDelete(m_pFragmentShader[i]);
    }

    m_InfoLog.clear();
    glDeleteProgram(m_ProgramHandler);
}

bool CShaderProgram::Link(void)
{
    int status = 0;
    glLinkProgram(m_ProgramHandler);
    glGetProgramiv(m_ProgramHandler, GL_LINK_STATUS, &status);

    if(status == GL_FALSE)
    {
        m_InfoLog.clear();
        int iLength = 0, cWritten = 0;
        glGetProgramiv(m_ProgramHandler, GL_INFO_LOG_LENGTH, &iLength);

        char *pError = (char *) malloc (iLength * sizeof(char) + 1);
        ZeroMemory(pError, iLength * sizeof(char) + 1);

        glGetProgramInfoLog(m_ProgramHandler, iLength, &cWritten, pError);
        m_InfoLog.assign(pError);

        delete pError;
        return false;
    }

    return true;
}

std::string CShaderProgram::getError(void)
{
    return m_InfoLog;
}

CShader *CShaderProgram::NewVertexShader(void)
{
    CShader *vertexShader = CAllocatorManager::GetSingletonPtr()->freeListAllocator->MakeNew<CShader>();
    if (vertexShader == NULL) return NULL;

    if (!vertexShader->CreateShader(GL_VERTEX_SHADER)) return false;
    glAttachShader(m_ProgramHandler, vertexShader->GetShaderHandler());

    m_pVertexShader.push_back(vertexShader);
    return vertexShader;
}

CShader *CShaderProgram::NewGeometryShader(void)
{
    CShader *geometryShader = CAllocatorManager::GetSingletonPtr()->freeListAllocator->MakeNew<CShader>();
    if (geometryShader == NULL) return NULL;

    if (!geometryShader->CreateShader(GL_GEOMETRY_SHADER)) return false;
    glAttachShader(m_ProgramHandler, geometryShader->GetShaderHandler());

    m_pVertexShader.push_back(geometryShader);
    return geometryShader;
}

CShader *CShaderProgram::NewFragmentShader(void)
{
    CShader *fragmentShader = CAllocatorManager::GetSingletonPtr()->freeListAllocator->MakeNew<CShader>();
    if (fragmentShader == NULL) return NULL;

    if (!fragmentShader->CreateShader(GL_FRAGMENT_SHADER)) return false;
    glAttachShader(m_ProgramHandler, fragmentShader->GetShaderHandler());

    m_pFragmentShader.push_back(fragmentShader);
    return fragmentShader;
}

CShader *CShaderProgram::getVertexShader(unsigned int i)
{
    return (i < m_pVertexShader.size()) ? m_pVertexShader[i] : NULL;
}

CShader *CShaderProgram::getFragmentShader(unsigned int i)
{
    return (i < m_pFragmentShader.size()) ? m_pFragmentShader[i] : NULL;
}

void CShaderProgram::ActiveProgram(void)
{
    glUseProgram(m_ProgramHandler);
}

void CShaderProgram::ReleaseProgram(void)
{
    glUseProgram(0);
}

void CShaderProgram::setUniformValue(const std::string &uName, float uValue)
{
    int uLocation = glGetUniformLocation(m_ProgramHandler, uName.c_str());
    glUniform1f(uLocation, uValue);
}

void CShaderProgram::setUniformValue(const std::string &uName, int uValue)
{
    int uLocation = glGetUniformLocation(m_ProgramHandler, uName.c_str());
    glUniform1i(uLocation, uValue);
}

void CShaderProgram::setUniformVector4f(const std::string &uName, const float *uValue)
{
    int uLocation = glGetUniformLocation(m_ProgramHandler, uName.c_str());
    glUniform4fv(uLocation, 1, uValue);
}

void CShaderProgram::setUniformVector3f(const std::string &uName, const float *uValue)
{
    int uLocation = glGetUniformLocation(m_ProgramHandler, uName.c_str());
    glUniform3fv(uLocation, 1, uValue);
}

void CShaderProgram::setUniformVector3f(const std::string &uName, float x, float y, float z)
{
    int uLocation = glGetUniformLocation(m_ProgramHandler, uName.c_str());
    glUniform3f(uLocation, x, y, z);
}

void CShaderProgram::setUniformMatrix4(const std::string &uName, bool transpose, const float *uValue)
{
    int uLocation = glGetUniformLocation(m_ProgramHandler, uName.c_str());
    glUniformMatrix4fv(uLocation, 1, transpose, uValue);
}

int CShaderProgram::getLocation(const std::string &uName)
{
    return glGetUniformLocation(m_ProgramHandler, uName.c_str());
}

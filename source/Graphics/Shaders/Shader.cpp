#include "./Shader.h"
#include "Common/Utils/FileUtils.h"


static const char *shaderTypeToString(unsigned int shaderType)
{
    switch (shaderType)
    {
        case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
        case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
        case GL_GEOMETRY_SHADER: return "GL_GEOMETRY_SHADER";
        default: return "Unkonw shader type";
    }
}

CShader::CShader(void)
    : m_ShaderHandler(0)
    , m_ShaderType(0)
    , mIsLoaded(false)
{
}

CShader::~CShader(void)
{
}

void CShader::ReleaseShader(void)
{
    glDeleteShader(m_ShaderHandler);
    m_ShaderHandler = 0;
}

bool CShader::CreateShader(unsigned int shaderType)
{
    m_ShaderHandler = glCreateShader(shaderType);
    m_ShaderType = shaderType;

    return m_ShaderHandler != 0;
}

bool CShader::CompileShader(const std::string &shaderPath)
{
    m_FileName.assign(shaderPath);
    std::string sContent = "";

    if (!FileGetContent(m_FileName, sContent))
    {
        m_InfoLog.assign("Error opening file: " + shaderPath);
        return false;
    }

    int lengths[] = { (int) sContent.length() };
    const char *c_str = sContent.c_str();

    glShaderSource(m_ShaderHandler, 1, &c_str, lengths);
    glCompileShader(m_ShaderHandler);

    int status = 0;
    glGetShaderiv(m_ShaderHandler, GL_COMPILE_STATUS, &status);

    if(status == GL_FALSE)
    {
        int iLength = 0, cWritten = 0;
        glGetShaderiv(m_ShaderHandler, GL_INFO_LOG_LENGTH, &iLength);

        char *sError = (char *) malloc (iLength * sizeof(char) + 1);
        ZeroMemory(sError, iLength * sizeof(char) + 1);

        glGetShaderInfoLog(m_ShaderHandler, iLength, &cWritten, sError);
        m_InfoLog.assign(sError);

        free(sError);
        return false;
    }

    return true;
}

unsigned int CShader::GetShaderHandler(void)
{
    return m_ShaderHandler;
}

unsigned int CShader::GetShaderType(void)
{
    return m_ShaderHandler;
}

std::string CShader::GetError(void)
{
    std::string shaderType(shaderTypeToString(m_ShaderType));
    shaderType += ": " + m_FileName + "\n";

    return shaderType + m_InfoLog;
}

bool CShader::isLoaded(void)
{
    return mIsLoaded;
}

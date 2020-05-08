#include "./Texture.h"

CTexture::CTexture(void) : m_Name("unnamed"), m_TextureUnit(0), m_TextureId(0)
{
    m_MinFilter = m_MagFilter = GL_NEAREST;
    m_WrapS = m_WrapT = GL_CLAMP_TO_EDGE;

    glGenTextures(1, &m_TextureId);
}

CTexture::~CTexture()
{
    glDeleteTextures(1, &m_TextureId);
}

CTexture &CTexture::SetUnit(unsigned int rextureUnit)
{
    m_TextureUnit = rextureUnit;
    return *this;
}

CTexture &CTexture::SetRepeate(bool repeat)
{
    if (repeat) m_WrapS = m_WrapT = GL_REPEAT;
    else m_WrapS = m_WrapT = GL_CLAMP_TO_EDGE;

    return *this;
}

CTexture &CTexture::SetSmooth(bool smoth)
{
    if (smoth) m_MinFilter = m_MagFilter = GL_LINEAR;
    else m_MinFilter = m_MagFilter = GL_NEAREST;

    return *this;
}

CTexture &CTexture::SetTexture(unsigned char *data, unsigned int width, unsigned int height, unsigned int numBytesColor)
{
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    unsigned int byteFormat = (numBytesColor == 4) ? GL_RGBA : (numBytesColor == 3) ? GL_RGB : GL_LUMINANCE;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrapT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_MinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_MagFilter);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, byteFormat, width, height, 0, byteFormat, GL_UNSIGNED_BYTE, data);

    return *this;
}

void CTexture::Use(void)
{
    glActiveTexture(GL_TEXTURE0 + m_TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void CTexture::UnUse(void)
{
    glActiveTexture(GL_TEXTURE0 + m_TextureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

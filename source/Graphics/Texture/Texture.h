#pragma once

#include <Windows.h>
#include <gl/glew.h>

#include <cstring>
#include <string>

class CTexture
{
    private:
        unsigned int m_TextureUnit;
        unsigned int m_TextureId;

        int m_MinFilter;
        int m_MagFilter;

        int m_WrapS;
        int m_WrapT;

    public:
        CTexture(void);
        ~CTexture(void);

        CTexture &SetTexture(unsigned char *data, unsigned int width, unsigned int height, unsigned int numBytesColor);
        CTexture &SetUnit(unsigned int rextureUnit);

        CTexture &SetRepeate(bool repeat);
        CTexture &SetSmooth(bool smoth);

        inline unsigned int GetTextureUnit() { return m_TextureUnit; }
        inline unsigned int GetTextureId() { return m_TextureId; }

        void UnUse(void);
        void Use(void);
};

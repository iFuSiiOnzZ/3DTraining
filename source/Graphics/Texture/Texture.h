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
        
        bool SetTexture(char *l_pData, unsigned int l_iWidth, unsigned int l_iHeight, unsigned int l_iNumBytesColor);
        void SetUnit(unsigned int l_iTextureUnit);

        void SetRepeate(bool l_bRepeat);
        void SetSmooth(bool l_bSmoth);

        void UnUse(void);
        void Use(void);
};


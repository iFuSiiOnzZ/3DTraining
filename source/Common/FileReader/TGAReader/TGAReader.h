#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct TGAImageData
{
    unsigned    int     mBitsXPixel;
    unsigned    int     mBytesXPixel;
    unsigned    char    mTGAHeader[6];

    unsigned    int     mImageSize;
    unsigned    int     mImgHeight;
    unsigned    int     mImgWidth;
} TGAImageData;

class CTGAReader
{
    private:
        unsigned char m_Header[12];

        void LoadUncompressedTGA    (std::FILE *pFile);
        void LoadCompressedTGA      (std::FILE *pFile);

    public:
        unsigned char *m_pPixels;
        TGAImageData   m_ImgInfo;

        CTGAReader   (const char *fPath);
        ~CTGAReader  (void);
};

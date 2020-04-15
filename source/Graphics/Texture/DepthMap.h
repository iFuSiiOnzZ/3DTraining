#pragma once

#include <Windows.h>
#include <gl/glew.h>

#include <cstring>
#include <string>

class CDirectionalDepthMap
{
    private:
        unsigned int depthMapFBO;
        unsigned int depthMap;

    public:
        CDirectionalDepthMap();
        ~CDirectionalDepthMap(void);

        void useTexture(int textureUnit);
        bool Create(int x, int y);

        void Unbind(void);
        void Bind(void);

        inline bool isValid()
        {
            return depthMapFBO != 0;
        }
};

class CPointDepthMap
{
private:
    unsigned int depthMapFBO;
    unsigned int depthCubeMap;

public:
    CPointDepthMap();
    ~CPointDepthMap(void);

    void useTexture(int textureUnit);
    bool Create(int x, int y);

    void Unbind(void);
    void Bind();

    inline bool isValid()
    {
        return depthMapFBO != 0;
    }
};

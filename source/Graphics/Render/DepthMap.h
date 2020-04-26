#pragma once

#include <Windows.h>
#include <gl/glew.h>

#include <cstring>
#include <string>

class CDepthMap
{
    private:
        unsigned int depthMapFBO;
        unsigned int depthMap;
        int w, h;

    public:
        CDepthMap();
        ~CDepthMap(void);

        void useTexture(int textureUnit);
        bool Create(int x, int y);

        void Unbind(void) const;
        void Bind(void) const;

        inline int width() const { return w; }
        inline int height() const { return h; }
        inline bool isValid() const { return depthMapFBO != 0; }
};

class CPointDepthMap
{
private:
    unsigned int depthCubeMap;
    unsigned int depthMapFBO;
    int h, w;

public:
    CPointDepthMap();
    ~CPointDepthMap(void);

    void useTexture(int textureUnit);
    bool Create(int x, int y);

    void Unbind(void) const;
    void Bind() const;

    inline int width() const { return w; }
    inline int height() const { return h; }
    inline bool isValid() const { return depthMapFBO != 0; }
};

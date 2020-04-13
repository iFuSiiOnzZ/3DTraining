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

    public:
        CDepthMap();
        ~CDepthMap(void);

        void useTexture(int textureUnit);
        bool GenerateDepth(int x, int y);
        inline bool isValid() { return depthMapFBO != 0; }

        void UnUse(void);
        void Use(void);
};

#include "DepthMap.h"

CDepthMap::CDepthMap()
{
    w = h = 0;
    depthMap = depthMapFBO = 0;
}

CDepthMap::~CDepthMap(void)
{
    w = h = 0;
    if (depthMap) glDeleteTextures(1, &depthMap);
    if (depthMapFBO) glDeleteFramebuffers(1, &depthMapFBO);
}

void CDepthMap::useTexture(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, depthMap);
}

bool CDepthMap::Create(int x, int y)
{
    glGenTextures(1, &depthMap);
    glGenFramebuffers(1, &depthMapFBO);

    glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, x, y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            glDeleteTextures(1, &depthMap);
            depthMap = 0;

            glDeleteFramebuffers(1, &depthMapFBO);
            depthMapFBO = 0;

            *((int *)0) = 0;
            return false;
        }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    w = x, h = y;
    return true;
}

void CDepthMap::Bind(void) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glViewport(0, 0, w, h);

    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
}

void CDepthMap::Unbind(void) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_CULL_FACE);
}

///////////////////////////////////////////////////////////////////////////////

CPointDepthMap::CPointDepthMap()
{
    w = h = 0;
    depthCubeMap = depthMapFBO = 0;
}

CPointDepthMap::~CPointDepthMap(void)
{
    w = h = 0;
    if (depthCubeMap) glDeleteTextures(1, &depthCubeMap);
    if (depthMapFBO) glDeleteFramebuffers(1, &depthMapFBO);
}

void CPointDepthMap::useTexture(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
}

bool CPointDepthMap::Create(int x, int y)
{
    glGenTextures(1, &depthCubeMap);
    glGenFramebuffers(1, &depthMapFBO);

    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        for (int i = 0; i < 6; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, x, y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        }
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubeMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            glDeleteTextures(1, &depthCubeMap);
            depthCubeMap = 0;

            glDeleteFramebuffers(1, &depthMapFBO);
            depthMapFBO = 0;

            *((int *)0) = 0;
            return false;
        }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    w = x, h = y;
    return true;
}

void CPointDepthMap::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, w, h);
}

void CPointDepthMap::Unbind(void) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

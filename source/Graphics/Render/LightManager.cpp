#include "LightManager.h"

#include "DebugRender.h"

S_LIGHT *CLightManger::addSpotLight(bool genShadowMap)
{
    m_SpotLigts.emplace_back(S_LIGHT());
    S_LIGHT *l = &m_SpotLigts.back();

    l->constant = l->linear = l->exp = 0.0f;
    l->angle = l->fallOff = 0.0f;

    if (genShadowMap)
    {
        l->pointDepthMap.Create(1024, 1024);
        ++m_SpotLightShadows;
    }

    return l;
}

S_LIGHT *CLightManger::addPointLight(bool genShadowMap)
{
    m_PointLigts.emplace_back(S_LIGHT());
    S_LIGHT *l = &m_PointLigts.back();

    l->constant = 1.0f;
    l->linear = 0.0f;
    l->exp = 0.1f;

    l->fallOff = 0.0f;
    l->angle = 0.0f;

    if (genShadowMap)
    {
        l->pointDepthMap.Create(1024, 1024);
        ++m_PointLightShadows;
    }

    return l;
}

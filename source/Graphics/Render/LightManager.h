#pragma once

#include "Common/Math/Vector/Vector.h"
#include "RenderableVertex.h"
#include "DepthMap.h"

#include <vector>

enum class LIGHT_TYPE : unsigned int
{
    Omnidirectiona,
    Directional,
    Spot
};

struct S_LIGHT
{
    bool enableShadow;
    bool isDynamic;

    // Attenuation factors
    float constant, linear, exp;

    // Sport light angles
    float angle, fallOff;

    // Position/direction
    CVector3f position;

    // Colors
    CVector3f ambient;
    CVector3f diffuse;
    CVector3f specular;

    // Depth info
    CDepthMap directionalDepthMap;
    CPointDepthMap pointDepthMap;
};

class CLightManger
{
    private:
        std::vector<S_LIGHT> m_PointLigts;
        std::vector<S_LIGHT> m_SpotLigts;
        S_LIGHT m_DirectionalLight;

        size_t m_PointLightShadows;
        size_t m_SpotLightShadows;

    public:
        inline S_LIGHT *getDirectionalLight() { return &m_DirectionalLight; }

        inline size_t getNumberOfPointLigts() { return m_PointLigts.size(); }
        inline size_t getNumberOfSpotLigts() { return m_SpotLigts.size(); }

        inline size_t getNumOfShadowsPointLight() { return m_PointLightShadows; }
        inline size_t getNumOfShadowsSpotLight() { return m_SpotLightShadows; }

        inline S_LIGHT *getPointLight(size_t idx) { return &m_PointLigts[idx]; }
        inline S_LIGHT *getSpotLight(size_t idx) { return &m_SpotLigts[idx]; }

        S_LIGHT *addSpotLight(bool genShadowMap = false);
        S_LIGHT *addPointLight(bool genShadowMap = false);
};

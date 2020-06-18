#pragma once

#include "Core/Process.h"
#include "RenderableObject.h"

#include "Common/Timer/Timer.h"
#include "Common/Math/Constants.h"
#include "Common/Math/Matrix/Matrix.h"
#include "Common/Math/Vector/Vector.h"

#include "Graphics/Render/Texture.h"
#include "Graphics/Render/DepthMap.h"
#include "Graphics/Render/LightManager.h"

#include "Graphics/Cameras/FPSCamera.h"

#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Shaders/Shader.h"

class CGraphicsManager;

class CObject3D;
class CTexture;
class CCamera;

typedef struct ssao_t
{
    CDepthMap ssaoDept;
    CShaderProgram shaderProg;
} ssao_t;

class CGameProcess : public CProcess
{
    private:
        CFPSCamera m_Camera;
        CTimer m_Timer;

        COrthographicProjectionf m_OrthProj;
        CPerspectiveProjectionf m_PersProj;

        CShaderProgram m_DebugQuad;
        CShaderProgram m_ShaderProgram;

        CShaderProgram m_PointLightDeptProgramShader;
        CShaderProgram m_DirectionalDepthProgramShader;

        ssao_t m_SSAO;
        CLightManger m_LightManager;
        std::vector<CRenderableObject> *m_RenderableObject;

    private:
        CMatrix4f GenerateDirectionalLightShadowMap(const S_LIGHT *light);
        void GeneratePointLightShadowMap(const S_LIGHT *light);
        void GenerateSSAODepthMap(CDepthMap &map);

    public:
        CGameProcess(CGraphicsManager *graphicsManager);
        ~CGameProcess(void) {}

        void Update (const S_PLATFORM *platform) override;
        void Render (const S_PLATFORM *platform) override;

        void Init    (const S_PLATFORM *platform);
        void Release (const S_PLATFORM *platform);
};

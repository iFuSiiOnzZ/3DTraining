#include <gl/glew.h>
#include <Windows.h>

#include "./GameProcess.h"

#include "Common/Math/Constants.h"
#include "Graphics/Render/DebugRender.h"

#include "Common/Utils/ResourceManager.h"
#include "Common/Memory/AllocatorManager.h"

///////////////////////////////////////////////////////////////////////////////

static CVector3f gDirLightPos(5.0f, 20.0f, 2.0f);
static CMatrix4f dirLightSpaceMatrix;

///////////////////////////////////////////////////////////////////////////////

CGameProcess::CGameProcess(CGraphicsManager *graphicsManager)
    : CProcess(graphicsManager)
    , m_Camera(60.0f, 0.01f, 100.0f)
    , m_Timer(60)
{
    m_RenderableObject = nullptr;
    CResourceManager::GetSingletonPtr()->Register<CTexture>();
}

void CGameProcess::Release(const S_PLATFORM *)
{
    m_DebugQuad.ReleaseProgram();
    m_DebugQuad.Release();

    m_PointLightDeptProgramShader.ReleaseProgram();
    m_PointLightDeptProgramShader.Release();

    m_ShaderProgram.ReleaseProgram();
    m_ShaderProgram.Release();

    m_DirectionalDepthProgramShader.ReleaseProgram();
    m_DirectionalDepthProgramShader.Release();

    m_SSAO.shaderProg.ReleaseProgram();
    m_SSAO.shaderProg.Release();

    CRenderableObject::free(m_RenderableObject);
    CResourceManager::TBranch *br = CResourceManager::GetSingletonPtr()->GetByType<CTexture>();

    for (auto &tex : *br)
    {
        ALLOCATOR_FREE_LIST->MakeDelete<CTexture>((CTexture*)tex.second);
    }

    CResourceManager::GetSingletonPtr()->Clear<CTexture>();
}

void CGameProcess::Init(const S_PLATFORM *platform)
{
    unsigned int screenWidth = 0, screenHeight = 0;
    m_pGraphicsManager->GetWindowSize(screenWidth, screenHeight);

    CShader *shader = m_ShaderProgram.NewVertexShader();
    if (!shader->CompileShader("./shaders/simple.vert")) OutputDebugStringA(shader->GetError().c_str());

    shader = m_ShaderProgram.NewFragmentShader();
    if (!shader->CompileShader("./shaders/simple.frag")) OutputDebugStringA(shader->GetError().c_str());

    if (!m_ShaderProgram.Link())
    {
        OutputDebugStringA(m_ShaderProgram.getError().c_str());
    }

    shader = m_DirectionalDepthProgramShader.NewVertexShader();
    if (!shader->CompileShader("./shaders/directionalLightDepthShader.vert")) OutputDebugStringA(shader->GetError().c_str());

    shader = m_DirectionalDepthProgramShader.NewFragmentShader();
    if (!shader->CompileShader("./shaders/directionalLightDepthShader.frag")) OutputDebugStringA(shader->GetError().c_str());

    if (!m_DirectionalDepthProgramShader.Link())
    {
        OutputDebugStringA(m_DirectionalDepthProgramShader.getError().c_str());
    }

    shader = m_DebugQuad.NewVertexShader();
    if (!shader->CompileShader("./shaders/debugQuad.vert")) OutputDebugStringA(shader->GetError().c_str());

    shader = m_DebugQuad.NewFragmentShader();
    if (!shader->CompileShader("./shaders/debugQuad.frag")) OutputDebugStringA(shader->GetError().c_str());

    if (!m_DebugQuad.Link())
    {
        OutputDebugStringA(m_DebugQuad.getError().c_str());
    }

    shader = m_PointLightDeptProgramShader.NewVertexShader();
    if (!shader->CompileShader("./shaders/pointLightDepthShader.vert")) OutputDebugStringA(shader->GetError().c_str());

    shader = m_PointLightDeptProgramShader.NewFragmentShader();
    if (!shader->CompileShader("./shaders/pointLightDepthShader.frag")) OutputDebugStringA(shader->GetError().c_str());

    shader = m_PointLightDeptProgramShader.NewGeometryShader();
    if (!shader->CompileShader("./shaders/pointLightDepthShader.geom")) OutputDebugStringA(shader->GetError().c_str());

    if (!m_PointLightDeptProgramShader.Link())
    {
        OutputDebugStringA(m_PointLightDeptProgramShader.getError().c_str());
    }

    shader = m_SSAO.shaderProg.NewVertexShader();
    if (!shader->CompileShader("./shaders/cameraDepthShader.vert")) OutputDebugStringA(shader->GetError().c_str());

    shader = m_SSAO.shaderProg.NewFragmentShader();
    if (!shader->CompileShader("./shaders/cameraDepthShader.frag")) OutputDebugStringA(shader->GetError().c_str());

    if (!m_SSAO.shaderProg.Link())
    {
        OutputDebugStringA(m_SSAO.shaderProg.getError().c_str());
    }

    ///////////////////////////////////////////////////////////////////////////

    m_Camera.SetPosition(CVector3f(0.0f, 5.0f, 0.0f));
    m_Camera.SetLookAt(m_Camera.GetPosition() + CVector3f(1.0, 0.0f, 0.0f));
    m_PersProj.set(m_Camera.GetFov(), 16.0f / 9.0f, m_Camera.GetZNear(), m_Camera.GetZFar());

    m_RenderableObject = CRenderableObject::loadObject("./models/sponza/sponza.obj");

    ///////////////////////////////////////////////////////////////////////////
    // centro abajo
    S_LIGHT *light = m_LightManager.addPointLight();
    light->position = CVector3f(4.888748f, 1.407070f, 1.400000f);
    light->ambient  = CVector3f(0.5f, 0.5f, 0.5f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(4.888748f, 1.407070f, -2.200000f);
    light->ambient  = CVector3f(0.5f, 0.5f, 0.5f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(-6.180983f, 1.406304f, 1.400000f);
    light->ambient  = CVector3f(0.5f, 0.5f, 0.5f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(-6.180983f, 1.406304f, -2.200000f);
    light->ambient  = CVector3f(0.5f, 0.5f, 0.5f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    ///////////////////////////////////////////////////////////////////////////
    // esqienas pasillo planta 0
    light = m_LightManager.addPointLight();
    light->position = CVector3f(-12.000000f, 1.500000f, 3.997805f);
    light->ambient  = CVector3f(0.5f, 0.5f, 0.5f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(-12.000000f, 1.500000f, -4.674432f);
    light->ambient  = CVector3f(0.5f, 0.5f, 0.5f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(11.000000f, 1.500000f, -4.528717f);
    light->ambient  = CVector3f(0.5f, 0.5f, 0.5f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(11.000000f, 1.500000f, 4.136447f);
    light->ambient  = CVector3f(0.5f, 0.5f, 0.5f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    ///////////////////////////////////////////////////////////////////////////
    // Planta 1 donde no da la luz

    light = m_LightManager.addPointLight();
    light->position = CVector3f(12.000000f, 6.500000f, 4.136447f);
    light->ambient  = CVector3f(0.0f, 0.0f, 0.0f);
    light->diffuse  = CVector3f(0.1f, 0.1f, 0.1f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(5.000000f, 6.500000f, 4.136447f);
    light->ambient  = CVector3f(0.0f, 0.0f, 0.0f);
    light->diffuse  = CVector3f(0.1f, 0.1f, 0.1f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(0.000000f, 6.500000f, 4.136447f);
    light->ambient  = CVector3f(0.0f, 0.0f, 0.0f);
    light->diffuse  = CVector3f(0.1f, 0.1f, 0.1f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(-5.000000f, 6.500000f, 4.136447f);
    light->ambient  = CVector3f(0.0f, 0.0f, 0.0f);
    light->diffuse  = CVector3f(0.1f, 0.1f, 0.1f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(-12.000000f, 6.500000f, 4.136447f);
    light->ambient  = CVector3f(0.0f, 0.0f, 0.0f);
    light->diffuse  = CVector3f(0.1f, 0.1f, 0.1f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    ///////////////////////////////////////////////////////////////////////////
    // Planta 1 donde da la luz
    light = m_LightManager.addPointLight();
    light->position = CVector3f(12.000000f, 6.500000f, -4.528717f);
    light->ambient  = CVector3f(0.0f, 0.0f, 0.0f);
    light->diffuse  = CVector3f(0.1f, 0.1f, 0.1f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(5.000000f, 6.500000f, -4.528717f);
    light->ambient  = CVector3f(0.8f, 0.8f, 0.8f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(0.000000f, 6.500000f, -4.528717f);
    light->ambient  = CVector3f(0.8f, 0.8f, 0.8f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(-5.000000f, 6.500000f, -4.528717f);
    light->ambient  = CVector3f(0.8f, 0.8f, 0.8f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    light = m_LightManager.addPointLight();
    light->position = CVector3f(-12.000000f, 6.500000f, -4.528717f);
    light->ambient  = CVector3f(0.8f, 0.8f, 0.8f);
    light->diffuse  = CVector3f(1.0f, 1.0f, 1.0f);
    light->specular = CVector3f(1.0f, 1.0f, 1.0f);

    ///////////////////////////////////////////////////////////////////////////

    light = m_LightManager.getDirectionalLight();
    light->position = CVector3f(5.0f, 20.0f, 2.0f);
    light->ambient  = CVector3f(0.6f, 0.6f , 0.6f);
    light->diffuse  = CVector3f(1.0f, 1.0f , 1.0f);
    light->specular = CVector3f(1.0f, 1.0f , 1.0f);

    light->directionalDepthMap.Create(1024 * 4, 1024 * 4);
    dirLightSpaceMatrix = GenerateDirectionalLightShadowMap(light);

    m_SSAO.ssaoDept.Create(platform->data.screenSize.x, platform->data.screenSize.y);
}

void CGameProcess::Update(const S_PLATFORM *platform)
{
    m_Timer.Update();
    m_Camera.Update(platform, &m_Timer);

    if (platform->data.input->Mouse.ButtonLeft.WasDown)
    {
        S_LIGHT *light = m_LightManager.addPointLight();
        light->position = m_Camera.GetPosition();

        light->ambient = CVector3f(0.5f, 0.5f, 0.5f);
        light->diffuse = CVector3f(1.0f, 1.0f, 1.0f);
        light->specular = CVector3f(1.0f, 1.0f, 1.0f);
    }

    if (platform->data.input->Keyboard.KeyState['P'].WasDown)
    {
        CDebugRender::TakeScreenShot("screenshot.jpg");
    }
}

void CGameProcess::Render(const S_PLATFORM *platform)
{
    //GenerateSSAODepthMap(m_SSAO.ssaoDept);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, platform->data.screenSize.x, platform->data.screenSize.y);

    m_ShaderProgram.ActiveProgram();
        CMatrix4f projViewMatrix = m_Camera.GetViewMatrix() * m_PersProj;
        m_ShaderProgram.setUniformMatrix4("projViewMatrix", false, projViewMatrix.m_pMatrix4);
        m_ShaderProgram.setUniformMatrix4("lightSpaceMatrix", false, dirLightSpaceMatrix.m_pMatrix4);

        m_ShaderProgram.setUniformValue("dirLightShadowMap", 5);
        m_LightManager.getDirectionalLight()->directionalDepthMap.useTexture(5);

        m_ShaderProgram.setUniformVector3f("directionalLight.ambient"  , m_LightManager.getDirectionalLight()->ambient.u );
        m_ShaderProgram.setUniformVector3f("directionalLight.diffuse"  , m_LightManager.getDirectionalLight()->diffuse.u );
        m_ShaderProgram.setUniformVector3f("directionalLight.specular" , m_LightManager.getDirectionalLight()->specular.u);
        m_ShaderProgram.setUniformVector3f("directionalLight.direction", m_LightManager.getDirectionalLight()->position.u);

        size_t numOfPointLights = m_LightManager.getNumberOfPointLigts(), shdIdx = 0;
        m_ShaderProgram.setUniformValue("pointLight.counter", (int)numOfPointLights);

        for (size_t i = 0; i < numOfPointLights; ++i)
        {
            char s[256];
            S_LIGHT *light = m_LightManager.getPointLight(i);

            sprintf_s(s, "pointLight.lights[%d].position", (int)i);
            m_ShaderProgram.setUniformVector3f(s, light->position.u);

            sprintf_s(s, "pointLight.lights[%d].ambient", (int)i);
            m_ShaderProgram.setUniformVector3f(s, light->ambient.u);

            sprintf_s(s, "pointLight.lights[%d].diffuse", (int)i);
            m_ShaderProgram.setUniformVector3f(s, light->diffuse.u);

            sprintf_s(s, "pointLight.lights[%d].specular", (int)i);
            m_ShaderProgram.setUniformVector3f(s, light->specular.u);

            sprintf_s(s, "pointLight.lights[%d].constant", (int)i);
            m_ShaderProgram.setUniformValue(s, light->constant);

            sprintf_s(s, "pointLight.lights[%d].linear", (int)i);
            m_ShaderProgram.setUniformValue(s, light->linear);

            sprintf_s(s, "pointLight.lights[%d].exp", (int)i);
            m_ShaderProgram.setUniformValue(s, light->exp);

            if (light->pointDepthMap.isValid() && light->enableShadow)
            {
                sprintf_s(s, "pointLight.lights[%d].hasShadow", (int)shdIdx);
                m_ShaderProgram.setUniformValue(s, 1);

                sprintf_s(s, "pointLight.lights[%d].shadowMap", (int)shdIdx);
                m_ShaderProgram.setUniformValue(s, 6 + (int)shdIdx);

                light->pointDepthMap.useTexture(6 + (int)shdIdx);
                ++shdIdx;
            }
        }

        m_ShaderProgram.setUniformValue("zFar", m_Camera.GetZFar());
        m_ShaderProgram.setUniformVector3f("userViewPos", m_Camera.GetPosition().u);

        for (size_t i = 0; m_RenderableObject && i < m_RenderableObject->size(); ++i)
        {
            m_RenderableObject->at(i).bind(m_ShaderProgram);
                m_ShaderProgram.setUniformMatrix4("modelMatrix", true, m_RenderableObject->at(i).transform.m_pMatrix4);
                m_RenderableObject->at(i).render();
            m_RenderableObject->at(i).unbind(m_ShaderProgram);
        }

    m_ShaderProgram.ReleaseProgram();

#if 1
    glLoadMatrixf((m_Camera.GetViewMatrix() * m_PersProj).m_pMatrix4);
    CDebugRender::DrawCube(gDirLightPos, CVector3f(0.0f, 1.0f, 0.0f));

    for (size_t i = 0; i < m_LightManager.getNumberOfPointLigts(); ++i)
    {
        S_LIGHT *light = m_LightManager.getPointLight(i);
        CDebugRender::DrawCube(light->position);
    }

    CDebugRender::DrawGrid(10, 2, CVector3f(1.0f, 1.0f, 1.0f));
    CDebugRender::DrawAxis(CVector3f(), 2.0f);
#endif

    SwapBuffers(m_pGraphicsManager->GetDevice());

#if 1
    char windowTitle[256] = { 0 };
    sprintf_s(windowTitle, 256, "3DEngine   %f Ms   %f FPS", m_Timer.GetFrameTimeInMs(), m_Timer.GetFrames());
    SetWindowText(m_pGraphicsManager->GetWindow(), windowTitle);
#endif
}

CMatrix4f CGameProcess::GenerateDirectionalLightShadowMap(const S_LIGHT *light)
{
    CFPSCamera cam(m_Camera.GetFov(), m_Camera.GetZFar(), m_Camera.GetZFar());
    COrthographicProjectionf orthoProj((float)light->directionalDepthMap.width() / (float)light->directionalDepthMap.height(), 25.0f, 25.0f, 0.0f, 50.0f);

    cam.SetPosition(light->position);
    cam.SetLookAt(CVector3f(0.0f, 0.0f, 0.0f));

    int currentViewPort[4];
    glGetIntegerv(GL_VIEWPORT, currentViewPort);

    glViewport(0, 0, light->directionalDepthMap.width(), light->directionalDepthMap.height());
    m_DirectionalDepthProgramShader.ActiveProgram();
        CMatrix4f lightSpaceMatrix = cam.GetViewMatrix() * orthoProj;
        m_DirectionalDepthProgramShader.setUniformMatrix4("lightSpaceMatrix", false, lightSpaceMatrix.m_pMatrix4);

        light->directionalDepthMap.Bind();
            for (size_t i = 0; m_RenderableObject && i < m_RenderableObject->size(); ++i)
            {
                m_DirectionalDepthProgramShader.setUniformMatrix4("modelMatrix", true, m_RenderableObject->at(i).transform.m_pMatrix4);
                m_RenderableObject->at(i).render();
            }
        light->directionalDepthMap.Unbind();
    m_DirectionalDepthProgramShader.ReleaseProgram();
    glViewport(0, 0, currentViewPort[2], currentViewPort[3]);

    /*
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_DebugQuad.ActiveProgram();
        m_DebugQuad.setUniformValue("zNear", 0.1f);
        m_DebugQuad.setUniformValue("zFar", 1000.0f);

        m_DebugQuad.setUniformValue("depthCubeMap", 0);
        m_DirLightDepthMap.useTexture(0);

        CDebugRender::RenderQuad();
    m_DebugQuad.ReleaseProgram();

    SwapBuffers(m_pGraphicsManager->GetDevice());
    */

    return lightSpaceMatrix;
}

void CGameProcess::GeneratePointLightShadowMap(const S_LIGHT *light)
{
    CPerspectiveProjectionf proj;
    proj.set(90.0f, (float)light->pointDepthMap.width() / (float)light->pointDepthMap.height(), m_Camera.GetZNear(), m_Camera.GetZFar());

    struct cubeFace_t
    {
        CVector3f dir;
        CVector3f up;
    };

    static cubeFace_t cubeFace[6] =
    {
        { CVector3f( 1.0f,  0.0f,  0.0f), CVector3f(0.0f, -1.0f,  0.0f) }, // GL_TEXTURE_CUBE_MAP_POSITIVE_X
        { CVector3f(-1.0f,  0.0f,  0.0f), CVector3f(0.0f, -1.0f,  0.0f) }, // GL_TEXTURE_CUBE_MAP_NEGATIVE_X
        { CVector3f( 0.0f,  1.0f,  0.0f), CVector3f(0.0f,  0.0f,  1.0f) }, // GL_TEXTURE_CUBE_MAP_POSITIVE_Y
        { CVector3f( 0.0f, -1.0f,  0.0f), CVector3f(0.0f,  0.0f, -1.0f) }, // GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
        { CVector3f( 0.0f,  0.0f,  1.0f), CVector3f(0.0f, -1.0f,  0.0f) }, // GL_TEXTURE_CUBE_MAP_POSITIVE_Z
        { CVector3f( 0.0f,  0.0f, -1.0f), CVector3f(0.0f, -1.0f,  0.0f) }  // GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    char shadowMatrixName[256];

    m_PointLightDeptProgramShader.ActiveProgram();
        m_PointLightDeptProgramShader.setUniformValue("zFar", m_Camera.GetZFar());
        m_PointLightDeptProgramShader.setUniformVector3f("lightPos", light->position.u);

        for (int j = 0; j < 6; ++j)
        {
            sprintf_s(shadowMatrixName, "lightSpaceMatrix[%d]", j);
            CMatrix4f lightSpaceMatrix = CLookAtf(light->position, light->position + cubeFace[j].dir, cubeFace[j].up) * proj;
            m_PointLightDeptProgramShader.setUniformMatrix4(shadowMatrixName, false, lightSpaceMatrix.m_pMatrix4);
        }

        light->pointDepthMap.Bind();
            for (size_t j = 0; m_RenderableObject && j < m_RenderableObject->size(); ++j)
            {
                m_PointLightDeptProgramShader.setUniformMatrix4("modelMatrix", true, m_RenderableObject->at(j).transform.m_pMatrix4);
                m_RenderableObject->at(j).render();
            }
        light->pointDepthMap.Unbind();
    m_PointLightDeptProgramShader.ReleaseProgram();
}

void CGameProcess::GenerateSSAODepthMap(CDepthMap &map)
{
    CPerspectiveProjectionf proj;
    proj.set(90.0f, (float)map.width() / (float)map.height(), m_Camera.GetZNear(), m_Camera.GetZFar());

    m_SSAO.shaderProg.ActiveProgram();
        m_SSAO.shaderProg.setUniformValue("zFar", m_Camera.GetZFar());
        m_SSAO.shaderProg.setUniformVector3f("cameraPos", m_Camera.GetPosition().u);

        CMatrix4f lightSpaceMatrix = m_Camera.GetViewMatrix() * proj;
        m_SSAO.shaderProg.setUniformMatrix4("projViewMatrix", false, lightSpaceMatrix.m_pMatrix4);

        map.Bind();
            for (size_t j = 0; m_RenderableObject && j < m_RenderableObject->size(); ++j)
            {
                m_SSAO.shaderProg.setUniformMatrix4("modelMatrix", true, m_RenderableObject->at(j).transform.m_pMatrix4);
                m_RenderableObject->at(j).render();
            }
        map.Unbind();
    m_SSAO.shaderProg.ReleaseProgram();
}

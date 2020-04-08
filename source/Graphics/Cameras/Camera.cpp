#include "./Camera.h"
#include "Common/Math/Constants.h"

CCamera::CCamera()
{
    m_ZFar = 0.01f;
    m_ZNear = 1000.0f;

    m_Fov = DEG2RAD(60.0f);

    m_CameraType = ECameraType::TC_FIRST_PERSON;
    m_3DCameraInfo = NULL;
}

CCamera::CCamera(float fov, float zNear, float zFar, CObject3D *cameraInfo, ECameraType cameraType)
{
    m_ZFar = zFar;
    m_ZNear = zNear;

    m_Fov = DEG2RAD(fov);

    m_CameraType = cameraType;
    m_3DCameraInfo = cameraInfo;
}

CCamera::~CCamera()
{
    m_3DCameraInfo = NULL;
}

float CCamera::GetFov(void)
{
    return m_Fov;
}

float CCamera::GetZFar(void)
{
    return m_ZFar;
}

float CCamera::GetZNear(void)
{
    return m_ZNear;
}

ECameraType CCamera::GetCameraType(void)
{
    return m_CameraType;
}

CObject3D *CCamera::Get3DCameraInfo(void)
{
    return m_3DCameraInfo;
}

void CCamera::Execute(void)
{
    Update();
}

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

CCamera::CCamera(float l_Fov, float l_ZNear, float l_ZFar, CObject3D &l_3DCameraInfo, ECameraType l_CameraType)
{
    m_ZFar = l_ZFar;
    m_ZNear = l_ZNear;

    m_Fov = DEG2RAD(l_Fov);

    m_CameraType = l_CameraType;
    m_3DCameraInfo = &l_3DCameraInfo;
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

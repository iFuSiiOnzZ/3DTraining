#include "./Camera.h"
#include "Common/Math/Constants.h"

CCamera::CCamera()
{
    m_ZFar = 0.01f;
    m_ZNear = 1000.0f;

    m_Fov = 60.0f;
    m_CameraType = ECameraType::UNDEFINED;
}

CCamera::CCamera(float fov, float zNear, float zFar)
{
    m_ZFar = zFar;
    m_ZNear = zNear;

    m_Fov = fov;
    m_CameraType = ECameraType::UNDEFINED;
}

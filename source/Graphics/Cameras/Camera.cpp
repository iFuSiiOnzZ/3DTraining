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

void CCamera::SetLookAt(const CVector3f &lookAt)
{
    CVector3f dir = (lookAt - m_CameraInfo.GetPosition());
    float y = std::atan2f(dir.x, dir.z), p = std::atan2f(dir.y, std::sqrtf(dir.x * dir.x + dir.z * dir.z));

    m_CameraInfo.SetYaw(y);
    m_CameraInfo.SetPitch(p);
}

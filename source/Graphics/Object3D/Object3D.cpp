#include "./Object3D.h"

CObject3D::CObject3D(void)
    : m_Position(0, 0, 0)
    , m_Scale(1, 1, 1)
    , m_Yaw(0.0f)
    , m_Roll(0.0f)
    , m_Pitch(0.0f)
{
}

CMatrix4f CObject3D::GetTransform(void)
{
    return CTranslationf(m_Position) * CScalef(m_Scale) * GetRotation() * CTranslationf(-m_Position);
}

CMatrix4f CObject3D::GetRotation(void)
{
    return CRotationf(m_Pitch, 1.0f, 0.0f, 0.0f) * CRotationf(m_Yaw, 0.0f, 1.0f, 0.0f) * CRotationf(m_Roll, 0.0f, 0.0f, 1.0f);
}

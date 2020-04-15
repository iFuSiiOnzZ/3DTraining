#pragma once

#include "Common/Math/Matrix/Matrix.h"
#include "Common/Math/Vector/Vector.h"

class CObject3D
{
    protected:
        CVector3f m_Position;
        CVector3f m_Scale;

        float     m_Yaw;
        float     m_Roll;
        float     m_Pitch;

    public:
        CObject3D   (void);

        inline void SetYaw(float yaw) { m_Yaw = yaw; }
        inline void SetRoll(float roll) { m_Roll = roll; }
        inline void SetPitch(float pitch) { m_Pitch = pitch; }

        inline float GetYaw(void) { return m_Yaw; }
        inline float GetRoll(void) { return m_Roll; }
        inline float GetPitch(void) { return m_Pitch; }

        inline void SetPosition(const CVector3f &postion) { m_Position = postion; }
        inline void SetScale(const CVector3f &scale) { m_Scale = scale; }

        inline const CVector3f &GetPosition(void) { return m_Position; }
        inline const CVector3f &GetScale(void) { return m_Scale; }

        CMatrix4f GetTransform(void);
        CMatrix4f GetRotation(void);
};

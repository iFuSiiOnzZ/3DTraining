#pragma once

#include "Common/Math/Matrix/Matrix.h"
#include "Common/Math/Vector/Vector.h"

class CObject3D
{
    protected:
        CMatrix4f m_Transform;

        CVector4f m_Position;
        CVector4f m_Scale;

        float     m_Yaw;
        float     m_Roll;
        float     m_Pitch;

    public:
        CObject3D      (void);
        ~CObject3D     (void);

        void SetYaw    (float yaw);
        void SetRoll   (float roll);
        void SetPitch  (float pitch);

        float GetYaw   (void);
        float GetRoll  (void);
        float GetPitch (void);

        void SetPosition (const CVector4f &Postion);
        void SetScale    (const CVector4f &Scale);

        CMatrix4f &GetTransform   (void);
        CVector4f &GetPosition    (void);
        CVector4f &GetScale       (void);
};

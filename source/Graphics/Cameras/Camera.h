#pragma once

#include "Graphics/Object3D/Object3D.h"

struct S_PLATFORM;
class CTimer;

enum class ECameraType : unsigned int
{
    UNDEFINED,
    FIRST_PERSON,
    THIRD_PERSON
};

class CCamera
{
    protected:
        float m_Fov;
        float m_ZFar;
        float m_ZNear;

        ECameraType m_CameraType;
        CObject3D m_CameraInfo;

    public:
        CCamera  (void);
        CCamera  (float fov, float zNear, float zFar);
        virtual ~CCamera(void) {}

        inline float GetFov(void) { return m_Fov; }
        inline float GetZFar(void) { return m_ZFar; }
        inline float GetZNear(void) { return m_ZNear; }

        inline ECameraType GetCameraType(void) { return m_CameraType; }
        inline CObject3D &Get3DCameraInfo(void) { return m_CameraInfo; }

        inline CVector3f GetUp(void) { return GetStride() ^ GetDirection(); }
        inline CVector3f GetLookAt(void) { return GetDirection().normalize() + GetPosition(); }

        inline CVector3f GetPosition(void) { return m_CameraInfo.GetPosition(); }
        inline void SetPosition(const CVector3f &pos) { m_CameraInfo.SetPosition(pos); }

        virtual CVector3f GetDirection  (void) = 0;
        virtual CVector3f GetStride     (void) = 0;

        inline CMatrix4f GetViewMatrix(void) { return CLookAtf(GetPosition(), GetLookAt(), GetUp()); }
        void SetLookAt(const CVector3f &lookAt);

        virtual void Update (const S_PLATFORM *platform, CTimer *gameTimer) = 0;
};

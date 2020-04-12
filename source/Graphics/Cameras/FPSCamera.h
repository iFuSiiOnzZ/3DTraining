#pragma once

#include "./Camera.h"

class CFPSCamera : public CCamera
{
    private:
        float m_Speed;

    private:
        void UpdateYawPitch(const S_PLATFORM *platform);

    public:
        CFPSCamera(void);
        CFPSCamera(float fov, float zNear, float zFar);

        void Update(const S_PLATFORM *platform, CTimer *gameTimer) override;

        CVector3f GetDirection(void) override;
        CVector3f GetStride(void)    override;
};

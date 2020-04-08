#pragma once

#include "./Camera.h"
#include "Input/InputManager.h"
#include "Common\Timer\Timer.h"

class CFPSCamera : public CCamera
{
    private:
        CInputManager *m_InputManager;
        CTimer        *m_Timer;

    public:
        CFPSCamera(void);
        CFPSCamera(float fov, float zNear, float zFar, CObject3D *cameraInfo, CInputManager *inputManager, CTimer *timer);
        ~CFPSCamera(void);

        void Update(void) override;

        CVector4f GetUp(void)        override;
        CVector4f GetLookAt(void)    override;

        CVector4f GetDirection(void) override;
        CVector4f GetStride(void)    override;

        CVector4f GetPosition(void)  override;
};

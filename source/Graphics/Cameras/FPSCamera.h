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
        CFPSCamera(float l_Fov, float l_ZNear, float l_ZFar, CObject3D *l_3DCameraInfo, CInputManager *l_InputManager, CTimer *l_Timer);
        ~CFPSCamera(void);

        void Update(void);

        CVector4f GetUp(void);
        CVector4f GetLookAt(void);

        CVector4f GetDirection(void);
        CVector4f GetStride(void);

        CVector4f GetPosition(void);
};

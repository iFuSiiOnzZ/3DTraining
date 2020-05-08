#include "./FPSCamera.h"

#include "Core/platform.h"
#include "Common/Timer/Timer.h"
#include "Common/Math/Constants.h"

CFPSCamera::CFPSCamera(void)
    : CCamera()
    , m_Speed(0.01f)
{
    m_CameraType = ECameraType::FIRST_PERSON;
}

CFPSCamera::CFPSCamera(float fov, float zNear, float zFar)
    : CCamera(fov, zNear, zFar)
    , m_Speed(0.1f)
{
    m_CameraType = ECameraType::FIRST_PERSON;
}

void CFPSCamera::UpdateYawPitch(const S_PLATFORM *platform)
{
    static bool firstTime = true;
    if (!platform->data.isAppActive)
    {
        firstTime = true;
        return;
    }

    int mX = platform->data.input->Mouse.Position.x;
    int mY = platform->data.input->Mouse.Position.y;

    int sX = platform->data.screenSize.x / 2;
    int sY = platform->data.screenSize.y / 2;

    if (firstTime)
    {
        mX = sX, mY = sY;
        firstTime = false;
    }

    platform->fn.SetMousePos(sX, sY);
    int dX = (mX - sX), dY = (mY - sY);

    float pitch = m_CameraInfo.GetPitch() - DEG2RAD((float)dY) * 0.2f;
    float yaw   = m_CameraInfo.GetYaw() - DEG2RAD((float)dX) * 0.2f;

    if (yaw > CONSTANTS_TWO_PI) yaw -= CONSTANTS_TWO_PI;
    if (yaw < 0.0f) yaw += CONSTANTS_TWO_PI;

    if (pitch >  CONSTANTS_HALF_PI) pitch =  CONSTANTS_HALF_PI;
    if (pitch < -CONSTANTS_HALF_PI) pitch = -CONSTANTS_HALF_PI;

    m_CameraInfo.SetPitch(pitch);
    m_CameraInfo.SetYaw(yaw);
}

void CFPSCamera::Update(const S_PLATFORM *platform, CTimer *gameTimer)
{
#define IsKeyDown(x)        (platform->data.input->Keyboard.KeyState[x].IsDown)
#define WasKeyDown(x)       (platform->data.input->Keyboard.KeyState[x].WasDown)
#define IsFnKeyDown(x)      (platform->data.input->Keyboard. ## x ## ->IsDown)
#define WasFnKeyDown(x)     (platform->data.input->Keyboard. ## x ## ->WasDown)
#define IsButtonPadDown(x)  (platform->data.input->Pad. ## x ## .IsDown)
#define WasButtonPadDown(x) (platform->data.input->Pad. ## x ## .WasDown)

    UpdateYawPitch(platform);
    CVector3f direction = GetDirection(), eyePos = GetPosition(), stride = GetStride();

    if (IsKeyDown('A'))
        eyePos = eyePos - stride * (m_Speed * 0.5f) * gameTimer->GetSpeedFactor();
    else if (IsKeyDown('D'))
        eyePos = eyePos + stride * (m_Speed * 0.5f) * gameTimer->GetSpeedFactor();

    if (IsKeyDown('W'))
        eyePos = eyePos + direction * m_Speed * gameTimer->GetSpeedFactor();
    else if (IsKeyDown('S'))
        eyePos = eyePos - direction * m_Speed * gameTimer->GetSpeedFactor();

    if (IsKeyDown('E') || IsButtonPadDown(Y))
        eyePos = eyePos + CVector3f(0.0f, 1.0f, 0.0f) * m_Speed * gameTimer->GetSpeedFactor();
    else if (IsKeyDown('Q') || IsButtonPadDown(A))
        eyePos = eyePos - CVector3f(0.0f, 1.0f, 0.0f) * m_Speed * gameTimer->GetSpeedFactor();

    m_Speed += (0.01f * platform->data.input->Mouse.zDelta);
    if (m_Speed < 0.01f) m_Speed = 0.01f;

    m_CameraInfo.SetPosition(eyePos);

#undef IsKeyDown
#undef WasKeyDown
#undef IsFnKeyDown
#undef WasFnKeyDown
#undef IsButtonPadDown
#undef WasButtonPadDown
}

CVector3f CFPSCamera::GetDirection(void)
{
    float pitch = m_CameraInfo.GetPitch(), yaw = m_CameraInfo.GetYaw();
    return CVector3f(std::cosf(pitch) * std::sinf(yaw), std::sinf(pitch), std::cosf(pitch) * std::cosf(yaw));
}

CVector3f CFPSCamera::GetStride(void)
{
    float yaw = m_CameraInfo.GetYaw();
    return CVector3f(std::sinf(yaw - CONSTANTS_HALF_PI), 0.0f, std::cosf(yaw - CONSTANTS_HALF_PI));
}

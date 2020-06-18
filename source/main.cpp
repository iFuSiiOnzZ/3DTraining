#include <Windows.h>
#include <process.h>

#include <Xinput.h>
#include <windowsx.h>
//
#include "Core/Engine.h"
#include "Core/Process.h"
#include "Core/platform.h"

#include "VideoGame/GameProcess.h"
//

#include "Common/Memory/AllocatorManager.h"
#include "Common/Utils/ResourceManager.h"
#include "Common/Memory/MemLeaks.h"

#include "Graphics/GraphicsManager/GraphicsManager.h"

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glew32.lib")

#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)

typedef X_INPUT_SET_STATE(x_input_set_state);
typedef X_INPUT_GET_STATE(x_input_get_state);

X_INPUT_SET_STATE(XInputSetStateStub) { (void)dwUserIndex; (void)pVibration; return 0; }
X_INPUT_GET_STATE(XInputGetStateStub) { (void)dwUserIndex; (void)pState;     return 0; }

static x_input_set_state *XInputSetState_ = XInputSetStateStub;
static x_input_get_state *XInputGetState_ = XInputGetStateStub;

#define XInputSetState XInputSetState_
#define XInputGetState XInputGetState_

#define ASSERT(x) if(!!(x)){*(int *)0 = 0;}
#define NUM_ELEMENTS(x) (sizeof(x) / sizeof((x)[0]))

static S_PLATFORM gPlatform = {};
static HWND gWindowHandler = nullptr;

static void Win32LoadXInput(void)
{
    HMODULE XInputLibrary = LoadLibraryA("XInput9_1_0.dll");
    if (!XInputLibrary) return;

    XInputGetState = (x_input_get_state *)GetProcAddress(XInputLibrary, "XInputGetState");
    if (!XInputGetState) { XInputGetState = XInputGetStateStub; }

    XInputSetState = (x_input_set_state *)GetProcAddress(XInputLibrary, "XInputSetState");
    if (!XInputSetState) { XInputSetState = XInputSetStateStub; }
}

static void Win32ProcessXInputDigitalButton(DWORD XInputButtonState, S_INPUT_STATE *lastState, DWORD ButtonBit, S_INPUT_STATE *currentState)
{
    currentState->WasDown = lastState->IsDown;
    currentState->IsDown = ((XInputButtonState & ButtonBit) == ButtonBit);
    currentState->HalfTransitionCount = (lastState->IsDown != currentState->IsDown) ? 1 : 0;
}

static float Win32ProcessXInputStickValue(SHORT Value, SHORT DeadZoneThreshold)
{
    float retValue = 0.0f;

    if (Value < -DeadZoneThreshold)
    {
        retValue = (float)((Value + DeadZoneThreshold) / (32768.0f - DeadZoneThreshold));
    }
    else if (Value > DeadZoneThreshold)
    {
        retValue = (float)((Value - DeadZoneThreshold) / (32767.0f - DeadZoneThreshold));
    }

    return retValue;
}

static void Win32ProcessGamePad(S_USER_INPUT *currentInput, S_USER_INPUT *lastInput)
{
    XINPUT_STATE controllerState;

    if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
    {
        XINPUT_GAMEPAD *pad = &controllerState.Gamepad;

        currentInput->Pad.LeftStick.x = Win32ProcessXInputStickValue(pad->sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        currentInput->Pad.LeftStick.y = Win32ProcessXInputStickValue(pad->sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

        currentInput->Pad.RightStick.x = Win32ProcessXInputStickValue(pad->sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
        currentInput->Pad.RightStick.y = Win32ProcessXInputStickValue(pad->sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

        currentInput->Pad.LeftTrigger = (float)pad->bLeftTrigger / 255.0f;
        currentInput->Pad.RightTrigger = (float)pad->bRightTrigger / 255.0f;

        Win32ProcessXInputDigitalButton(pad->wButtons,
            &lastInput->Pad.A, XINPUT_GAMEPAD_A,
            &currentInput->Pad.A);

        Win32ProcessXInputDigitalButton(pad->wButtons,
            &lastInput->Pad.B, XINPUT_GAMEPAD_B,
            &currentInput->Pad.B);

        Win32ProcessXInputDigitalButton(pad->wButtons,
            &lastInput->Pad.X, XINPUT_GAMEPAD_X,
            &currentInput->Pad.X);

        Win32ProcessXInputDigitalButton(pad->wButtons,
            &lastInput->Pad.Y, XINPUT_GAMEPAD_Y,
            &currentInput->Pad.Y);

        Win32ProcessXInputDigitalButton(pad->wButtons,
            &lastInput->Pad.Start, XINPUT_GAMEPAD_START,
            &currentInput->Pad.Start);

        Win32ProcessXInputDigitalButton(pad->wButtons,
            &lastInput->Pad.Back, XINPUT_GAMEPAD_BACK,
            &currentInput->Pad.Back);

        Win32ProcessXInputDigitalButton(pad->wButtons,
            &lastInput->Pad.LeftShoulder, XINPUT_GAMEPAD_LEFT_SHOULDER,
            &currentInput->Pad.LeftShoulder);

        Win32ProcessXInputDigitalButton(pad->wButtons,
            &lastInput->Pad.RightShoulder, XINPUT_GAMEPAD_RIGHT_SHOULDER,
            &currentInput->Pad.RightShoulder);
    }
}

static void Win32ProcessKeyboardMessage(S_INPUT_STATE *currentState, bool isDown)
{
    if (currentState->IsDown != isDown)
    {
        currentState->IsDown = isDown;
        currentState->WasDown = !isDown;
        ++currentState->HalfTransitionCount;
    }
}

static void Win32ProcessPendingMessage(S_USER_INPUT *currentInput, S_USER_INPUT *lastInput)
{
    for (int i = 0; i < NUM_ELEMENTS(currentInput->Keyboard.KeyState); ++i)
    {
        currentInput->Keyboard.KeyState[i].IsDown = lastInput->Keyboard.KeyState[i].IsDown;
        currentInput->Keyboard.KeyState[i].HalfTransitionCount = 0;
        currentInput->Keyboard.KeyState[i].WasDown = false;
    }

    {
        currentInput->Mouse.ButtonLeft.IsDown = lastInput->Mouse.ButtonLeft.IsDown;
        currentInput->Mouse.ButtonLeft.WasDown = false;

        currentInput->Mouse.ButtonRight.IsDown = lastInput->Mouse.ButtonRight.IsDown;
        currentInput->Mouse.ButtonRight.WasDown = false;

        currentInput->Mouse.ButtonMiddle.IsDown = lastInput->Mouse.ButtonMiddle.IsDown;
        currentInput->Mouse.ButtonMiddle.WasDown = false;

        currentInput->Mouse.Position = lastInput->Mouse.Position;
        currentInput->Mouse.zDelta = 0.0f;
    }

    MSG hMsg;
    while (PeekMessageA(&hMsg, NULL, 0U, 0U, PM_REMOVE))
    {
        switch (hMsg.message)
        {
            case WM_SYSKEYDOWN:
            case WM_KEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYUP:
            {
                bool wasDown = ((hMsg.lParam & (1UL << 30)) != 0);
                bool isDown  = ((hMsg.lParam & (1UL << 31)) == 0);

                if (isDown != wasDown)
                {
                    Win32ProcessKeyboardMessage(&currentInput->Keyboard.KeyState[hMsg.wParam], isDown);
                }
            } break;

            case WM_LBUTTONDOWN:
            {
                currentInput->Mouse.ButtonLeft.IsDown = true;

            } break;

            case WM_LBUTTONUP:
            {
                currentInput->Mouse.ButtonLeft.IsDown = false;
                currentInput->Mouse.ButtonLeft.WasDown = true;
            } break;

            case WM_RBUTTONDOWN:
            {
                currentInput->Mouse.ButtonRight.IsDown = true;

            } break;

            case WM_RBUTTONUP:
            {
                currentInput->Mouse.ButtonRight.IsDown = false;
                currentInput->Mouse.ButtonRight.WasDown = true;
            } break;

            case WM_MBUTTONDOWN:
            {
                currentInput->Mouse.ButtonMiddle.IsDown = true;

            } break;

            case WM_MBUTTONUP:
            {
                currentInput->Mouse.ButtonMiddle.IsDown = false;
                currentInput->Mouse.ButtonMiddle.WasDown = true;
            } break;

            case WM_MOUSEWHEEL:
            {
                // NOTE(Andrei): The orignal values is always 120
                currentInput->Mouse.zDelta = (float)GET_WHEEL_DELTA_WPARAM(hMsg.wParam) / 120.0f;
            } break;

            case WM_MOUSEMOVE:
            {
                currentInput->Mouse.Position.x = GET_X_LPARAM(hMsg.lParam);
                currentInput->Mouse.Position.y = GET_Y_LPARAM(hMsg.lParam);
            } break;

            default:
            {
                TranslateMessage(&hMsg);
                DispatchMessageA(&hMsg);
            } break;
        }
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT hMsg, WPARAM wParam, LPARAM lParam)
{
    switch (hMsg)
    {
        case WM_CLOSE:
        {
            DestroyWindow(hWnd);
        } break;

        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS);
        } break;

        case  WM_SIZE:
        {
            gPlatform.data.screenSize.x = LOWORD(lParam);
            gPlatform.data.screenSize.y = HIWORD(lParam);
        } break;

        case WM_SIZING:
        {
            RECT *r = (RECT *)lParam;
            gPlatform.data.screenSize.x = r->right - r->left;
            gPlatform.data.screenSize.y = r->bottom - r->top;
        }

        case WM_ACTIVATEAPP:
        {
            if (wParam == TRUE)
            {
                gPlatform.data.isAppActive = true;
                ShowCursor(FALSE);
            }
            else
            {
                gPlatform.data.isAppActive = false;
                ShowCursor(TRUE);
            }
        } break;

        default:
        {
            return DefWindowProcA(hWnd, hMsg, wParam, lParam);
        } break;
    }

    return 0;
}

void PrintLastError(const char *msg)
{
    DWORD errCode = GetLastError();
    char *err;

    if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, errCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&err, 0, NULL))
        return;

    static char buffer[1024];
    sprintf_s(buffer, sizeof(buffer), "ERROR: %s: %s\n", msg, err);

    OutputDebugStringA(buffer);
    LocalFree(err);
}

bool SetCursorPosition(int x, int y)
{
    POINT pt = { (LONG)x, (LONG)y };
    ClientToScreen(gWindowHandler, &pt);

    if (SetCursorPos(pt.x, pt.y) == 0)
    {
        PrintLastError("SetCursorPosition");
        return false;
    }

    return true;
}

int WINAPI WinMain(HINSTANCE hActualInst, HINSTANCE hPrevInst, LPSTR cmdLine, int cmdShow)
{
    (void)cmdShow, (void)cmdLine, (void)hPrevInst;
    Win32LoadXInput();

    static const char *PROGRAM_NAME  = "3DTraining";
    static const char *PROGRAM_CLASS = "3DTraining";

    WNDCLASSEX  wndCls;
    memset(&wndCls, 0, sizeof(WNDCLASSEX));


    wndCls.cbSize       = sizeof(WNDCLASSEX);
    wndCls.cbClsExtra   = 0;
    wndCls.cbWndExtra   = 0;

    wndCls.hInstance    = hActualInst;
    wndCls.hCursor      = LoadCursor(NULL, IDC_ARROW);
    wndCls.hIconSm      = LoadIcon(NULL, IDI_APPLICATION);
    wndCls.hIcon        = LoadIcon(NULL, IDI_APPLICATION);

    wndCls.lpfnWndProc      = WndProc;
    wndCls.lpszMenuName     = NULL;
    wndCls.lpszClassName    = PROGRAM_CLASS;

    wndCls.style            = 0;
    wndCls.hbrBackground    = (HBRUSH) (COLOR_WINDOW + 1);

    unsigned int screenSizeX = GetSystemMetrics(SM_CXSCREEN);
    unsigned int screenSizeY = GetSystemMetrics(SM_CYSCREEN);

    if(RegisterClassEx(&wndCls) == 0)
    {
        MessageBox(NULL, "Window Registration Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return(EXIT_FAILURE);
    }

    gWindowHandler = CreateWindowEx
    (
        WS_EX_CLIENTEDGE, PROGRAM_CLASS, PROGRAM_NAME, WS_OVERLAPPEDWINDOW, 0, 0,
        screenSizeX, screenSizeY, NULL, NULL, hActualInst, NULL
    );

    if(gWindowHandler == NULL)
    {
        MessageBox(NULL, "Window Creation Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return EXIT_FAILURE;
    }

    ShowWindow(gWindowHandler, SW_SHOWMAXIMIZED);
    UpdateWindow(gWindowHandler);

    MemLeaks::MemoryBegin();

    CGraphicsManager graphicsManager;
    if(!graphicsManager.Init(gWindowHandler, false))
    {
        UnregisterClass(PROGRAM_CLASS, wndCls.hInstance);
        return EXIT_FAILURE;
    }

    CAllocatorManager *allocatorManager = new CAllocatorManager();
    CResourceManager *resourceManager = new CResourceManager();

    CGameProcess process(&graphicsManager);
    bool RunGame = true;

    CEngine gameEgine(&process);
    gameEgine.Init(&gPlatform);

    S_USER_INPUT gameControllers[2] = {};
    S_USER_INPUT *lastInput = &gameControllers[1];
    S_USER_INPUT *currentInput = &gameControllers[0];

    while(RunGame)
    {
        Win32ProcessPendingMessage(currentInput, lastInput);
        Win32ProcessGamePad(currentInput, lastInput);

        gPlatform.data.input = currentInput;
        gPlatform.fn.SetMousePos = SetCursorPosition;

        process.Update(&gPlatform);
        process.Render(&gPlatform);

        if (currentInput->Keyboard.Esc->IsDown)
        {
            RunGame = false;
        }

        std::swap(currentInput, lastInput);
    }

    gameEgine.Release(&gPlatform);
    graphicsManager.Release();

    delete allocatorManager;
    delete resourceManager;
    MemLeaks::MemoryEnd();

    UnregisterClass(PROGRAM_CLASS, wndCls.hInstance);
    return EXIT_SUCCESS;
}

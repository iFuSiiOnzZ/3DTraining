#pragma once

typedef struct S_INPUT_STATE
{
    int HalfTransitionCount = 0;
    bool IsDown = false, WasDown = false;
} S_INPUT_STATE;

typedef struct S_PAD_CONTROLLER
{
    struct S_CONTROLLER_STICK
    {
        float x, y;
    };

    float LeftTrigger, RightTrigger;

    S_CONTROLLER_STICK LeftStick;
    S_CONTROLLER_STICK RightStick;

    S_INPUT_STATE A, B, X, Y;
    S_INPUT_STATE PadUp, PadDown, PadLeft, PadRight;

    S_INPUT_STATE Start, Back;
    S_INPUT_STATE LeftShoulder, RightShoulder;
} S_GAME_CONTROLLER;

typedef struct S_MOUSE_CONTROLLER
{
    struct S_MOUSE_COORD
    {
        int x, y;
    };

    float zDelta = 0.0f;
    S_MOUSE_COORD Position;
    S_INPUT_STATE ButtonLeft, ButtonRight, ButtonMiddle;
} S_MOUSE_CONTROLLER;

typedef struct S_KEYBOARD_CONTROLLER
{
    S_INPUT_STATE KeyState[256] = {};

    S_INPUT_STATE *F1 = &KeyState[0x70]
        , *F2 = &KeyState[0x71]
        , *F3 = &KeyState[0x72]
        , *F4 = &KeyState[0x73]
        , *F5 = &KeyState[0x74]
        , *F6 = &KeyState[0x75]
        , *F7 = &KeyState[0x76]
        , *F8 = &KeyState[0x77]
        , *F9 = &KeyState[0x78]
        , *F10 = &KeyState[0x79]
        , *F11 = &KeyState[0x7A]
        , *F12 = &KeyState[0x7B];

    S_INPUT_STATE *Ctrl = &KeyState[0x11]
        , *Shift = &KeyState[0x10]
        , *Alt = &KeyState[0x12]
        , *Tab = &KeyState[0x09]
        , *Enter = &KeyState[0x0D]
        , *Back = &KeyState[0x08]
        , *Pause = &KeyState[0x13]
        , *Esc = &KeyState[0x1B]
        , *Left = &KeyState[0x25]
        , *Right = &KeyState[0x27]
        , *Up = &KeyState[0x26]
        , *Down = &KeyState[0x28];
} S_KEYBOARD_CONTROLLER;

typedef struct S_USER_INPUT
{
    S_PAD_CONTROLLER Pad;
    S_MOUSE_CONTROLLER Mouse;
    S_KEYBOARD_CONTROLLER Keyboard;
} S_USER_INPUT;

typedef struct S_PLATFORM
{
    struct S_POINT_2D
    {
        int x, y;
    };

    struct functions_t
    {
        bool (*SetMousePos)(int x, int y);
    };

    struct data_t
    {
        bool isAppActive;
        S_POINT_2D screenSize;
        S_USER_INPUT *input;
    };

    functions_t fn;
    data_t data;
} S_PLATFORM;

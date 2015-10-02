#pragma once

#include <Windows.h>
#include <gl\glew.h>
#include <gl\wglew.h>

class CGraphicsManager
{
    private:
        HDC     m_pDeviceContext;
		HGLRC   m_pRenderContext;
		HWND    m_pWndInstance;

    public:
        CGraphicsManager        (void);
        ~CGraphicsManager       (void);

        bool    Init            (const HWND &hWnd, bool vSync);
        bool    Release         (void);

        HDC     GetDevice       (void);
        HGLRC   GetRender       (void);
};

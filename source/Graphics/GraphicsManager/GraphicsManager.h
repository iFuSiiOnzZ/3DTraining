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

        inline HDC   GetDevice() { return m_pDeviceContext; }
        inline HGLRC GetRender() { return m_pRenderContext; }

        inline HWND  GetWindow       (void) { return m_pWndInstance; }
        void         GetWindowSize   (unsigned int &l_Width, unsigned int &l_Height);
};

#include "./GraphicsManager.h"

CGraphicsManager::CGraphicsManager(void)
{
    m_pRenderContext = NULL;
    m_pDeviceContext = NULL;
    m_pWndInstance   = NULL;
}

CGraphicsManager::~CGraphicsManager(void)
{
    Release();
}

bool CGraphicsManager::Release(void)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(m_pRenderContext);
    ReleaseDC(m_pWndInstance, m_pDeviceContext);

    m_pDeviceContext = NULL;
    m_pRenderContext = NULL;

    return true;
}

bool CGraphicsManager::Init(const HWND &hWnd, bool vSync)
{
    m_pWndInstance = hWnd;
    PIXELFORMATDESCRIPTOR pFormat;

    memset(&pFormat, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pFormat.dwFlags     = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

    pFormat.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
    pFormat.nVersion    = 1;

    pFormat.iPixelType  = LPD_TYPE_RGBA;
    pFormat.cColorBits  = 32;
    pFormat.cDepthBits  = 24;

    if(NULL == (m_pDeviceContext = GetDC(m_pWndInstance))) return false;
    if(TRUE != SetPixelFormat(m_pDeviceContext, ChoosePixelFormat(m_pDeviceContext, &pFormat), &pFormat)) return false;

    if(NULL == (m_pRenderContext = wglCreateContext(m_pDeviceContext))) return false;
    if(TRUE != wglMakeCurrent(m_pDeviceContext, m_pRenderContext)) return false;

    if(GLEW_OK != glewInit()) return false;
    wglSwapIntervalEXT(vSync);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    return true;
}

void CGraphicsManager::GetWindowSize(unsigned int &l_Width, unsigned int &l_Height)
{
    HMONITOR l_Monitor = MonitorFromWindow(m_pWndInstance, MONITOR_DEFAULTTONEAREST);
    MONITORINFO l_MonitorInfo = { 0 };

    l_MonitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(l_Monitor, &l_MonitorInfo);

    l_Width = l_MonitorInfo.rcMonitor.right - l_MonitorInfo.rcMonitor.left;
    l_Height = l_MonitorInfo.rcMonitor.bottom - l_MonitorInfo.rcMonitor.top;
}

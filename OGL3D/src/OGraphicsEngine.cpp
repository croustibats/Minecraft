#include "OGraphicsEngine.h"
#include "glad_wgl.h"
#include "glad.h"
#include <assert.h>
#include <tchar.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = _T("OGL3DDummyWindow");
    wc.lpfnWndProc = DefWindowProc;
    wc.style = CS_OWNDC;

    auto classId = RegisterClassEx(&wc);
    assert(classId);

    auto dummyWindow = CreateWindowEx(NULL, MAKEINTATOM(classId), _T(""), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

    assert(dummyWindow);

    auto dummyDC = GetDC(dummyWindow);

    PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
    pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormatDesc.nVersion = 1;
    pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDesc.cColorBits = 32;
    pixelFormatDesc.cAlphaBits = 8;
    pixelFormatDesc.cDepthBits = 24;
    pixelFormatDesc.cStencilBits = 8;
    pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;


    auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);
    SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);

    auto dummyContext = wglCreateContext(dummyDC);
    assert(dummyContext);

    wglMakeCurrent(dummyDC, dummyContext);

    if (!gladLoadWGL(dummyDC))
        throw std::runtime_error("OGrapghicsEngine - Error - gladLoadWGL failed");

    if (!gladLoadGL())
        throw std::runtime_error("OGrapghicsEngine - Error - gladLoadGL failed");

    wglMakeCurrent(dummyDC, 0);
    wglDeleteContext(dummyContext);
    ReleaseDC(dummyWindow, dummyDC);
    DestroyWindow(dummyWindow);
}

OGraphicsEngine::~OGraphicsEngine()
{
}

void OGraphicsEngine::clear(const OVec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}
#include "OGraphicsEngine.h"
#include "OVertexArrayObject.h"
#include "OShaderProgram.h"
#include "OUniformBuffer.h"
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

OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc)
{
    return std::make_shared<OVertexArrayObject>(vbDesc);
}

OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc & ibDesc)
{
    return std::make_shared<OVertexArrayObject>(vbDesc, ibDesc);
}

OUniformBufferPtr OGraphicsEngine::createUniformBuffer(const OUniformBufferDesc& desc)
{
    return std::make_shared<OUniformBuffer>(desc);
}

OShaderProgramPtr OGraphicsEngine::createShaderProgram(const OShaderProgramDesc& desc)
{
    return std::make_shared<OShaderProgram>(desc);
}

void OGraphicsEngine::clear(const OVec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OGraphicsEngine::setFaceCulling(const OCullType& type)
{
    auto cullType = GL_BACK;

    if (type==FrontFace) cullType == GL_FRONT;
    if (type==BackFace) cullType == GL_BACK;
    if (type==Both) cullType == GL_FRONT_AND_BACK;

    glEnable(GL_CULL_FACE);
    glCullFace(cullType);
}

void OGraphicsEngine::setWindingOrder(const OWindingOrder& order)
{
    auto orderType = GL_CW;

    if (order == ClockWise) orderType = GL_CW;
    if (order == CounterClockWise) orderType = GL_CCW;

    glFrontFace(orderType);
}


void OGraphicsEngine::setViewport(const ORect& size)
{
    glViewport(size.left, size.top, size.width, size.height);
}

void OGraphicsEngine::setVertexArrayObject(const OVertexArrayObjectPtr& vao)
{
    glBindVertexArray(vao->getId());
}

void OGraphicsEngine::setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}

void OGraphicsEngine::setShaderProgram(const OShaderProgramPtr& program)
{
    glUseProgram(program->getId());
}

void OGraphicsEngine::drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset)
{
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
        case TriangleList: { glTriType = GL_TRIANGLES; break; }
        case TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }
    }

    glDrawArrays(glTriType, offset, vertexCount);
}

void OGraphicsEngine::drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount)
{
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
        case TriangleList: { glTriType = GL_TRIANGLES; break; }
        case TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }
    }

    glDrawElements(glTriType, indicesCount, GL_UNSIGNED_INT, nullptr);
}
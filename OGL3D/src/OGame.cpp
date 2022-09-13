#include "OGame.h"
#include "Owindow.h"
#include "OGraphicsEngine.h"
#include "OVertexArrayObject.h"
#include <Windows.h>
#include <tchar.h>


OGame::OGame()
{
    m_graphicsEngine = std::make_unique<OGraphicsEngine>();
    m_display = std::make_unique<OWindow>();

    m_display->makeCurrentContext();

    m_graphicsEngine->setViewport(m_display->getInnerSize());
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
    const f32 triangleVertices[] = {
        -0.5f,-0.5f,0.0f,
        0    ,1    ,0   ,

        0.5f, -0.5f, 0.0f,
        0    ,0    ,1   ,

        0.0f, 0.5f, 0.0f,
        1    ,0    ,0   ,
    };

    OVertextAttribute attribsList[] = {
        3,//position
        3//color
    };

    m_triangleVAO = m_graphicsEngine->createVertexArrayObject(
        {
            (void*)triangleVertices,
            sizeof(f32)*(3+3),
            3,


            attribsList,
            2
        });

    m_shader = m_graphicsEngine->createShaderProgram(
        {
            L"C:\\Users\\Baptiste Cournault\\Documents\\dev\\Minecraft\\OGL3D\\src\\BasicShader.vert",
            L"C:\\Users\\Baptiste Cournault\\Documents\\dev\\Minecraft\\OGL3D\\src\\BasicShader.frag"
        });

}
void OGame::onUpdate()
{

    m_graphicsEngine->clear(OVec4(0, 0, 0, 1));

    m_graphicsEngine->setVertexArrayObject(m_triangleVAO);

    m_graphicsEngine->setShaderProgram(m_shader);

    m_graphicsEngine->drawTriangles(m_triangleVAO->getVertexBufferSize(), 0);

    m_display->present(false);
}
void OGame::onQuit()
{
}
    

void OGame::run()
{   
    onCreate();

    MSG msg = {};
    while (m_isRunning)
    {
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                m_isRunning = false;
                continue;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        onUpdate();
    }

    onQuit();
}

void OGame::quit()
{
    m_isRunning = false;
}


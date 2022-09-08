#include "OGame.h"
#include "Owindow.h"
#include "OGraphicsEngine.h"
#include <Windows.h>


OGame::OGame()
{
    m_graphicsEngine = std::make_unique<OGraphicsEngine>();
    m_display = std::make_unique<OWindow>();

    m_display->makeCurrentContext();
}

OGame::~OGame()
{
}

void OGame::onCreate()
{

    m_graphicsEngine->clear(OVec4(0, 127, 0, 1));

    m_display->present(false);
}
void OGame::onUpdate()
{
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


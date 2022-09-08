#include "../../../include/OGL3D/Game/OGame.h"
#include "../../../include/OGL3D/Window/OWindow.h"
#include <Windows.h>


OGame::OGame()
{
    m_display = std::make_unique<OWindow>();
}

OGame::~OGame()
{

}

void OGame::run()
{   
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

        Sleep(1);
    }
}

void OGame::quit()
{
    m_isRunning = false;
}


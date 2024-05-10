#include<OpenGL3D/Game/OGame.hpp>
#include<OpenGL3D/Window/OWindow.hpp>
#include<Windows.h>


OGame::OGame()
{
    m_display=std::unique_ptr<OWindow>(new OWindow());
}

OGame::~OGame()
{
}

void OGame::run()
{
    MSG msg;
    while(m_isRunning && !m_display->isClosed())
    {
        if(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Sleep(1);
    }
}

void OGame::quit()
{
}

int main(){
    OGame game;
    game.run();
}
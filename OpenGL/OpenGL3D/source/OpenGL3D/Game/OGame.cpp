#include<OGame.hpp>
#include<OWindow.hpp>
#include<Windows.h>


OGame::OGame()
{
    m_display=std::make_unique<OWindow>();
}

OGame::~OGame()
{
}

void OGame::run()
{
    
    while(m_isRunning)
    {
        MSG msg={};
        if(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
        if(msg.message == WM_QUIT)
        {
                m_isRunning=false;
                continue;
        }
        else
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
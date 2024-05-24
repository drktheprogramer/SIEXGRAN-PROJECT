#include<OGame.hpp>
#include<OGraphicsEngine.hpp>
#include<OWindow.hpp>
#include<Windows.h>

void OGame::run()
{
    onCreate();
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
        onUpdate();
    }

    onQuit();
}

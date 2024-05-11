#include<OpenGL3D/Window/OWindow.hpp>
#include<Windows.h>
#include<cassert>



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
        {
            OWindow* window=(OWindow*)GetWindowLongPtr(hwnd,GWLP_USERDATA);
            window->onDestroy();
            break;
        }

        default:
            return DefWindowProc(hwnd,msg,wParam,lParam);
    }
    return NULL;
}

OWindow::OWindow()
{
    WNDCLASSEX wclass={};
    wclass.cbSize=sizeof(WNDCLASSEX);
    wclass.lpszClassName=L"OpenGL Window";
    wclass.lpfnWndProc=&WndProc;

    auto classId=RegisterClassEx(&wclass);

    assert(classId);

    RECT rc={0,0,1024,768};
    AdjustWindowRect(&rc,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,false);
    m_handle=CreateWindowEx(NULL,MAKEINTATOM(classId),L"SIEXGRAN PROJECT | OpenGl Window",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
    CW_USEDEFAULT, CW_USEDEFAULT, rc.right-rc.left, rc.bottom-rc.top,NULL,NULL,NULL,NULL);
    assert(m_handle);

    SetWindowLongPtr((HWND)m_handle,GWLP_USERDATA,(LONG_PTR)this);

    ShowWindow((HWND)m_handle,SW_SHOW);
    UpdateWindow((HWND)m_handle);
}
    

OWindow::~OWindow()
{
    DestroyWindow((HWND)m_handle);
}


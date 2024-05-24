#include<OWindow.hpp>
#include<glad_wgl.h>
#include<glad.h>
#include<cassert>
#include<Windows.h>


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
        {
            OWindow* window=(OWindow*)GetWindowLongPtr(hwnd,GWLP_USERDATA);
            break;
        }
        case WM_QUIT:
        {
            PostQuitMessage(0);
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
    wclass.lpszClassName=(LPCSTR)"OpenGL Window";
    wclass.lpfnWndProc=&WndProc;
    wclass.style=CS_OWNDC;

    auto classId=RegisterClassEx(&wclass);

    assert(classId);

    RECT rc={0,0,1024,768};
    AdjustWindowRect(&rc,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,false);
    m_handle=CreateWindowEx(NULL,MAKEINTATOM(classId),(LPCSTR)"SIEXGRAN PROJECT | OpenGl Window",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
    CW_USEDEFAULT, CW_USEDEFAULT, rc.right-rc.left, rc.bottom-rc.top,NULL,NULL,NULL,NULL);
    assert(m_handle);

    SetWindowLongPtr((HWND)m_handle,GWLP_USERDATA,(LONG_PTR)this);

    ShowWindow((HWND)m_handle,SW_SHOW);
    UpdateWindow((HWND)m_handle);

    //Creating an OpenGl Render Context
    auto hDC=GetDC(HWND(m_handle));

    int pixelFormatAttributes[]={
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };

    int pixelFormat=0;
    UINT numFormats=0;

    wglChoosePixelFormatARB(hDC,pixelFormatAttributes,nullptr,1,&pixelFormat,&numFormats);
    assert(numFormats);

    PIXELFORMATDESCRIPTOR pixelFormatDesc={};
    DescribePixelFormat(hDC, pixelFormat,sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);
    SetPixelFormat(hDC, pixelFormat, &pixelFormatDesc);

    int OpenGLAttributes[]={
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    m_context = wglCreateContextAttribsARB(hDC, 0, OpenGLAttributes);
    assert(m_context);
}
    

OWindow::~OWindow()
{
    wglDeleteContext(HGLRC(m_context));
    DestroyWindow((HWND)m_handle);
}

void OWindow::makeCurrentContext()
{
    wglMakeCurrent(GetDC(HWND(m_handle)),HGLRC(m_context));
}

void OWindow::present(bool vsync)
{
    wglSwapIntervalEXT(vsync);
    wglSwapLayerBuffers(GetDC(HWND(m_handle)),WGL_SWAP_MAIN_PLANE);
}

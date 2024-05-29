#include<OGraphicsEngine.hpp>
#include<glad.h>
#include<glad_wgl.h>
#include<Windows.h>
#include<cassert>
#include<stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
	WNDCLASSEX wc={};
	wc.cbSize=sizeof(WNDCLASSEX);
	wc.lpszClassName=(LPCSTR)"NOT A VWINDOW";
	wc.lpfnWndProc=DefWindowProc;
	wc.style=CS_OWNDC;
	
	auto classId=RegisterClassEx(&wc);
	//auto classId=ResgisterClassEx(&wc);
	assert(classId);
	
	auto hiddenWindow=CreateWindowEx(
	NULL,
	MAKEINTATOM(classId),
	(LPCSTR)"",
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
	CW_USEDEFAULT, CW_USEDEFAULT,
	CW_USEDEFAULT, CW_USEDEFAULT,
	NULL, NULL, NULL, NULL);
	
	assert(hiddenWindow);
	auto hDC=GetDC(hiddenWindow);
	
	PIXELFORMATDESCRIPTOR pixelFormatD={};
	pixelFormatD.nSize=sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatD.nVersion=1;
	pixelFormatD.iPixelType=PFD_TYPE_RGBA;
	pixelFormatD.dwFlags=PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatD.cColorBits=32;
	pixelFormatD.cAlphaBits=8;
	pixelFormatD.cDepthBits=24;
	pixelFormatD.cStencilBits=8;
	pixelFormatD.iLayerType=PFD_MAIN_PLANE;
	
	auto pixelFormat=ChoosePixelFormat(hDC, &pixelFormatD);
	SetPixelFormat(hDC, pixelFormat, &pixelFormatD);
	
	auto hiddenContext=wglCreateContext(hDC);
	assert(hiddenContext);
	
	wglMakeCurrent(hDC,hiddenContext);

	if(!gladLoadWGL(hDC))
		throw std::runtime_error("OGraphics Engine - Error - gladLoadWGL failed");
	
	if(!gladLoadGL())
		throw std::runtime_error("OGraphics Engine - Error - gladLoadGL failed");

	wglMakeCurrent(hDC,0);
	wglDeleteContext(hiddenContext);
	ReleaseDC(hiddenWindow,hDC);
	DestroyWindow(hiddenWindow);
}

OGraphicsEngine::~OGraphicsEngine()
{
	
}

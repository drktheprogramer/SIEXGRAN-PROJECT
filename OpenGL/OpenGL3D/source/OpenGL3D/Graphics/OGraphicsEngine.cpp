#include<OpenGL3D/Graphics/OGraphicsEngine.hpp>
#include<glad/glad_wgl.h>
#include<glad/glad.h>
#include<cassert>

OGraphicsEngine::OGraphicsEngine()
{
	WNDCLASSEX wc={};
	wc.cbSize=sizeof(WNDXLASSEX);
	wc.lpszClassName=L"NOT A VWINDOW";
	wc.lpfnWndProc=DefWinProc;
	
	auto classId=ResgistClassEx(&wc);
	assert(classId);
	
	auto notVWindow=CreateWindowEx(
	NULL,
	MAKEINTATOM(classId),
	L"",
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
	CW_USEDEFAULT, CW_USEDEFAULT,
	CW_USEDEFAULT, CW_USEDEFAULT,
	NULL, NULL, NULL, NULL);
	
	assert(notVWindow);
	auto notVDC=GetDC(notVWindow);
	
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
	
	auto pixelFormat=ChoosePixelFormat(notVDC, &pixelFormatD);
	SetPixelFormat(notVDC, pixelFormat, &pixelFormatD);
	
	auto notVisibleContext=wglCreateContext(notVDC);
	assert(notVisibleContext);
	
	wglMakeCurrent(notVDC,notVisibleContext);
	
}

OGraphicsEngine::~OGraphicsEngine()
{
	
}
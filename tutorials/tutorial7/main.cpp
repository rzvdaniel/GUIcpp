//-------------------------------------------------------------------
//  main.cpp
//  (C) 2004 Razvan Predescu
//
//  Description:
//  This tutorial shows you how you can embed GUIde into an already 
//  existing Windows - OpenGL application.

//  Original code by:
//  Nicholas Anderson
//  email: ceenda@cee.hw.ac.uk
//  web  : http://www.ceenda.freeserve.co.uk/
//-------------------------------------------------------------------
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "guide/screenembeded.h"
#include "Form1.h"

// Window dimensions
int Width = 800;
int Height = 600;

// GUIde's main object: the TScreen
TScreenEmbeded* Screen = NULL;

// The glu quadric we'll render (a simple cylinder)
GLUquadricObj *quadric = NULL;

// Window procedure
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
// Enable OpenGL
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
// Disable OpenGL
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
// This function is located in winkey.cpp and will translate
// keyboard messages for GUIde
extern TKey TranslateKey(int);

//-------------------------------------------------------------------
//  Init()
//  Initialize a 3D scene and GUIde
//  18-Oct-2004   rzv    created
//-------------------------------------------------------------------
void Init(void)
{
	glShadeModel(GL_SMOOTH);

	// Init the quadric (a 3D cylinder)
	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH); 
	gluQuadricTexture(quadric, GL_TRUE);

	// Create the GUIde's TScreen object. Give to it the dimensions
	// of our screen
	Screen = new TScreenEmbeded;
	Screen->Create(TRect(0, 0, Width, Height), "../res/skins/aqua.xml");

	// Create a simple form
	TForm1* Form1 = new TForm1;
	Form1->Create(NULL, TRect(200, 100, 400, 300), true);
	Form1->SetMain(true);
}

//-------------------------------------------------------------------
//  Exit()
//  18-Oct-2004   rzv    created
//-------------------------------------------------------------------
void Exit(void)
{
	// Delete GUIde's TScreen object. It's no need to delete the 2D
	// controls because GUIde will take care of this thing and 
	// it'll release them safely
	if(Screen != NULL)
		delete Screen;
}

//-------------------------------------------------------------------
//  DrawScene()
//  Render the 3D scene and GUIde
//  18-Oct-2004   rzv    created
//-------------------------------------------------------------------
void DrawScene(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)(Width)/(float)(Height), 0.1f, 500.0); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -15);
	glRotatef(0, 1.0f, 0.0f, 0.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
    glRotatef(0, 0.0f, 0.0f, 1.0f);
	
	// Enable lighting and depth test because GUIde disables them
	glEnable(GL_LIGHTING);	
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	// Just a simple cylinder
	gluCylinder(quadric, 4.0f, 4.0f, 4.0f, 16, 2);

	// Render the GUIde at the top of your 3D scene
	Screen->Render();
}

//-------------------------------------------------------------------
//  WinMain()
//  18-Oct-2004   rzv    created
//-------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow )
{
	WNDCLASS wc;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;
	
	// Register window class
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Opengl";
	RegisterClass(&wc);
	
	// Create main window
	hWnd = CreateWindow("Opengl", "GUIde embeded", 
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
		0, 0, Width, Height,NULL, NULL, hInstance, NULL);

	// Hide mouse cursor; GUIde will render it's own one.
	ShowCursor(FALSE);

	// Enable OpenGL for the window
	EnableOpenGL(hWnd, &hDC, &hRC);
	
	// Init our specific stuff
	Init();
		
	// Program main loop
	while(!bQuit) 
	{
		// Check for messages
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			// Handle or dispatch messages
			if(msg.message == WM_QUIT) 
			{
				bQuit = TRUE;
			} 
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else 
		{
			// Render our scene
			DrawScene(); 
			
			// Swap buffers
			SwapBuffers(hDC); 
		}
		
	}
	
	// Exit application
	Exit();
	
	// Shutdown OpenGL
	DisableOpenGL(hWnd, hDC, hRC);
	
	// Destroy the window explicitly
	DestroyWindow(hWnd);

	// Show mouse cursor
	ShowCursor(TRUE);

	return msg.wParam;	
}

//-------------------------------------------------------------------
//  WndProc()
//  18-Oct-2004   rzv    created
//-------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TMessage msg;

	switch(message) 
	{	
		case WM_CREATE:
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_DESTROY:
			return 0;
		case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDBLCLK:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:     
			switch(message) 
			{
				case WM_LBUTTONDBLCLK:
                case WM_RBUTTONDBLCLK:
                case WM_MBUTTONDBLCLK:
					msg.Msg	= CM_MOUSEDBLCLCK;
					break;
				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
				case WM_MBUTTONDOWN:
					SetCapture(hWnd);
					msg.Msg	= CM_MOUSEDOWN;
					break;
				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
				case WM_MBUTTONUP:
					ReleaseCapture();
					msg.Msg	= CM_MOUSEUP;
					break;
			}
			msg.WParam	= wParam;
			msg.LParam	= lParam;  
            break;
        case WM_MOUSEMOVE:
            msg.Msg	= CM_MOUSEMOVE;
			msg.WParam	= wParam;
			msg.LParam	= lParam; 
            break;
		case WM_CHAR:
			msg.Msg		= CM_CHAR;
			msg.WParam	= wParam;
            break;
		case WM_KEYDOWN:
			msg.Msg		= CM_KEYDOWN;
			msg.LParam	= TranslateKey((int)wParam);

			// We want to exit when the ESC key is pressed
			if(wParam == VK_ESCAPE)
				PostQuitMessage(0); 

            break;
		case WM_KEYUP:
			msg.Msg		= CM_KEYUP;
			msg.LParam	= TranslateKey((int)wParam);
            break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );	
	}

	// Pass the input to the TScreen object
	if(Screen != NULL)
		Screen->HandleInputMessage(&msg);

	return 1;
}

//-------------------------------------------------------------------
//  EnableOpenGL()
//  18-Oct-2004   rzv    created
//-------------------------------------------------------------------
void EnableOpenGL( HWND hWnd, HDC * hDC, HGLRC * hRC )
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;
	
	// get the device context (DC)
	*hDC = GetDC(hWnd);
	
	// set the pixel format for the DC
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(*hDC, &pfd);
	SetPixelFormat(*hDC, iFormat, &pfd);
	
	// Create and enable the render context (RC)
	*hRC = wglCreateContext(*hDC);
	wglMakeCurrent(*hDC, *hRC);
}

//-------------------------------------------------------------------
//  DisableOpenGL()
//  18-Oct-2004   rzv    created
//-------------------------------------------------------------------
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

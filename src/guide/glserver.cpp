#define N_IMPLEMENTS TGlServer
//-------------------------------------------------------------------
//  glserver.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/glserver.h"
#include "guide/screen.h"
#include "guide/debug.h"

extern TKey TranslateKey(int);

//-------------------------------------------------------------------
//  CheckError()
//  26-Nov-98   floh    created
//-------------------------------------------------------------------
inline static void CheckError(void)
{
    GLenum error;
    while ((error=glGetError()) != GL_NO_ERROR) {
        t_printf("GL error: %s\n", gluErrorString(error));
    }
}

//-------------------------------------------------------------------
//  TGlServer()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
TGlServer::TGlServer()
{
    ClearBufferBit = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
}

//-------------------------------------------------------------------
//  ~TGlServer()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
TGlServer::~TGlServer()
{
}

//-------------------------------------------------------------------
//  HandleEvent()
//  19-Oct-2004   rzv    created
//-------------------------------------------------------------------
bool TGlServer::HandleEvent(SDL_Event *event)
{
	TMessage msg;
	switch(event->type) 
	{
		case SDL_MOUSEMOTION:
			msg.Msg	= CM_MOUSEMOVE;
			msg.LParam	= T_MAKELONG(event->motion.x, event->motion.y); 
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP: 
			if(event->button.state == SDL_PRESSED)
				msg.Msg	= CM_MOUSEDOWN;
			else
				msg.Msg	= CM_MOUSEUP;
			msg.LParam	= T_MAKELONG(event->motion.x, event->motion.y);
			msg.WParam	= event->key.state;
			break;
	    case SDL_KEYDOWN:
			if(event->key.keysym.sym >= 32 && event->key.keysym.sym <= 126)
			{	
				msg.Msg	= CM_CHAR;
				if ((event->key.keysym.unicode & 0xFF80) == 0)
					msg.WParam = event->key.keysym.unicode & 0x7F;
			}
			else
			{
				msg.Msg	= CM_KEYDOWN;
				msg.LParam	= TranslateKey((int)event->key.keysym.sym);
			}
			break;
		case SDL_KEYUP:
			msg.Msg		= CM_KEYUP;
			msg.LParam	= TranslateKey((int)event->key.keysym.sym);
			break;
	    case SDL_QUIT:
			QuitRequested = true;
			break;
	}

	// Pass the input to the TScreen object
	TScreen::Singleton->HandleInputMessage(&msg);

	return(QuitRequested);
}

//-------------------------------------------------------------------
/**
	@brief One loop rendering and message handling.
*/
//-------------------------------------------------------------------
void TGlServer::Loop(void)
{
	// Paint everything
	Begin();
	TScreen::Singleton->CMPaint();
	End();	

	// Swap OpenGL buffers
	SDL_GL_SwapBuffers();

	// Check for error conditions
	GLenum gl_error = glGetError();
	if(gl_error != GL_NO_ERROR)
		t_printf("testgl: OpenGL error: %d\n", gl_error);

	// Print SDL errors
	char* sdl_error = SDL_GetError();
	if(sdl_error[0] != '\0') 
	{
		t_printf("testgl: SDL error '%s'\n", sdl_error);
		SDL_ClearError();
	}

	// Check if there is s a pending event
	SDL_Event event;
	while(SDL_PollEvent(&event)) 
	{
		HandleEvent(&event);
	}
}

//-------------------------------------------------------------------
//  Run()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TGlServer::Run(void)
{
	// Loop until done
	while(!QuitRequested) 
	{
	    Loop();
	}
}

//-------------------------------------------------------------------
//  Idle()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TGlServer::Idle(void)
{
	Loop();
}

//-------------------------------------------------------------------
//  OpenDisplay()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
bool TGlServer::OpenDisplay(void)
{
	int done = 0;

	// Initialize SDL video
	if(SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		t_printf("Couldn't initialize SDL: %s\n",SDL_GetError());
		return false;
	}

	// tell SDL that the GL drawing is going to be double buffered 
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); 
	// size of depth buffer 
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, BitsPerPixel); 
	// we aren't going to use the stencil buffer 
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 0);
	// this and the next three lines set the bits allocated per pixel for the accumulation buffer to 0
    SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 0); 
    SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 0);
    SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 0); 
    SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 0); 

	unsigned int VideoMode;
	if(Fullscreen == true)
		VideoMode = SDL_OPENGL | SDL_FULLSCREEN;
	else
		VideoMode = SDL_OPENGL;

	// Set video mode
	if(SDL_SetVideoMode( Width, Height, BitsPerPixel, VideoMode ) == NULL) 
	{
		t_printf("Could not set GL mode: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}
	
	// Set the window manager title bar
	SDL_WM_SetCaption("GUIde", "guide");

	// Hide mouse cursor because GUIde will render its own one
	SDL_ShowCursor(0);

	// Enable unicode characters
	SDL_EnableUNICODE(true);

	// Enable keyboard repeat
	SDL_EnableKeyRepeat(500, 30);

    return true;
}

//-------------------------------------------------------------------
//  CloseDisplay()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TGlServer::CloseDisplay(void)
{
	// Show mouse cursor
	SDL_ShowCursor(1);
	
	// Destroy our GL context, etc
	SDL_Quit();
}

//-------------------------------------------------------------------
//  Begin()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TGlServer::Begin(void)
{
    glClear(ClearBufferBit);
    glClearColor(ClearColor[0], ClearColor[1], ClearColor[2], ClearColor[3]);
	glViewport(0, 0, Width, Height);
	
	// Always have filled polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// "An optimum compromise that allows all primitives to be 
	// specified at integer positions, while still ensuring 
	// predictable rasterization, is to translate x and y by 0.375, 
	// as shown in the following code fragment. Such a translation 
	// keeps polygon and pixel image edges safely away from the 
	// centers of pixels, while moving line vertices close enough 
	// to the pixel centers." - Red Book

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Width, Height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.375f, 0.375f, 0.0);

	glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	/*
	glEnable(GL_CLIP_PLANE0);
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE2);
	glEnable(GL_CLIP_PLANE3); 
	*/
}

//-------------------------------------------------------------------
//  End()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TGlServer::End(void)
{
	/*
    glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_CLIP_PLANE2);
	glDisable(GL_CLIP_PLANE3);
	*/
}

//-------------------------------------------------------------------
//  BeginScene()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TGlServer::BeginScene(void)
{
    // "An optimum compromise that allows all primitives to be 
	// specified at integer positions, while still ensuring 
	// predictable rasterization, is to translate x and y by 0.375, 
	// as shown in the following code fragment. Such a translation 
	// keeps polygon and pixel image edges safely away from the 
	// centers of pixels, while moving line vertices close enough 
	// to the pixel centers." - Red Book
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
    
	/*
	glEnable(GL_CLIP_PLANE0);
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE2);
	glEnable(GL_CLIP_PLANE3);
	*/

	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, Width, Height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.375f, 0.375f, 0.0);
}

//-------------------------------------------------------------------
//  EndScene()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TGlServer::EndScene(void)
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
	glMatrixMode(GL_PROJECTION);
    glPopMatrix();
	
	/*
	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_CLIP_PLANE2);
	glDisable(GL_CLIP_PLANE3);
	*/
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

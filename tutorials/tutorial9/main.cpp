//-------------------------------------------------------------------
//  main.cpp
//  (C) 2004 Ricas -- R.Predescu
//
//  Description:
//  This tutorial shows you how you can embed GUIde into an already 
//  existing SDL application, in a nice way. It looks as the previous
//  tutorial, with the difference that our main form has the screen
//  dimensions and it is invisible. This will let users to see the 
//  3D scene behind it, without any restrictions in rendering the gui.
//-------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sdl/SDL.h"
#include "sdl/SDL_opengl.h"
#include "guide/screenembeded.h"
#include "Form1.h"

// GUIde's main object: the TScreen
TScreenEmbeded* Screen = NULL;

// The glu quadric we'll render (a simple cylinder)
GLUquadricObj *quadric = NULL;

// Window dimensions
int Width = 800;
int Height = 600;

// This function is located in sdlkey.cpp and will translate
// keyboard messages for GUIde
extern TKey TranslateKey(int);

//-------------------------------------------------------------------
//  Init()
//  Initialize a 3D scene and GUIde
//  19-Oct-2004   rzv    created
//-------------------------------------------------------------------
void Init(void)
{
	// Init the quadric (a 3D cylinder)
	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH); 
	gluQuadricTexture(quadric, GL_TRUE);

	// Create the GUIde's TScreen object. Give to it the dimensions
	// of our screen
	Screen = new TScreenEmbeded;
	Screen->Create(TRect(0, 0, Width, Height), "../res/skins/aqua.xml");

	// Create the main form, without any caption
	TForm1* Form1 = new TForm1;
	Form1->Create(NULL, TRect(0, 0, Width, Height), false);
	Form1->SetMain(true);
}

//-------------------------------------------------------------------
//  Exit()
//  19-Oct-2004   rzv    created
//-------------------------------------------------------------------
void Exit(void)
{
	// Delete GUIde's TScreen object. It's no need to delete the
	// controls because GUIde will take care of them
	if(Screen != NULL)
		delete Screen;
}

//-------------------------------------------------------------------
//  DrawScene()
//  Render the 3D scene and GUIde
//  19-Oct-2004   rzv    created
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
//  HandleEvent()
//  19-Oct-2004   rzv    created
//-------------------------------------------------------------------
int HandleEvent(SDL_Event *event)
{
	int done = 0;
	TMessage msg;
	switch(event->type) 
	{
		case SDL_MOUSEMOTION:
			msg.Msg	= CM_MOUSEMOVE;
			msg.LParam	= MAKELONG(event->motion.x, event->motion.y); 
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP: 
			if(event->button.state == SDL_PRESSED)
				msg.Msg	= CM_MOUSEDOWN;
			else
				msg.Msg	= CM_MOUSEUP;
			msg.LParam	= MAKELONG(event->motion.x, event->motion.y); 
			break;
	    case SDL_KEYDOWN:
			msg.Msg		= CM_KEYDOWN;
			msg.LParam	= TranslateKey((int)event->key.keysym.sym);
			
			// We want to exit when the ESC key is pressed
			if(event->key.keysym.sym == SDLK_ESCAPE)
				done = 1;			
			break;
		case SDL_KEYUP:
			msg.Msg		= CM_KEYUP;
			msg.LParam	= TranslateKey((int)event->key.keysym.sym);
			break;
	    case SDL_QUIT:
			done = 1;
			break;
	}

	// Pass the input to the TScreen object
	if(Screen != NULL)
		Screen->HandleInputMessage(&msg);

	return(done);
}

//-------------------------------------------------------------------
//  Run()
//  19-Oct-2004   rzv    created
//-------------------------------------------------------------------
int Run(void)
{
	int done = 0;

	// Initialize SDL video
	if(SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		fprintf(stderr,"Couldn't initialize SDL: %s\n",SDL_GetError());
		exit(1);
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );    // tell SDL that the GL drawing is going to be double buffered 
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16);      // size of depth buffer 
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 0);     // we aren't going to use the stencil buffer 
    SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 0);   // this and the next three lines set the bits allocated per pixel - 
    SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 0); // - for the accumulation buffer to 0 
    SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 0); 
    SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 0); 
	
	// Set video mode
	if(SDL_SetVideoMode( Width, Height, 16, SDL_OPENGL ) == NULL) 
	{
		fprintf(stderr, "Couldn't set GL mode: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	
	// Set the window manager title bar
	SDL_WM_SetCaption("SDL GL test", "testgl");

	// Hide mouse cursor because GUIde will render its own one
	SDL_ShowCursor(0);

	// Initilize our specific stuff
	Init();
	
	// Loop until done
	while(!done) 
	{
		// Render our scene
		DrawScene();

		// Swap OpenGL buffers
		SDL_GL_SwapBuffers();

		// Check for error conditions
		GLenum gl_error = glGetError();
		if(gl_error != GL_NO_ERROR)
			fprintf( stderr, "testgl: OpenGL error: %d\n", gl_error);

		// Print SDL errors
		char* sdl_error = SDL_GetError();
		if(sdl_error[0] != '\0') 
		{
			fprintf(stderr, "testgl: SDL error '%s'\n", sdl_error);
			SDL_ClearError();
		}

		// Check if there's a pending event
		SDL_Event event;
		while(SDL_PollEvent(&event)) 
		{
			done = HandleEvent(&event);
		}
	}

	// Clean up our specific stuff
	Exit();

	// Destroy our GL context, etc
	SDL_Quit();

	return(0);
}

//-------------------------------------------------------------------
//  Run()
//  19-Oct-2004   rzv    created
//-------------------------------------------------------------------
int main(int argc, char *argv[])
{
 	Run();

	return 0;
}
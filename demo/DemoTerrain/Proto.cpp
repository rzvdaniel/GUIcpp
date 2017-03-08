//-------------------------------------------------------------------
//  CProto.cpp
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------
#ifdef WIN32
#include <time.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Proto.h"

//-------------------------------------------------------------------
//  CProto()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
CProto::CProto()
{
	Camera = NULL;
	Terrain = NULL;
}

//-------------------------------------------------------------------
//  ~CProto()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
CProto::~CProto()
{
	if(Terrain != NULL)
		delete Terrain;

	if(Camera != NULL)
		delete Camera;
}

//-------------------------------------------------------------------
//  Init()
//  14-March-2004   E    created
//-------------------------------------------------------------------
void CProto::Init(void)
{
	// Create the camera
	Camera = new CCamera;
	Camera->Move(ROTATE, 0);

	//srand(224);
	// Create and initialiaze the terrain
	Terrain = new CTerrain;
	Terrain->CreateFractal();
	//srand((unsigned)time(NULL));

	// OpenGL specific
	float FogColor[] = {0.75, 0.75, 1.0, 1.0};
	glFogi(GL_FOG_MODE, GL_LINEAR);
  	glFogfv(GL_FOG_COLOR, FogColor);
	glFogf(GL_FOG_DENSITY, 1.0);
	glFogf(GL_FOG_START, 8*COMP);
	glFogf(GL_FOG_END, 16*COMP);		
}

//-------------------------------------------------------------------
//  Render()
//  14-March-2004   E    created
//-------------------------------------------------------------------
void CProto::Render(int DisplayWidth, int DisplayHeight)
{
	// Prepare matrices
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)DisplayWidth/(float)DisplayHeight, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Camera->xpos, Camera->ypos, Camera->zpos, 
		Camera->xpos + Camera->lookx, 
		Camera->ypos + Camera->looky, 
		Camera->zpos + Camera->lookz, 
		0.0, 1.0, 0.0);
	
	// Enable depth testing and fog
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG);

	// Render terrain
	Terrain->Render(Camera->lookx, Camera->lookz, Camera->xpos, Camera->zpos);
	
	// Update camera position
	Camera->Move(FORWARD, Camera->speed);
	Camera->ypos = Terrain->GetHeight(Camera->xpos, Camera->zpos) + Camera->height;
	
	// No need for depth test and fog anymore
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

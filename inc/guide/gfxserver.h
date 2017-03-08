#ifndef T_GFXSERVER_H
#define T_GFXSERVER_H
//-------------------------------------------------------------------
/**
	@class TGfxServer
	@brief Abstract graphic server.

	This class is the base class for graphic servers the gui could
	use to render its graphics. It contains only pure virtual 
	methods that will be implemented in derrived classes. For example, 
	TGlServer is the OpenGL graphic server on top of TGfxServer. 
	
	Few of the most important methods:
	
	<code> OpenDisplay(), CloseDisplay() </code>
	- Functions to open and close a display.

	<code> Run() </code> 
	- Main rendering loop.

	<code> Begin(), End() </code> 
	- Prepare and finalize scene to render the gui in independent applications.

	<code> BeginScene(), EndScene() </code> 
	- Prepare and finalize scene to render the gui in embeded applications.

	@author Razvan Predescu
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TGfxServer
#include "guide/ndefdllclass.h"

#ifndef T_MATHLIB_H
#include "guide/mathlib.h"
#endif

#ifndef T_OSINCLUDES_H
#include "guide/osincludes.h"
#endif

//-------------------------------------------------------------------

class N_PUBLIC TGfxServer 
{
public:
    bool QuitRequested;
    int BitsPerPixel;
	bool Fullscreen;
	float ClearColor[4];
	int Width;
	int Height;
	
public:
	TGfxServer();
	virtual ~TGfxServer();
	
	virtual bool OpenDisplay(void) = 0;
	virtual void CloseDisplay(void) = 0;
	
	virtual void Run(void) = 0;
	virtual void Idle(void) = 0;
	virtual void Close(void);
		
	virtual void Begin(void) = 0;
	virtual void End(void) = 0;
	
	virtual void BeginScene(void) = 0;
	virtual void EndScene(void) = 0;
};
                                                                   
//-------------------------------------------------------------------
#endif


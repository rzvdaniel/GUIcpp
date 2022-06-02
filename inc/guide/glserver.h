#ifndef T_GLSERVER_H
#define T_GLSERVER_H
//-------------------------------------------------------------------
/**
	@class TGlServer
	@brief Implementation of the base class TGfxServer that uses OpenGL
	API to render visual aspects of the gui.

	This class is responsible to open and close a display, running 
	application's mai rendering loop, preparing and finishing a scene
	for drawing, all of these using OpenGL API. Take a look at
	TGfxServer class for a description of its methods.
	
	@see <code>TGfxServer</code>

	@author Razvan Predescu
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TGlServer
#include "guide/ndefdllclass.h"

#ifndef T_GFXSERVER_H
#include "guide/gfxserver.h"
#endif

#include "SDL.h"
#include "SDL_opengl.h"

//-------------------------------------------------------------------

class N_PUBLIC TGlServer : public TGfxServer
{
    long ClearBufferBit;
	SDL_Window* window;

public:
	TGlServer();
	virtual ~TGlServer();
	
	void SetClearBufferBit(long Value) { ClearBufferBit = Value; }
	long GetClearBufferBit(void) const { return ClearBufferBit; }
	
	virtual bool OpenDisplay(void);
	virtual void CloseDisplay(void);
	
	virtual void Run(void);
	virtual void Idle(void);
		
	virtual void Begin(void);
	virtual void End(void);
	
	virtual void BeginScene(void);
	virtual void EndScene(void);
	
private:
	bool HandleEvent(SDL_Event *event);
	void Loop(void);
};
                                                                   
//-------------------------------------------------------------------
#endif


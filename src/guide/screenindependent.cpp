#define N_IMPLEMENTS TScreenIndependent
//-------------------------------------------------------------------
//  screenindependent.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/screenindependent.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TScreenIndependent()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
TScreenIndependent::TScreenIndependent()
{
}

//-------------------------------------------------------------------
//  ~TScreenIndependent()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
TScreenIndependent::~TScreenIndependent()
{
	GetGfxServer()->CloseDisplay();
}

//-------------------------------------------------------------------
//  Create()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
bool TScreenIndependent::Create(const TRect& Rect, int Bpp, bool Full, const char* SkinFile)
{
	TScreen::Create(Rect);
	
	// GfxServer was previously created by TScreen::Create() function, so we can use it safely
	GetGfxServer()->BitsPerPixel = Bpp;
	GetGfxServer()->Fullscreen = Full;

	// Open the display
	if(!OpenDisplay(Full))
		return false;

	// Load the skin
	if(!LoadSkin(SkinFile))
		return false;

	return true;
}

//-------------------------------------------------------------------
//  Close()
//  22-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreenIndependent::Close(void)
{
	GetGfxServer()->QuitRequested = true;
}

//-------------------------------------------------------------------
//  OpenDisplay()
//  02-Aug-2003   rzv   created
//-------------------------------------------------------------------
bool TScreenIndependent::OpenDisplay(bool IsFullscreen)
{
	// Open the display
	return GetGfxServer()->OpenDisplay();
}

//-------------------------------------------------------------------
//  CloseDisplay()
//  02-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreenIndependent::CloseDisplay(void)
{
    GetGfxServer()->QuitRequested = true;
}

//-------------------------------------------------------------------
//  Run()
//  20-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreenIndependent::Run(void)
{
	GetGfxServer()->Run();
}

//-------------------------------------------------------------------
//  Idle()
//  07-Jan-2004   rzv   created
//-------------------------------------------------------------------
void TScreenIndependent::Idle(void)
{
	GetGfxServer()->Idle();
}


//-------------------------------------------------------------------
//  Render()
//  29-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TScreenIndependent::Render(void)
{
	t_error("Pure virtual function called.");
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

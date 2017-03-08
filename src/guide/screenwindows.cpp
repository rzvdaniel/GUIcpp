#define N_IMPLEMENTS TScreenWindows
//-------------------------------------------------------------------
//  screenwindows.cpp
//  (C) 2003 R.Predescu   
//-------------------------------------------------------------------
#include "guide/screenwindows.h"
#include "guide/skin.h"
#include "guide/debug.h"

#ifdef __WIN32__
extern TKey TranslateKey(int);

//-------------------------------------------------------------------
//  TScreenWindows()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
TScreenWindows::TScreenWindows()
{	
}

//-------------------------------------------------------------------
//  ~TScreenWindows()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
TScreenWindows::~TScreenWindows()
{
	GetGfxServer()->CloseDisplay();
}

//-------------------------------------------------------------------
//  Create()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreenWindows::Create(const TRect& Rect, int Bpp, bool Full, const char* SkinFile)
{	
	TScreenIndependent::Create(Rect, Bpp, Full, SkinFile);

	// Open the display
	GetGfxServer()->OpenDisplay();

	// Create and load the skin
	Skin = new TSkin;
	Skin->Load(SkinFile);

	// Set the default font
	SetFont(Skin->GetDefaultFont());
	// Set the default mouse cursor
	SetMouseCursor(Skin->GetDefaultMouseCursor());
}

//-------------------------------------------------------------------
//  Close()
//  22-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreenWindows::Close(void)
{
	GetGfxServer()->QuitRequested = true;
}

//-------------------------------------------------------------------
//  Run()
//  20-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreenWindows::Run(void)
{	
	GetGfxServer()->Run();
}

//-------------------------------------------------------------------
//  Idle()
//  07-Jan-2004   rzv   created
//-------------------------------------------------------------------
void TScreenWindows::Idle(void)
{
	GetGfxServer()->Idle();
}

//-------------------------------------------------------------------
//  SetMousePosition()
//  23-March-2004   rzv   created
//-------------------------------------------------------------------
void TScreenWindows::SetMousePosition(int X, int Y)
{
	::SetCursorPos(X, Y);
}

#endif
//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

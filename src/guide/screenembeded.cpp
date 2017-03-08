#define N_IMPLEMENTS TScreenEmbeded
//-------------------------------------------------------------------
//  screenembeded.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/screenembeded.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TScreenEmbeded()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
TScreenEmbeded::TScreenEmbeded()
{	
}

//-------------------------------------------------------------------
//  ~TScreenEmbeded()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
TScreenEmbeded::~TScreenEmbeded()
{	 
}

//-------------------------------------------------------------------
//  Create()
//  01-Aug-2003   rzv   created
//-------------------------------------------------------------------
bool TScreenEmbeded::Create(const TRect& Rect, const char* SkinFile)
{
	TScreen::Create(Rect);
	
	// Load the skin
	if(!LoadSkin(SkinFile))
		return false;

	return true;
}

//-------------------------------------------------------------------
//  Render()
//  04-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TScreenEmbeded::Render(void)
{
	GetGfxServer()->BeginScene();

	// Paint everything
	CMPaint();
	
	GetGfxServer()->EndScene();
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

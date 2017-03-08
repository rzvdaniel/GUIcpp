#define N_IMPLEMENTS TMouseCursor
//-------------------------------------------------------------------
//  mousecursor.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/mousecursor.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TMouseCursor()
//  29-June-2003   rzv   created
//-------------------------------------------------------------------
TMouseCursor::TMouseCursor()
{
	Texture = NULL;
	Width = 0;
	Height = 0;
}

//-------------------------------------------------------------------
//  ~TMouseCursor()
//  29-June-2003   rzv   created
//-------------------------------------------------------------------
TMouseCursor::~TMouseCursor()
{
	if(Texture != NULL)
		delete Texture;
}

//-------------------------------------------------------------------
//  Create()
//  29-June-2003   rzv   created
//-------------------------------------------------------------------
void TMouseCursor::Create(const char* Filename, const TPoint& AHotspot)
{
	SetImage(Filename);
	Hotspot = AHotspot;
}

//-------------------------------------------------------------------
//  Create()
//  13-Mar-2004   rzv   created
//-------------------------------------------------------------------
void TMouseCursor::Create(TString Filename, const TPoint& AHotspot)
{
	Create(Filename.c_str(), AHotspot);
}

//-------------------------------------------------------------------
//  SetImage()
//  06-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TMouseCursor::SetImage(TString Filename)
{
	Image.assign(Filename);

	if(Texture != NULL)
	{
		delete Texture;
		Texture = NULL;
	}

	Texture = new TTexture;
	Texture->Load(Image.c_str());

	Width = Texture->GetPicture()->GetWidth();
	Height = Texture->GetPicture()->GetHeight();
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


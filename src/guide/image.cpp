#define N_IMPLEMENTS TImage
//-------------------------------------------------------------------
//  image.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/image.h"
#include "guide/texture.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TImage()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
TImage::TImage()
{
	Texture = NULL;
	AutoSize = false;
	Display = idNormal;
}

//-------------------------------------------------------------------
//  ~TImage()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
TImage::~TImage()
{
	if(Texture != NULL)
		delete Texture;
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TImage::Create(TComponent* AOwner, const TRect& Rect)
{
	TControl::Create(AOwner, Rect);

	SetColor(0xEEFFFFFF);
}

//-------------------------------------------------------------------
//  SetAutoSize()
//  06-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TImage::SetAutoSize(bool Value) 
{ 
	AutoSize = Value;
	
	if(AutoSize == true)
		Display = idNormal;
}

//-------------------------------------------------------------------
//  LoadPicture()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
void TImage::LoadPicture(const char* Filename)
{
	if(Texture != NULL)
	{
		delete Texture;
		Texture = NULL;
	}

	Texture = new TTexture;
	Texture->Load(Filename);

	Canvas->Brush->SetTexture(Texture);
}

//-------------------------------------------------------------------
//  LoadPicture()
//  15-Mar-2004   rzv   created
//-------------------------------------------------------------------
void TImage::LoadPicture(TString Filename)
{
	LoadPicture(Filename.c_str());
}

//-------------------------------------------------------------------
//  OnPaint()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
void TImage::OnPaint(void)
{	
	Canvas->Brush->SetColor(GetColor());
	Canvas->FillRect(0, 0, GetWidth(), GetHeight());

	TControl::OnPaint();
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



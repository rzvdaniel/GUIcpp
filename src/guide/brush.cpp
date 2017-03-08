#define N_IMPLEMENTS TBrush
//-------------------------------------------------------------------
//  brush.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/brush.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TBrush()
//  06-July-2002   rzv   created
//-------------------------------------------------------------------
TBrush::TBrush()
{	
	Color	 = clWhite;
    Style	 = bsSolid;
    Texture  = NULL;	
	TextureU = 1.0f;
	TextureV = 1.0f;
	TextureOffsetU = 0.0f;
	TextureOffsetV = 0.0f;
}

//-------------------------------------------------------------------
//  ~TBrush()
//  06-July-2002   rzv   created
//-------------------------------------------------------------------
TBrush::~TBrush()
{
}

//-------------------------------------------------------------------
//  ~SetTextureUV()
//  23-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TBrush::SetTextureUV(float U, float V)
{
	TextureU = U;
	TextureV = V;
}

//-------------------------------------------------------------------
//  GetTextureUV()
//  23-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TBrush::GetTextureUV(float &U, float &V)
{
	U = TextureU;
	V = TextureV;
}

//-------------------------------------------------------------------
//  SetTextureOffsetUV()
//  28-Oct-2003   rzv   created
//-------------------------------------------------------------------
void TBrush::SetTextureOffsetUV(float U, float V)
{
	TextureOffsetU = U;
	TextureOffsetV = V;
}

//-------------------------------------------------------------------
//  GetTextureOffsetUV()
//  28-Oct-2003   rzv   created
//-------------------------------------------------------------------
void TBrush::GetTextureOffsetUV(float &U, float &V)
{
	U = TextureOffsetU;
	V = TextureOffsetV;
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


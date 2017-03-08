#ifndef T_BRUSH_H
#define T_BRUSH_H
//-------------------------------------------------------------------
//  CLASS
//  TBrush
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TBrush
#include "guide/ndefdllclass.h"

#ifndef T_MATHLIB_H
#include "guide/mathlib.h"
#endif

#ifndef T_GRAPHICS_H
#include "guide/graphics.h"
#endif

#ifndef T_TEXTURE_H
#include "guide/texture.h"
#endif

//-------------------------------------------------------------------

enum TBrushStyle { bsSolid, bsClear, bsHorizontal, bsVertical, 
			       bsFDiagonal, bsBDiagonal, bsCross, bsDiagCross };

//-------------------------------------------------------------------

class N_PUBLIC TBrush  
{
	TColor Color;
	TBrushStyle Style;
	TTexture* Texture;
	float TextureU;
	float TextureV;
	float TextureOffsetU;
	float TextureOffsetV;

public:
	TBrush();
	virtual ~TBrush();

	TColor GetColor(void) const { return Color; }
	void SetColor(TColor Value) { Color = Value; }

	TBrushStyle GetStyle(void) const { return Style; }
	void SetStyle(TBrushStyle Value) { Style = Value; } 

	TTexture* GetTexture(void) const { return Texture; }
	void SetTexture(TTexture* ATexture) { Texture = ATexture; }

	float GetTextureU(void) const { return TextureU; }
	float GetTextureV(void) const { return TextureV; }
	void SetTextureUV(float U, float V);
	void GetTextureUV(float &U, float &V);

	void SetTextureOffsetUV(float U, float V);
	void GetTextureOffsetUV(float &U, float &V);
	float GetTextureOffsetU(void) const { return TextureOffsetU; }
	float GetTextureOffsetV(void) const { return TextureOffsetV; }

};

//-------------------------------------------------------------------
#endif 


#ifndef T_GRIDCELL_H
#define T_GRIDCELL_H
//-------------------------------------------------------------------
//  CLASS
//  TGridCell
//
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TGridCell
#include "guide/ndefdllclass.h"

#ifndef T_OBJECT_H
#include "guide/object.h"
#endif

#ifndef T_MATHLIB_H
#include "guide/mathlib.h"
#endif

#ifndef T_TEXTURE_H
#include "guide/texture.h"
#endif

#ifndef TINYXML_INCLUDED 
#include "tinyxml.h"
#endif

enum TAlignCell { calNone, calLeft, calRight, calClient };
enum TTextureRepeat { trNone, trAll, trHorizontal, trVertical };

//-------------------------------------------------------------------
class TCanvas;
class TGridRow;
class N_PUBLIC TGridCell : public TObject
{	
	int Left;
	int Top;
	int Width; 
	int Height;
	TGridRow* Row;	
	TAlignCell Align;
	TTexture* Texture;
	TTextureRepeat TextureRepeat;
	float TextureU;
	float TextureV;

public:
	TGridCell(TGridRow* ARow);
	virtual ~TGridCell();
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);
    
	TGridRow* GetRow(void) const { return Row; }

	void SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	void SetLeft(int Value);
	int GetLeft(void) const { return Left; }
	void SetTop(int Value);
	int GetTop(void) const { return Top; }
	void SetWidth(int Value);
	int GetWidth(void) const { return Width; }
	void SetHeight(int Value);
	int GetHeight(void) const { return Height; }

	TTextureRepeat GetTextureRepeat(void) const { return TextureRepeat; }
	void SetTextureRepeat(TTextureRepeat Value) { TextureRepeat = Value; }

	TTexture* GetTexture(void) const { return Texture; }
	void SetTexture(TTexture* ATexture) { Texture = ATexture; }

	void SetAlign(TAlignCell Value);
	TAlignCell GetAlign(void) const { return Align; }
	
	void Paint(TCanvas* Canvas);
};

//-------------------------------------------------------------------
#endif

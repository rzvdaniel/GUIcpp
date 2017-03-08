#ifndef T_MOUSECURSOR_H
#define T_MOUSECURSOR_H
//-------------------------------------------------------------------
//  CLASS
//  TMouseCursor
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TMouseCursor
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

//------------------------------------------------------------------------------
class N_PUBLIC TMouseCursor : public TObject
{
	TString	Image;
    TTexture* Texture;
	TPoint Hotspot;
	int Width;
	int	Height;

public:
    TMouseCursor();
    virtual ~TMouseCursor();
	virtual void Create(const char* Filename, const TPoint& AHotspot);
	virtual void Create(TString Filename, const TPoint& AHotspot);
    
	TTexture* GetTexture(void) const { return Texture; } 
	
	void SetImage(TString Filename);
	TString GetImage(void) const { return Image; }
	
	void SetHotspot(TPoint Value) { Hotspot = Value; }
    TPoint GetHotspot(void) const { return Hotspot; } 

	void SetWidth(int Value) { Width = Value; }
	int GetWidth(void) const { return Width; }
	
	void SetHeight(int Value) { Height = Value; }
	int GetHeight(void) const { return Height; }  
};

//-------------------------------------------------------------------
#endif 


#ifndef T_PEN_H
#define T_PEN_H
//-------------------------------------------------------------------
//  CLASS
//  TPen
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TPen
#include "guide/ndefdllclass.h"

#ifndef T_GRAPHICS_H
#include "guide/graphics.h"
#endif

//-------------------------------------------------------------------
enum TPenStyle { psSolid, psDash, psDot, psDashDot, psDashDotDash,
				 psDashDotDot};

//-------------------------------------------------------------------
class N_PUBLIC TPen  
{
	TColor Color;
	TPenStyle Style;
	int	Width;

public:
	TPen();
	virtual ~TPen();

	TColor GetColor(void) const { return Color; }
	void SetColor(TColor Value) { Color = Value; }

	TPenStyle GetStyle(void) const { return Style; }
	void SetStyle(TPenStyle Value) { Style = Value; } 

	int GetWidth(void) const { return Width; }
	void SetWidth(int Value) { Width = Value; }

};
//-------------------------------------------------------------------
#endif

 

#ifndef T_CANVAS_H
#define T_CANVAS_H
//-------------------------------------------------------------------
//  CLASS
//  TCanvas 
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TCanvas
#include "guide/ndefdllclass.h"

#ifndef T_MATHLIB_H
#include "guide/mathlib.h"
#endif

#ifndef T_GRAPHICS_H
#include "guide/graphics.h"
#endif

#ifndef T_BRUSH_H
#include "guide/brush.h"
#endif

#ifndef T_PEN_H
#include "guide/pen.h"
#endif

#ifndef T_STRINGCI_H
#include "string.h"
#endif

//-------------------------------------------------------------------
class TControl;
class N_PUBLIC TCanvas
{	
	TControl* Control;
	TPoint PenPos;
	float TextAntialias;

public:
	TBrush*	Brush;
	TPen* Pen;

public:
	TCanvas(TControl* AControl);
	virtual ~TCanvas();

	TControl* GetControl(void) const { return Control; }	

	void SetPenPos(const TPoint& Point) { PenPos = Point; }
	TPoint GetPenPos(void) const { return PenPos; }
	
	float GetTextWidth(const TString& String);
	float GetTextWidth(const char* String);
	float GetTextHeight(const TString& String);
	float GetTextHeight(const char* String);
	void  SetTextAntialias(float Value) { TextAntialias = Value; }
	float GetTextAntialias(void) const { return TextAntialias; }
	
	void ClipDrawing(void);
	void ClipDrawing(const TRect& Rect);
	void EnableClipping(void);
	void DisableClipping(void);

	void BeginUserScene(void);
	void EndUserScene(void);
	
	bool QueryExtension(char* Extension) const; 

	// Graphic functions

	void Text(float X, float Y, const TString& String);
	void Text(float X, float Y, const char* String);
	void Text3D(float X, float Y, TColor ColorUp, TColor ColorDown, TPoint Offset, const TString& String);
	void Text3D(float X, float Y, TColor ColorUp, TColor ColorDown, TPoint Offset, const char* String);

	void DrawRect(int X, int Y, int CX, int CY, int Width);
	void DrawRect(const TRect &Rect, int Width);
	
	void Draw3DRect(int X, int Y, int CX, int CY, int Width, TColor ClrTopLeft, TColor ClrBottomRight);
	void Draw3DRect(const TRect &Rect, int Width, TColor ClrTopLeft, TColor ClrBottomRight);		
	
	void FillRect(int X, int Y, int CX, int CY);
	void FillRect(const TRect &Rect);
	
	void FillTexturedRect(TTexture* Texture, TColor Color, int X, int Y, int CX, int CY,  
                          float U=1.0f, float V=1.0f, float UOffset=0.0f, float VOffset=0.0f);
	void FillTexturedRect(TTexture* Texture, TColor Color, const TRect &Rect, 
                          float U=1.0f, float V=1.0f, float UOffset=0.0f, float VOffset=0.0f);

	void MoveTo(int X, int Y);
	void LineTo(int X, int Y);
};

//-------------------------------------------------------------------
#endif



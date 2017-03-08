#ifndef T_MAINFORM_H
#define T_MAINFORM_H
//-------------------------------------------------------------------
//  CLASS
//  TMainForm
//
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

#ifndef SBG_MAINSCREEN_H
#include "MainScreen.h"
#endif

#ifndef C_PROTO_H
#include "Proto.h"
#endif

//-------------------------------------------------------------------
class TMainForm : public TForm
{	
	/// Main screen (UI)
	TMainScreen* MainScreen; 
	/// Pointer to the proto object
	CProto* Proto;
	/// Game is started?
	bool GameStarted;
	/// Mouse cursor X 
	int MouseX;
	/// Mouse cursor Y 
	int MouseY;

public:  
    TMainForm();
    virtual ~TMainForm();
	virtual void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
	
	void SetProto(CProto* AProto) { Proto = AProto; }
	CProto* GetProto(void) const { return Proto; }

	bool IsGameStarted(void) const { return GameStarted; }
	void SetGameStarted(bool Value) { GameStarted = Value; }

protected:
	// Events	
	void OnPaint(void);
	void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	void OnKeyDown(unsigned short &Key, const TShiftState& Shift);
	void OnKeyUp(unsigned short &Key, const TShiftState& Shift);
};

//-------------------------------------------------------------------
#endif 
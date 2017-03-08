#ifndef T_SCROLLWINCTRL_H
#define T_SCROLLWINCTRL_H
//-------------------------------------------------------------------
//  CLASS
//  TScrollingWinControl
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TScrollingWinControl
#include "guide/ndefdllclass.h"

#ifndef T_WINCONTROL_H
#include "guide/wincontrol.h"
#endif

#ifndef T_SCROLLBAR_H
#include "guide/scrollbar.h"
#endif

enum TScrollStyle { ssNone, ssHorizontal, ssVertical, ssBoth };

//-------------------------------------------------------------------
class N_PUBLIC TScrollingWinControl : public TWinControl
{		
	/// Specifies whether scroll bars appear automatically on the 
	/// scrolling windowed control if it is not large enough to 
	/// display all of its elements.
	bool AutoScroll;
	/// Determines whether the control has any scroll bars.
	TScrollStyle ScrollStyle;

public:
	/// The horizontal scroll bar
	TScrollBar* HorzScrollBar;
	/// The vertical scroll bar
	TScrollBar* VertScrollBar;

public:
	TScrollingWinControl();
	virtual ~TScrollingWinControl();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	void SetAutoScroll(bool Value) { AutoScroll = Value; }
	bool GetAutoScroll(void) const { return AutoScroll; }

	void SetScrollStyle(TScrollStyle Value);
	TScrollStyle GetScrollStyle(void) const { return ScrollStyle; }

protected:
	// Events
	virtual void OnKeyDown(unsigned short &Key, const TShiftState& Shift);
	virtual void OnKeyUp(unsigned short &Key, const TShiftState& Shift);
	virtual void OnKeyPress(char &Key);

public:
	// Event handlers
};

//-------------------------------------------------------------------
#endif 


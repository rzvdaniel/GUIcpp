#ifndef T_WINCONTROL_H
#define T_WINCONTROL_H
//-------------------------------------------------------------------
/**
	@class TWinControl
	@brief Base class for all the standard windowed controls.

	Windowed controls can receive keyboard input and can be activated 
	and deactivated. Only one active control exists at any time for a 
	control placeholder. 
*/
#undef N_DEFINES
#define N_DEFINES TWinControl
#include "guide/ndefdllclass.h"

#ifndef T_CONTROL_H
#include "guide/control.h"
#endif

typedef CBFunctor2<unsigned short&, TShiftState> TKeyDownEvent;
typedef CBFunctor2<unsigned short&, TShiftState> TKeyUpEvent;
typedef CBFunctor1<char&> TKeyPressEvent;

//-------------------------------------------------------------------
class N_PUBLIC TWinControl : public TControl  
{	
	bool Active;
	TWinControl* ActiveControl;

public:
	TKeyDownEvent FOnKeyDown;
	TKeyUpEvent FOnKeyUp;
	TKeyPressEvent FOnKeyPress;

public:
	TWinControl();
	virtual ~TWinControl();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	void SetVisible(bool Value);
	bool GetActive(void) const { return Active; }
	
	void SetActiveControl(TWinControl* Control);
	TWinControl* GetActiveControl(void) const { return ActiveControl; }

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	virtual void OnKeyDown(unsigned short &Key, const TShiftState& Shift);
	virtual void OnKeyUp(unsigned short &Key, const TShiftState& Shift);
	virtual void OnKeyPress(char &Key);
	virtual void OnSize(int AWidth, int AHeight);
	virtual void OnActivate(void);
	virtual void OnDeactivate(void);

public:
	// Event handlers
	virtual void CMKeyDown(unsigned short &Key, const TShiftState& Shift);
	virtual void CMKeyUp(unsigned short &Key, const TShiftState& Shift);
	virtual void CMKeyPress(char &Key);
	virtual void CMActivate(void);
	virtual void CMDeactivate(void);
};

//-------------------------------------------------------------------
#endif 


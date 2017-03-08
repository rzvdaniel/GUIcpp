#define N_IMPLEMENTS TWinControl
//-------------------------------------------------------------------
//  wincontrol.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/wincontrol.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TWinControl()
//  09-July-2002   rzv   created
//-------------------------------------------------------------------
TWinControl::TWinControl()
{
	ActiveControl = NULL;
	Active = true;
}

//-------------------------------------------------------------------
//  ~TWinControl()
//  09-July-2002   rzv   created
//-------------------------------------------------------------------
TWinControl::~TWinControl()
{
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TWinControl::Create(TComponent* AOwner, const TRect& Rect)
{
	TControl::Create(AOwner, Rect);

	TWinControl* CtrlParent = (TWinControl*)GetParent();
	if(CtrlParent != NULL)
		CtrlParent->SetActiveControl(this);
}

//-------------------------------------------------------------------
//  SetVisible()
//  12-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TWinControl::SetVisible(bool Value) 
{
	TControl::SetVisible(Value);
		
	TWinControl* CtrlParent = (TWinControl*)GetParent();
	if(Value == true)
	{
        BringToFront();
				
		if(CtrlParent != NULL)
			CtrlParent->SetActiveControl(this);
	}
}

//-------------------------------------------------------------------
//  SetActiveControl()
//  10-July-2002   rzv   created
//-------------------------------------------------------------------
void TWinControl::SetActiveControl(TWinControl* Control)
{
	if(Control != NULL && Control->GetEnabled())
	{
		TWinControl* CtrlParent = (TWinControl*)GetParent();
		if(CtrlParent != NULL)
			CtrlParent->SetActiveControl(this);
	
		if(Control != this && Control != ActiveControl) 
		{	
			if(ActiveControl != NULL) 
				ActiveControl->CMDeactivate();
	
			ActiveControl = Control;
			ActiveControl->CMActivate();
		}
	}
	else 
	{
		if(ActiveControl != NULL && ActiveControl->GetEnabled()) 
		{
			ActiveControl->CMDeactivate();
			ActiveControl = NULL;
		}
	}
}

//-------------------------------------------------------------------
//  CMKeyDown()
//  03-Feb-2003   rzv    created
//-------------------------------------------------------------------
void TWinControl::CMKeyDown(unsigned short &Key, const TShiftState& Shift)
{		
	// Send the event to the active control and return imediately
	if(ActiveControl != NULL)
	{
		ActiveControl->CMKeyDown(Key, Shift);
		return;
	}

	OnKeyDown(Key, Shift);
	
	if(FOnKeyDown)
		FOnKeyDown(Key, Shift);
}

//-------------------------------------------------------------------
//  CMKeyUp()
//  03-Feb-2003   rzv    created
//-------------------------------------------------------------------
void TWinControl::CMKeyUp(unsigned short &Key, const TShiftState& Shift)
{	
	// Send the event to the active control and return imediately
	if(ActiveControl != NULL)
	{
		ActiveControl->CMKeyUp(Key, Shift);
		return;
	}
	
	OnKeyUp(Key, Shift);	

	if(FOnKeyUp)
		FOnKeyUp(Key, Shift);
}

//-------------------------------------------------------------------
//  CMKeyPress()
//  03-Feb-2003   rzv    created
//-------------------------------------------------------------------
void TWinControl::CMKeyPress(char& Key)
{		
	// Send the event to the active control and return immediately
	if(ActiveControl != NULL)
	{
		ActiveControl->CMKeyPress(Key);
		return;
	}

	OnKeyPress(Key);
	
	if(FOnKeyPress)
		FOnKeyPress(Key);
}

//-------------------------------------------------------------------
//  CMActivate()
//  18-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TWinControl::CMActivate(void)
{
	OnActivate();
}

//-------------------------------------------------------------------
//  CMDeactivate()
//  18-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TWinControl::CMDeactivate(void)
{
	OnDeactivate();
}

//-------------------------------------------------------------------
//  OnPaint()
//  29-July-2002   rzv    created
//-------------------------------------------------------------------
void TWinControl::OnPaint(void)
{	
	TControl::OnPaint();
	
	// Paint child controls
	TControlsList* ControlsList = GetControls();
	if(ControlsList != NULL)
	{
		PushClipRect();

		TControlsList::iterator iter;
		for(iter = ControlsList->begin(); 
			iter != ControlsList->end(); 
			iter++)
		{
			TControl* Control = (TControl*)(*iter);
			if(Control->GetVisible())
				Control->CMPaint();
		}

		PopClipRect();
	}
	
	// Paint borders
	PaintBorders();

	// Cast shadows
	if(GetCastShadows() == true && Skin->GetShadow() != NULL)
		Skin->GetShadow()->Render(this);
}

//-------------------------------------------------------------------
/**
	The OnKeyDown event occurs when a user presses any key while the 
	control is the active one. 
*/
//-------------------------------------------------------------------
void TWinControl::OnKeyDown(unsigned short &Key, const TShiftState& Shift)
{
}

//-------------------------------------------------------------------
/**
	The OnKeyUp event occurs when a user releases a key that has been 
	pressed.
*/
//-------------------------------------------------------------------
void TWinControl::OnKeyUp(unsigned short& Key, const TShiftState& Shift)
{	
}

//-------------------------------------------------------------------
/**
	The OnKeyPress event occurs when a user presses a single character 
	key.
*/
//-------------------------------------------------------------------
void TWinControl::OnKeyPress(char &Key)
{
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TWinControl::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	if(GetEnabled())
	{
		TWinControl* CtrlParent = (TWinControl*)GetParent();
		if(CtrlParent != NULL)
			CtrlParent->SetActiveControl(this);
	}

	TControl::OnMouseDown(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TWinControl::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TControl::OnMouseUp(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TWinControl::OnMouseMove(const TShiftState& Shift, int X, int Y)
{
	TControl::OnMouseMove(Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnSize()
//  23-March-2004   rzv    created
//-------------------------------------------------------------------
void TWinControl::OnSize(int AWidth, int AHeight)
{
	TControl::OnSize(AWidth, AHeight);
	
	TControlsList* ControlsList = GetControls();
	if(ControlsList != NULL)
	{
		TControlsList::iterator iter;
		for(iter = ControlsList->begin(); 
			iter != ControlsList->end(); 
			iter++)
		{
			TControl* Control = (TControl*)(*iter);
			Control->CMParentResize(AWidth, AHeight);
		}
	}
}

//-------------------------------------------------------------------
/**
	The OnActivate event occurs when a the control becomes the active 
	one.
*/
//-------------------------------------------------------------------
void TWinControl::OnActivate(void)
{
	Active = true;
		
	if(GetControls() != NULL)
	{
		// Reverse iterator for move from the end to the begining of Controls
		TControlsList::reverse_iterator iter;
		for(iter = GetControls()->rbegin(); iter != GetControls()->rend(); iter++)
		{
			TControl* Control = (TControl*)(*iter);
			Control->CMParentActivate();
		}
	}
}

//-------------------------------------------------------------------
/**
	The OnDeactivate event occurs when a the control is deactivated.
*/
//-------------------------------------------------------------------
void TWinControl::OnDeactivate(void)
{
	Active = false;

	if(GetControls() != NULL)
	{
		// Reverse iterator for move from the end to the begining of Controls
		TControlsList::reverse_iterator iter;
		for(iter = GetControls()->rbegin(); iter != GetControls()->rend(); iter++)
		{
			TControl* Control = (TControl*)(*iter);
			Control->CMParentDeactivate();
		}
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

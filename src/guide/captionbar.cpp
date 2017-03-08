#define N_IMPLEMENTS TCaptionBar
//-------------------------------------------------------------------
//  captionbar.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/captionbar.h"
#include "guide/form.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TCaptionBar()
//  07-Jan-2003   rzv   created
//-------------------------------------------------------------------
TCaptionBar::TCaptionBar()
{
	MouseX  = 0; 
	MouseY  = 0;
}

//-------------------------------------------------------------------
//  ~TCaptionBar()
//  07-Jan-2003   rzv   created
//-------------------------------------------------------------------
TCaptionBar::~TCaptionBar()
{
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::Create(TComponent* AOwner, const TRect& Rect)
{
	TWinControl::Create(AOwner, Rect);

	ApplySkin(Skin->CaptionBar);

	SetAlign(alTop);
	SetCurrentGrid(GetGrid("Active"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::Assign(TObject* Object)
{
	TWinControl::Assign(Object);
}

//-------------------------------------------------------------------
void TCaptionBar::ApplySkin(TObject* Object)
{
	TWinControl::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  OnPaint()
//  27-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::OnPaint(void) 
{
	// Paint grid
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas); 
		
	// Paint the caption
	CaptionX = (GetWidth() - CaptionWidth)/2;
	CaptionY = (GetHeight() - CaptionHeight)/2;
	
	// Set the pen color		
	Canvas->Pen->SetColor(GetCaptionColor());
	Canvas->Text(CaptionX, CaptionY, GetCaption());	

	TWinControl::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  07-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{	
	TWinControl::OnMouseDown(Button, Shift, X, Y);

	ControlToScreen(X, Y);
	MouseX = X; MouseY = Y;
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  07-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{	
	TWinControl::OnMouseUp(Button, Shift, X, Y);
	
	ControlToScreen(X, Y);
	MouseX = X; MouseY = Y;
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  07-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::OnMouseMove(const TShiftState& Shift, int X, int Y)
{	
	TWinControl::OnMouseMove(Shift, X, Y);

	if(GetCaptured())
	{
		ControlToScreen(X, Y);
		
		TControl* CtrlParent = (TControl*)GetParent();
		TControl* CtrlParentParent = (TControl*)CtrlParent->GetParent();

		if(CtrlParentParent != NULL)
		{
			if(X < CtrlParentParent->GetControlRect().left)
				X = CtrlParentParent->GetControlRect().left;
			else if(X > CtrlParentParent->GetControlRect().right)
				X = CtrlParentParent->GetControlRect().right;

			if(Y < CtrlParentParent->GetControlRect().top)
				Y = CtrlParentParent->GetControlRect().top;
			else if(Y > CtrlParentParent->GetControlRect().bottom)
				Y = CtrlParentParent->GetControlRect().bottom;
		}

		int DX = MouseX - X; 
		int DY = MouseY - Y;
				
		CtrlParent->SetLeft(GetParent()->GetLeft() - DX);
		CtrlParent->SetTop(GetParent()->GetTop() - DY);
	
		MouseX = X; MouseY = Y;
	}
}

//-------------------------------------------------------------------
//  OnParentActivate()
//  01-Oct-2003   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::OnParentActivate(void)
{
	TWinControl::OnParentActivate();

	SetCaptionColor(GetCaptionColorEnabled());
	SetCurrentGrid(GetGrid("Active"));
}

//-------------------------------------------------------------------
//  OnParentDeactivate()
//  01-Oct-2003   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::OnParentDeactivate(void)
{	
	TWinControl::OnParentDeactivate();

	SetCaptionColor(GetCaptionColorDisabled());
	SetCurrentGrid(GetGrid("Inactive"));
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCaptionBar::ParseSkin(TiXmlElement* XmlElement)
{
	TWinControl::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


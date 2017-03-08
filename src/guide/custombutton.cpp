#define N_IMPLEMENTS TCustomButton
//-------------------------------------------------------------------
//  custombutton.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/custombutton.h"
#include "guide/form.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TCustomButton()
//  09-Jan-2003   rzv   created
//-------------------------------------------------------------------
TCustomButton::TCustomButton()
{
	CaptionOffset = 0;
	State = bUp;
	ModalResult = mrNone;
}

//-------------------------------------------------------------------
//  TCustomButton()
//  09-Jan-2003   rzv   created
//-------------------------------------------------------------------
TCustomButton::~TCustomButton()
{
}

//-------------------------------------------------------------------
//  Create()
//	15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TCustomButton::Create(TComponent* AOwner, TRect Rect)
{
	TWinControl::Create(AOwner, Rect);
}

//-------------------------------------------------------------------
//	Assign()
//	15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TCustomButton::Assign(TObject* Object)
{
	TWinControl::Assign(Object);
}

//-------------------------------------------------------------------
void TCustomButton::ApplySkin(TObject* Object)
{
	TWinControl::ApplySkin(Object);

	TCustomButton* AControl = (TCustomButton*)Object;
	if(AControl != NULL)
	{
		SetCaptionOffset(AControl->GetCaptionOffset());
	}
}

//-------------------------------------------------------------------
/**
	@brief Changes the modal result of the button. 
	
	Clicking the button will close the modal form that contains it if 
	State is different than <code>mrNone</code>.

    @param Value Modal result for the button.
*/
//-------------------------------------------------------------------
void TCustomButton::SetModalResult(TModalResult Value) 
{ 
	if(ModalResult != Value)
		ModalResult = Value; 
}

//-------------------------------------------------------------------
/**
	@brief How much the caption moves when the button is pressed.

	@param Value	Amplitude of caption movement.
*/
//-------------------------------------------------------------------
void TCustomButton::SetCaptionOffset(float Value) 
{ 
	if(CaptionOffset != Value)
		CaptionOffset = Value; 
}

//-------------------------------------------------------------------
//  OnClick()
//  26-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TCustomButton::OnClick(void)
{	
	// If we have an owner form
	if(dynamic_cast<TForm*>(GetOwner()))
	{
		TForm* OwnerForm = (TForm*)GetOwner();

		// If the owner form is modal
		if(OwnerForm->GetModalResult() == mrNone)
			OwnerForm->SetModalResult(ModalResult);
	}
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TCustomButton::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TWinControl::OnMouseDown(Button, Shift, X, Y);

	State = bDown;
	CaptionX += CaptionOffset;
    CaptionY += CaptionOffset;	
	SetCurrentGrid(GetGrid("Pressed"));	
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TCustomButton::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{	
	TWinControl::OnMouseUp(Button, Shift, X, Y);

	State = bUp;
	SetCurrentGrid(GetGrid("Active"));
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TCustomButton::OnMouseMove(const TShiftState& Shift, int X, int Y)
{	
	TWinControl::OnMouseMove(Shift, X, Y);

	if(!GetCaptured())
	{
		SetCapture();	

		if(GetGrid("MouseOver") != NULL)
			SetCurrentGrid(GetGrid("MouseOver"));
		else
			SetCurrentGrid(GetGrid("Inactive"));
	}	
	else
	{
		ControlToScreen(X, Y);
		TRect Rect = GetControlRect();		
		if(!Rect.PtInRect(TPoint(X, Y)))
			ReleaseCapture();
	}
}

//-------------------------------------------------------------------
//  OnCaptureChanged()
//  29-July-2002   rzv    created
//-------------------------------------------------------------------
void TCustomButton::OnCaptureChanged(void)
{	
	TWinControl::OnCaptureChanged();

	if(State == bDown)
	{
		State = bUp;
		CaptionX -= CaptionOffset;
		CaptionY -= CaptionOffset;
	}
		
	if(GetActive())
	{
		if(GetGrid("Active") != NULL)
			SetCurrentGrid(GetGrid("Active"));
		else
			SetCurrentGrid(GetGrid("Inactive"));
	}
	else
		SetCurrentGrid(GetGrid("Inactive"));
}

//-------------------------------------------------------------------
//  OnActivate()
//  18-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCustomButton::OnActivate(void)
{
	if(GetGrid("Active") != NULL)
		SetCurrentGrid(GetGrid("Active"));
	else
		SetCurrentGrid(GetGrid("Inactive"));
	
	TWinControl::OnActivate();
}

//-------------------------------------------------------------------
//  OnDeactivate()
//  18-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCustomButton::OnDeactivate(void)
{
	SetCurrentGrid(GetGrid("Inactive"));
		
	TWinControl::OnDeactivate();
}

//-------------------------------------------------------------------
//  OnEnable()
//  15-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomButton::OnEnable(void)
{
    TWinControl::OnEnable();
	
	
	SetCaptionColor(GetCaptionColorEnabled());

	if(GetActive())
	{
		if(GetGrid("Active") != NULL)
			SetCurrentGrid(GetGrid("Active"));
		else
			SetCurrentGrid(GetGrid("Inactive"));
	}
	else
		SetCurrentGrid(GetGrid("Inactive"));
}

//-------------------------------------------------------------------
//  OnDisable()
//  15-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomButton::OnDisable(void)
{
	TWinControl::OnDisable();
	
	SetCaptionColor(GetCaptionColorDisabled());

	if(GetGrid("Disabled") != NULL)
		SetCurrentGrid(GetGrid("Disabled"));
	else
		SetCurrentGrid(GetGrid("Inactive"));
}

//-------------------------------------------------------------------
//  OnParentActivate()
//  29-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCustomButton::OnParentActivate(void)
{		
	TWinControl::OnParentActivate();
	
	if(GetActive())
	{
	    if(GetGrid("Active") != NULL)
			SetCurrentGrid(GetGrid("Active"));
		else
			SetCurrentGrid(GetGrid("Inactive"));	
	}
}
//-------------------------------------------------------------------
//  OnParentDeactivate()
//  29-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCustomButton::OnParentDeactivate(void)
{
	TWinControl::OnParentDeactivate();
	
	SetCurrentGrid(GetGrid("Inactive"));
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomButton::ParseSkin(TiXmlElement* XmlElement)
{
	TWinControl::ParseSkin(XmlElement);

	const char *value = NULL;

	// Set the caption offset
	value = XmlElement->Attribute("CaptionOffset");
	if(value != NULL)
	{
		sscanf(value, "%f", &CaptionOffset);
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



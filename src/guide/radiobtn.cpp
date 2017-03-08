#define N_IMPLEMENTS TRadioBtn
//-------------------------------------------------------------------
//  radiobtn.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/radiobtn.h"
#include "guide/skin.h"
#include "guide/group.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TRadioBtn()
//  09-Sep-2003   rzv   created
//-------------------------------------------------------------------
TRadioBtn::TRadioBtn()
{
}

//-------------------------------------------------------------------
//  ~TRadioBtn()
//  09-Sep-2003   rzv   created
//-------------------------------------------------------------------
TRadioBtn::~TRadioBtn()
{
}

//-------------------------------------------------------------------
//  Create()
//  09-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TRadioBtn::Create(TComponent* AOwner, const TRect& Rect)
{
	TCheckBtn::Create(AOwner, Rect);

	ApplySkin(Skin->RadioBtn);

	SetCurrentGrid(GetGrid("Unchecked"));
}

//-------------------------------------------------------------------
//  SetCheckState()
//  02-June-2004   rzv   created
//-------------------------------------------------------------------
void TRadioBtn::SetCheckState(TCheckState Value) 
{ 
	if(GetEnabled())
	{
		if(GetGroup() != NULL && GetCheckState() == cbUp)
		{
			TComponentsList::iterator iter;
			for(iter = GetGroup()->GetComponents()->begin(); 
				iter != GetGroup()->GetComponents()->end(); 
				iter++)
			{
				TCheckBtn* Button = (TCheckBtn*)(*iter);
				if(Button->GetCheckState() == cbDown && Button != this)
				{
					Button->SetCheckState(cbUp);
					break;
				}
			}
		}

		// Don't use TCheckBtn::SetCheck() !
		TCheckBtn::SetCheckState(Value);
	
		if(GetCheckState() == cbUp)
			SetCurrentGrid(GetGrid("Unchecked"));
		else
			SetCurrentGrid(GetGrid("Checked"));

	}	 
}

//-------------------------------------------------------------------
//  OnPaint()
//  01-June-2004   rzv   created
//-------------------------------------------------------------------
void TRadioBtn::OnPaint(void)
{		
    if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	TWinControl::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  01-June-2004   rzv   created
//-------------------------------------------------------------------
void TRadioBtn::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TCheckBtn::OnMouseDown(Button, Shift, X, Y);

	SetCheckState(cbDown);
}

//-------------------------------------------------------------------
//  OnEnable()
//  01-June-2004   rzv   created
//-------------------------------------------------------------------
void TRadioBtn::OnEnable(void)
{	
	TCheckBtn::OnEnable();

	if(GetCheckState() == cbUp)
		SetCurrentGrid(GetGrid("Unchecked"));
	else
		SetCurrentGrid(GetGrid("Checked"));
}

//-------------------------------------------------------------------
//  OnDisable()
//  01-June-2004   rzv   created
//-------------------------------------------------------------------
void TRadioBtn::OnDisable(void)
{
	TCheckBtn::OnDisable();

	if(GetCheckState() == cbUp)
		SetCurrentGrid(GetGrid("UncheckedDisabled"));
	else
		SetCurrentGrid(GetGrid("CheckedDisabled"));
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TRadioBtn::ParseSkin(TiXmlElement* XmlElement)
{
	TWinControl::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



#define N_IMPLEMENTS TCheckBtn
//-------------------------------------------------------------------
//  checkbtn.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/checkbtn.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TCheckLabel()
//  11-Sep-2003   rzv   created
//-------------------------------------------------------------------
TCheckLabel::TCheckLabel()
{
	CheckBtn = NULL;
}

//-------------------------------------------------------------------
//  OnPaint()
//  11-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCheckLabel::OnPaint(void)
{
	CaptionY = (GetHeight() - CaptionHeight)/2;
	
	// Set the pen color		
	Canvas->Pen->SetColor(GetCaptionColor());
	// Render text
	Canvas->Text(TextPosX, CaptionY, GetCaption());
	
	TControl::OnPaint();	
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  11-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCheckLabel::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{	
    TLabel::OnMouseDown(Button, Shift, X, Y);
	
     if(CheckBtn != NULL)
		CheckBtn->CMMouseDown(Button, X, Y);
}

//-------------------------------------------------------------------
//  TCheckBtn()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
TCheckBtn::TCheckBtn()
{
	Label = NULL;	
	CheckState = cbUp;
}

//-------------------------------------------------------------------
//  ~TCheckBtn()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
TCheckBtn::~TCheckBtn()
{
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::Create(TComponent* AOwner, const TRect& Rect)
{
	TWinControl::Create(AOwner, Rect);

	ApplySkin(Skin->CheckBtn);

	SetCurrentGrid(GetGrid("Unchecked"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::Assign(TObject* Object)
{
	TWinControl::Assign(Object);
}

//-------------------------------------------------------------------
void TCheckBtn::ApplySkin(TObject* Object)
{
	TWinControl::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  SetParent()
//  11-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::SetParent(TControl* AParent) 
{
	TWinControl::SetParent(AParent);

	// Set the same parent for the label
	if(Label != NULL)
		Label->SetParent(AParent);
}

//-------------------------------------------------------------------
//  SetCheckState()
//  01-June-2004   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::SetCheckState(TCheckState Value) 
{ 
	if(CheckState == Value)
		return;

	CheckState = Value; 

	if(GetEnabled())
	{
		
		if(GetCheckState() == cbUp)
			SetCurrentGrid(GetGrid("Unchecked"));
		else
			SetCurrentGrid(GetGrid("Checked"));
	}	 
}

//-------------------------------------------------------------------
//  OnPaint()
//  11-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::OnPaint(void)
{	
    Canvas->Brush->SetColor(GetColor());	
	
    if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	TWinControl::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TCheckBtn::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TWinControl::OnMouseDown(Button, Shift, X, Y);
	
	if(GetEnabled())
	{
		if(CheckState == cbUp)
			SetCheckState(cbDown);
		else
			SetCheckState(cbUp);
	}
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  10-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::OnTextChanged(void)
{
	TWinControl::OnTextChanged();

	TString CtrlCaption = GetCaption();
	if(!CtrlCaption.empty())
	{
		if(Label == NULL)
		{
			int Y = GetTop() + (GetHeight() - CaptionHeight)/2;

			Label = new TCheckLabel;
			Label->Create(this, TRect(GetLeft() + GetWidth(), Y, 0, 0));
			Label->SetParent(GetParent());
			Label->SetCheckBtn(this);
			Label->SetAutoSize(true);
		}
			
		Label->SetCaption(CtrlCaption.c_str());
	}
}

//-------------------------------------------------------------------
//  OnEnable()
//  27-Oct-2003   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::OnEnable(void)
{	
	TWinControl::OnEnable();

	if(GetCheckState() == cbUp)
		SetCurrentGrid(GetGrid("Unchecked"));
	else
		SetCurrentGrid(GetGrid("Checked"));

}

//-------------------------------------------------------------------
//  OnDisable()
//  27-Oct-2003   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::OnDisable(void)
{
	TWinControl::OnDisable();

	if(GetCheckState() == cbUp)
		SetCurrentGrid(GetGrid("UncheckedDisabled"));
	else
		SetCurrentGrid(GetGrid("CheckedDisabled"));
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCheckBtn::ParseSkin(TiXmlElement* XmlElement)
{
	TWinControl::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



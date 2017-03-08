#define N_IMPLEMENTS TButton
//-------------------------------------------------------------------
//  button.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/button.h"
#include "guide/form.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TButton()
//  09-Jan-2003   rzv   created
//-------------------------------------------------------------------
TButton::TButton()
{	
}

//-------------------------------------------------------------------
//  TButton()
//  09-Jan-2003   rzv   created
//-------------------------------------------------------------------
TButton::~TButton()
{
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TButton::Create(TComponent* AOwner, TRect Rect)
{
	TCustomButton::Create(AOwner, Rect);

	ApplySkin(Skin->Button);

	SetCurrentGrid(GetGrid("Active"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TButton::Assign(TObject* Object)
{
	TCustomButton::Assign(Object);
}

//-------------------------------------------------------------------
void TButton::ApplySkin(TObject* Object)
{
	TCustomButton::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  OnPaint()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
void TButton::OnPaint(void)
{
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	// Set the pen color		
	Canvas->Pen->SetColor(GetCaptionColor());
	// Paint caption
	Canvas->Text(CaptionX, CaptionY, GetCaption());	

	TCustomButton::OnPaint();
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  22-May-2004   rzv    created
//-------------------------------------------------------------------
void TButton::OnTextChanged(void)
{
	TCustomButton::OnTextChanged();
	
	CaptionX = (GetWidth() - CaptionWidth)/2;
	CaptionY = (GetHeight() - CaptionHeight)/2;
}

//-------------------------------------------------------------------
//  OnSize()
//  22-May-2004   rzv    created
//-------------------------------------------------------------------
void TButton::OnSize(int AWidth, int AHeight)
{
	TCustomButton::OnSize(AWidth, AHeight);

	CaptionX = (GetWidth() - CaptionWidth)/2;
	CaptionY = (GetHeight() - CaptionHeight)/2;
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TButton::ParseSkin(TiXmlElement* XmlElement)
{
	TCustomButton::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



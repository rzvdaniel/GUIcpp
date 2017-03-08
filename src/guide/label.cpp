#define N_IMPLEMENTS TLabel
//-------------------------------------------------------------------
//  label.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/label.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TLabel()
//  05-March-2003   rzv   created
//-------------------------------------------------------------------
TLabel::TLabel()
{
    TextMargin = 1;
	TextPosX = TextMargin;
	TextAlignment = taLeftJustify;
	AutoSize = false;    
}

//-------------------------------------------------------------------
//  ~TLabel()
//  05-March-2003   rzv   created
//-------------------------------------------------------------------
TLabel::~TLabel()
{	
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TLabel::Create(TComponent* AOwner, const TRect& Rect)
{
	TControl::Create(AOwner, Rect);
}

//-------------------------------------------------------------------
//  SetTextAlignment()
//  05-March-2003   rzv   created
//-------------------------------------------------------------------
void TLabel::SetTextAlignment(TTextAlignment Value)
{
    if(TextAlignment != Value)
	{
		TextAlignment = Value;
		UpdateTextPosition();
	}

}

//-------------------------------------------------------------------
//  UpdateTextPosition()
//  16-March-2004   rzv   created
//-------------------------------------------------------------------
void TLabel::UpdateTextPosition(void)
{
	if(!AutoSize)
	{
		switch(TextAlignment)
		{
			case taCenter:
				TextPosX = (GetWidth() - CaptionWidth)/2;
				break;
			case taLeftJustify:
				TextPosX = TextMargin;
				break;
			case taRightJustify:
				TextPosX = GetWidth() - CaptionWidth - TextMargin;
				break;
		}
	}
}

//-------------------------------------------------------------------
/**
	Make the label adjust its size automatically so the client area 
	accomodates the height and width of the text. When AutoSize is 
	true, the size of the label is readjusted whenever its text changes.
*/
void TLabel::SetAutoSize(bool Value)
{
    if(AutoSize != Value)
		AutoSize = Value;

	if(AutoSize == true)
		SetBounds(GetLeft(), GetTop(), CaptionWidth, CaptionHeight);
}

//-------------------------------------------------------------------
//  OnPaint()
//  05-March-2003   rzv   created
//-------------------------------------------------------------------
void TLabel::OnPaint(void) 
{
    CaptionY = (GetHeight() - CaptionHeight)/2;
    	
	// Render background
	Canvas->Brush->SetColor(GetColor());
	Canvas->FillRect(0, 0, GetWidth(), GetHeight());

	// Render text
	Canvas->Text(TextPosX, CaptionY, GetCaption());
	
	TControl::OnPaint();	
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  05-March-2003   rzv   created
//-------------------------------------------------------------------
void TLabel::OnTextChanged(void)
{
	TControl::OnTextChanged();
	
	// Update the bounds if the AutoSize is true
	SetAutoSize(GetAutoSize());

	// Update the text position
	UpdateTextPosition();
}

//-------------------------------------------------------------------
//  OnSize()
//  16-March-2004   rzv   created
//-------------------------------------------------------------------
void TLabel::OnSize(int AWidth, int AHeight)
{
	TControl::OnSize(AWidth, AHeight);

	// Update the text position
	UpdateTextPosition();
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



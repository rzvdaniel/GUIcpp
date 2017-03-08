#define N_IMPLEMENTS TGroupBox
//-------------------------------------------------------------------
//  groupbox.cpp
//  (C) 2003 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/groupbox.h"
#include "guide/screen.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TGroupBox()
//  10-Sep-2003   rzv   created
//-------------------------------------------------------------------
TGroupBox::TGroupBox() 
{
	CaptionAlignment = caLeftJustify;
	CaptionMargin = 15;
	CaptionSpacing = 5;
	CaptionPos = 0;
}

//-------------------------------------------------------------------
//  ~TGroupBox()
//  10-Sep-2003   rzv   created
//-------------------------------------------------------------------
TGroupBox::~TGroupBox()
{	
}

//-------------------------------------------------------------------
//  Create()
//  10-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TGroupBox::Create(TComponent* AOwner, const TRect& Rect)
{
	TWinControl::Create(AOwner, Rect);
}

//-------------------------------------------------------------------
//  SetCaptionAlignment()
//  Specify how the caption is aligned within the control
//  10-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TGroupBox::SetCaptionAlignment(TCaptionAlignment Value)
{
    if(CaptionAlignment != Value)
		CaptionAlignment = Value;

	switch(CaptionAlignment)
	{    
		case caCenter:
			CaptionPos = (GetWidth() - GetCaptionWidth() - CaptionSpacing)/2;
            break;
	    case caLeftJustify:
	        CaptionPos = CaptionMargin + CaptionSpacing;
			break;
		case caRightJustify:
	        CaptionPos = GetWidth() - GetCaptionWidth() - CaptionMargin - CaptionSpacing;
			break;
	}
}	
	
//-------------------------------------------------------------------
//  OnPaint()
//  10-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TGroupBox::OnPaint(void) 
{
	Canvas->Pen->SetColor(GetColor());
	
	// top right 
	Canvas->MoveTo(GetWidth(), GetCaptionHeight()/2);
	Canvas->LineTo(CaptionPos + CaptionSpacing + GetCaptionWidth(), GetCaptionHeight()/2);
	// top left	
	Canvas->MoveTo(CaptionPos - CaptionSpacing, GetCaptionHeight()/2);
	Canvas->LineTo(0, GetCaptionHeight()/2);								
	// left	
	Canvas->LineTo(0, GetHeight());	
	// bottom 					
	Canvas->LineTo(GetWidth(), GetHeight());
	// right 		
	Canvas->LineTo(GetWidth(), GetCaptionHeight()/2);	

	// Render text
	Canvas->Pen->SetColor(GetCaptionColor());
	Canvas->Text(CaptionPos, 0, GetCaption());	
	
	TWinControl::OnPaint();
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  10-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TGroupBox::OnTextChanged(void)
{
	TWinControl::OnTextChanged();

	// Call to update CaptionPos because one of GetCaptionWidth() or
	// GetCaptionHeight() has changed
	SetCaptionAlignment(CaptionAlignment);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


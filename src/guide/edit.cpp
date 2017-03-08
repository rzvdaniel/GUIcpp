#define N_IMPLEMENTS TEdit
//-------------------------------------------------------------------
//  edit.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/edit.h"
#include "guide/skin.h"
#include "guide/screen.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TEdit()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
TEdit::TEdit() 
{
	LeftCharIndex = 0;
	TextMovement = 5;
}

//-------------------------------------------------------------------
//  ~TEdit()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
TEdit::~TEdit()
{	
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TEdit::Create(TComponent* AOwner, const TRect& Rect)
{
	TCustomEdit::Create(AOwner, Rect);

	ApplySkin(Skin->Edit);

	SetCurrentGrid(GetGrid("Unfocused"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::Assign(TObject* Object)
{
	TCustomEdit::Assign(Object);
}

//-------------------------------------------------------------------
void TEdit::ApplySkin(TObject* Object)
{
	TCustomEdit::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  OnPaint()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnPaint(void) 
{	
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	TRect Margin = GetTextMargins();
	float YPosText = (GetHeight() - GetFont()->GetHeight())/2;

	// Set the pen color		
	Canvas->Pen->SetColor(GetCaptionColor());

	// Render text
	Canvas->Text(Margin.left, YPosText, VisibleText);
	
	if(GetActive()) 
	{	
		// Render the caret
		Canvas->Pen->SetColor(GetCaretColor());
        Canvas->MoveTo(CaretPos.x, YPosText);
        Canvas->LineTo(CaretPos.x, YPosText + GetFont()->GetHeight());

		// Render selection rect
		Canvas->Brush->SetColor(GetSelectionColor());
	    Canvas->FillRect(TRect(SelRect.left, YPosText, SelRect.right - SelRect.left, GetFont()->GetHeight()));
	}
	else
	{
		/*
		if(GetHideSelection() == false)
		{
			// Render selection rect
			Canvas->Brush->SetColor(GetSelectionColor());
	        Canvas->FillRect(TRect(SelRect.left, SelRect.top, SelRect.right - SelRect.left, SelRect.bottom));
		}
		*/
	}
	
	TCustomEdit::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	// Retrieve the character index at position X
	int CharIndex = GetCharIndex(X - GetTextMargins().left);

	// If the SHIFT key is pressed
	if(Shift.count(ssShift))
	{
		if(CharIndex > GetCursorPos())
		{
			SetSelectionStart(GetCursorPos());
			SetSelectionEnd(CharIndex);
		}
		else
		{
			SetSelectionStart(CharIndex);
			SetSelectionEnd(GetCursorPos());
		}
	}
	else
	{
		SetSelectionStart(CharIndex);
		SetSelectionEnd(CharIndex);
	}

	// Set the new cursor position.
	SetCursorPos(CharIndex);
	
	UpdateCaret();
	UpdateSelectionRect();

	TCustomEdit::OnMouseDown(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TCustomEdit::OnMouseUp(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnMouseMove(const TShiftState& Shift, int X, int Y)
{	
	if(GetCaptured())
	{
	/*
		float LeftTextWidth =  Text->GetTextWidth(GetFont(),  Text->substr(0, LeftCharIndex));
		int CharIndex = Text->GetCharIndex(GetFont(), LeftTextWidth + X - MarginLeft);
		
		// Check if we're selecting to the right or to the left
		bool SelectionRight = true;
		if(CharIndex < DragStart)
			SelectionRight = false;

		DragEnd = CharIndex;
		Text->SetSelection(DragStart, DragEnd);

		if(SelectionRight == true)
			UpdateSelectionRight();
		else
			UpdateSelectionLeft();
*/
	}

	TCustomEdit::OnMouseMove(Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnKeyDown()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnKeyDown(unsigned short &Key, const TShiftState& Shift)
{
	if(Key == T_KEY_LEFT)
	{
		CursorLeft();
	}
	else if(Key == T_KEY_RIGHT)
	{
		CursorRight();
	}
	else if(Key == T_KEY_BACK)
	{
	    DeleteLeft(); 	
	}
	else if(Key == T_KEY_DELETE)
	{
		if(GetSelection().size() == 0)
			DeleteRight(); 
		else
			DeleteLeft(); 	
    }

	// Update selection
	int CursorPosition = GetCursorPos();
	
	// If the SHIFT key is pressed
	if(Screen->GetShiftState().count(ssShift))
	{
		if(CursorPosition > GetSelectionStart())
			SetSelectionEnd(CursorPosition);
		else
			SetSelectionStart(CursorPosition);			
	}
	else
	{
		SetSelectionStart(CursorPosition);
		SetSelectionEnd(CursorPosition);
	}

	UpdateCaret();
	UpdateSelectionRect();

	TCustomEdit::OnKeyDown(Key, Shift);	
}

//-------------------------------------------------------------------
//  OnKeyUp()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnKeyUp(unsigned short& Key, const TShiftState& Shift)
{
	TCustomEdit::OnKeyUp(Key, Shift);	
}

//-------------------------------------------------------------------
//  OnKeyPress()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnKeyPress(char &Key)
{
	if(GetReadOnly() == false)
	{
		switch(GetCharCase())
		{
			case ecNormal:
				break;
			case ecLowerCase:
				Key = tolower(Key);
				break;
			case ecUpperCase:
				Key = toupper(Key);
				break;
		}

		// If we have a maximum text length for our control
		if(GetMaxLength() > 0)
		{
			// Insert a new character only if the text length doesn't exceed
			// the maximum allowed length
			if((int)GetText().size() - (int)GetSelection().size() < GetMaxLength())
			{
				ReplaceSelectedSubstring(&Key);
			}
		}
		else
		{
				ReplaceSelectedSubstring(&Key);			
		}		 
		
		MoveTextLeft(TString(&Key));
		UpdateCaret();
		CMTextChanged();
	}

	TCustomEdit::OnKeyPress(Key);	
}

//-------------------------------------------------------------------
//  OnCaptureChanged()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnCaptureChanged(void)
{	
	TCustomEdit::OnCaptureChanged();
}

//-------------------------------------------------------------------
//  OnActivate()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnActivate(void)
{
    TCustomEdit::OnActivate();
    
	if(GetAutoSelect() == true)
	{
		/*
		SetSelectionStart(GetText().size());
		SetSelectionEnd(0);
		MoveTextLeft();
		UpdateSelectionRect();
		*/
	}

	SetCurrentGrid(GetGrid("Focused"));
}

//-------------------------------------------------------------------
//  OnDeactivate()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnDeactivate(void)
{
    TCustomEdit::OnDeactivate();

	SetCurrentGrid(GetGrid("Unfocused"));
}

//-------------------------------------------------------------------
//  OnSize()
//  06-Sep-2004   rzv    created
//-------------------------------------------------------------------
void TEdit::OnSize(int AWidth, int AHeight)
{
	TCustomEdit::OnSize(AWidth, AHeight);
}

//-------------------------------------------------------------------
//  OnFontChanged()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnFontChanged(void)
{
	TCustomEdit::OnFontChanged();

	if(GetAutoSize() == true)
		SetBounds(GetLeft(), GetTop(), GetWidth(), GetFont()->GetHeight());
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  30-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::OnTextChanged(void)
{	
	TCustomEdit::OnTextChanged();
    
	SetModified(true);	
	
	UpdateVisibleText();
	UpdateSelectionRect();		
}

//-------------------------------------------------------------------
/**
	Change selection start position too.
*/
//-------------------------------------------------------------------
void TEdit::CursorHome(void)
{
    TCustomEdit::CursorHome();
}

//-------------------------------------------------------------------
/**
	Change selection end position too.
*/
//-------------------------------------------------------------------
void TEdit::CursorEnd(void)
{
    TCustomEdit::CursorEnd();
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TEdit::CursorLeft(void)
{
    TCustomEdit::CursorLeft();

	MoveTextRight(GetText().substr(GetCursorPos(), 1));
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TEdit::CursorRight(void)
{
    TCustomEdit::CursorRight();

	MoveTextLeft(GetText().substr(GetCursorPos(), 1));
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TEdit::DeleteLeft(void)
{
	TCustomEdit::DeleteLeft();

	TString Str = GetText().substr(GetCursorPos(), 1);
	if(GetCursorPos() < LeftCharIndex + 1)
		MoveTextRight(Str);
	else
		MoveTextLeft(Str);
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TEdit::DeleteRight(void)
{
	TCustomEdit::DeleteRight();
}

//-------------------------------------------------------------------
/**
	Also updates the caret position.
	
	@param Value New cursor position.
*/
//-------------------------------------------------------------------
void TEdit::SetCursorPos(int Value)
{
	TCustomEdit::SetCursorPos(Value);
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TEdit::UpdateVisibleText(void)
{ 
	TString Text = GetText();

	// If the caret is at the end of the text, LeftCharIndex will be Text.size() + 1
    for(int i = 0; i < Text.size() - LeftCharIndex + 1; i++)
    {
		// Get the width of the substring from the left character index, i characters
		TString Substring = Text.substr(LeftCharIndex, i + 1);
        float StringWidth = GetFont()->GetTextWidth(Substring);
        	
        if(StringWidth > GetWidth() - GetTextMargins().left - GetTextMargins().right)
		{
            VisibleText.assign(Text.substr(LeftCharIndex, i));			
			return;
		}
    }

	if(LeftCharIndex <= Text.size())
		VisibleText.assign(Text.substr(LeftCharIndex));
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TEdit::UpdateCaret(void)
{	
	/*
	int CursorPosition = GetCursorPos();
		
	if(Screen->GetShiftState().count(ssShift))
	{
		if(CursorPosition >= GetSelectionStart())
		{
			SetSelectionEnd(CursorPosition);
		}
		else
		{
			SetSelectionEnd(GetSelectionStart());
			SetSelectionStart(CursorPosition);
		}
	}
	else
	{
		SetSelectionStart(CursorPosition);
		SetSelectionEnd(CursorPosition);
	}
	*/

	TString Str = VisibleText.substr(0, GetCursorPos() - LeftCharIndex);
	CaretPos.x = GetTextMargins().left + Canvas->GetTextWidth(Str);  
}

//-------------------------------------------------------------------
/** 
		Updates left and right positions for selection rect.
*/
//-------------------------------------------------------------------
void TEdit::UpdateSelectionRect(void)
{
	if(GetSelectionStart() <= GetSelectionEnd())
	{		
		// Be careful that LeftCharIndex could become greater than SelStart, if the text is moved to the left. 
		if(GetSelectionStart() > LeftCharIndex)
			SelRect.left = GetTextMargins().left + Canvas->GetTextWidth(VisibleText.substr(0, GetSelectionStart() - LeftCharIndex));
		else 
			SelRect.left = GetTextMargins().left;

		SelRect.right = GetTextMargins().left + Canvas->GetTextWidth(VisibleText.substr(0, GetSelectionEnd() - LeftCharIndex));
	}
	else
	{
		SelRect.left = SelRect.right = GetTextMargins().left;
	}
}

//-------------------------------------------------------------------
/** 
	Retrieve the substring from the beginning of the visible text to 
	the specified pixel position.

	@param
		X Position in pixels where we're looking.
	@return 
		Substring that is found from the beginning of the text to the
		specified position.
*/
//-------------------------------------------------------------------
TString TEdit::GetSubstring(int X)
{
	TString Str;
	char buf[128];
	
	for(int i = 0; i < (int)VisibleText.size(); i++)
	{
		// Get the substring from the beginning of the text, i + 1 characters
		Str = VisibleText.substr(0, i + 1);

		// And find it's width.
		float StrWidth = GetFont()->GetTextWidth(Str);
		
		// Converts the character at position i to a character string
		sprintf(buf, "%c", VisibleText.at(i));
		
		if(X < StrWidth)
		{
			/*
			
			ATTACK word example:

			     -----   
			       |     
			       |     
			AT |   |   | ACK
			---------------
			    |     |
			    |     |
			 X LEFT  X RIGHT   
			
			*/

			if( StrWidth - X > GetFont()->GetTextWidth(buf)/2 )
			{
				// Returns the substring without the last character X position is containing
				// (Go to LEFTt of X position).
				return VisibleText.substr(0, i);
			}
			else
			{
				// Returns the substring WITH the last character X position is containing
				// (Go to RIGHT of X position).
				return Str;
			}
		}
	}
	
	return VisibleText;
}

//-------------------------------------------------------------------
/** 
	Give us the index of the character within the visible text,
	at specified position.

	@param
		X Position in pixels where we're looking.
	@return 
		Index of the character within the visible text.
*/
//-------------------------------------------------------------------
int TEdit::GetVisibleTextCharIndex(int X)
{
	TString Str = GetSubstring(X);
	return Str.size();
}

//-------------------------------------------------------------------
/** 
	Give us the index of the character within control's text, at 
	specified position.

	@param
		X Position in pixels where we're looking.
	@return 
		Index of the character within the text.
*/
//-------------------------------------------------------------------
int TEdit::GetCharIndex(int X)
{
	TString Str = GetSubstring(X);
	return LeftCharIndex + Str.size();
}

//-------------------------------------------------------------------
//  MoveTextLeft()
//  05-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::MoveTextLeft(TString AString)
{
	if(GetCursorPos() - LeftCharIndex > (int)VisibleText.size())
		LeftCharIndex += TextMovement;

	UpdateVisibleText();
}

//-------------------------------------------------------------------
//  MoveTextRight()
//  05-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::MoveTextRight(TString AString)
{
	if(GetCursorPos() < LeftCharIndex + 1)
	{
		LeftCharIndex -= TextMovement;

		if(LeftCharIndex < 0)
			LeftCharIndex = 0;
	}

	UpdateVisibleText();
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TEdit::ParseSkin(TiXmlElement* XmlElement)
{
	TCustomEdit::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


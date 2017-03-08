#define N_IMPLEMENTS TCustomEdit
//-------------------------------------------------------------------
//  customedit.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/customedit.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
/**
	Constructor.
*/
//-------------------------------------------------------------------
TCustomEdit::TCustomEdit()
{
	MaxLength = 0;
	CursorPos = 0;
	SelStart = 0;
	SelEnd = 0;
	Modified = false;
	AutoSize = false;
	ReadOnly = false;
	AutoSelect = false;
	HideSelection = true;
	CharCase = ecNormal;
	ColorCaret = clBlack;
	PasswordChar = '\0';
}

//-------------------------------------------------------------------
/**
	Destructor.
*/
//-------------------------------------------------------------------
TCustomEdit::~TCustomEdit()
{
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::Create(TComponent* AOwner, const TRect& Rect)
{	

	TWinControl::Create(AOwner, Rect);
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::Assign(TObject* Object)
{
	TWinControl::Assign(Object);
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::ApplySkin(TObject* Object)
{
	TWinControl::ApplySkin(Object);

	TCustomEdit* CustomEdit = (TCustomEdit*)Object;
	if(CustomEdit != NULL)
	{
		SetCaretColor(CustomEdit->GetCaretColor());
		SetTextMargins(CustomEdit->GetTextMargins());
	}
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::SetMaxLength(int Value) 
{ 
	MaxLength = Value; 
}

//-------------------------------------------------------------------
/** 
    @brief Set the character that will be used for a password edit control.
	    
    Password character will be used when displaying the text of the 
    control. This will not affect the real control's text, but only the
    way it will looks for the user.
*/	
//-------------------------------------------------------------------
void TCustomEdit::SetPasswordChar(char Value)
{
    if(PasswordChar != Value)
        PasswordChar = Value;
}
	
//-------------------------------------------------------------------
/**
	Adjust the height of the control to the height of the font.
	It doesn't changes the control's width.
*/
//-------------------------------------------------------------------
void TCustomEdit::SetAutoSize(bool Value)
{
    if(AutoSize != Value)
		AutoSize = Value;

	if(AutoSize == true)
		SetBounds(GetLeft(), GetTop(), GetWidth(), GetFont()->GetHeight());
}

//-------------------------------------------------------------------
/**
	Transforms the characters of the specified string to uppercase 
	letters.

	@note This function is from www.bruceeckel.com. 
*/
//-------------------------------------------------------------------
TString TCustomEdit::UpperCase(TString& String) 
{
	for(unsigned int i = 0; i < String.length(); i++)
		String[i] = toupper(String[i]);
	
	return String;
}

//-------------------------------------------------------------------
/**
	Transforms the characters of the specified string to lowercase 
	letters.

	@note This function is from www.bruceeckel.com. 
*/
//-------------------------------------------------------------------
TString TCustomEdit::LowerCase(TString& String) 
{
	for(unsigned int i = 0; i < String.length(); i++)
		String[i] = tolower(String[i]);
	
	return String;
}

//-------------------------------------------------------------------
/**
	Set the character case of the control.

    @param Value An TEditCharCase enum: <code> ecNormal </code> for
				 normal case (both uppercase and lowercase letters), 
				 <code> ecLowerCase </code> if the control should
				 contains only lowercase letters and 
				 <code> ecUpperCase </code> for only uppercase letters.
*/
//-------------------------------------------------------------------
void TCustomEdit::SetCharCase(TEditCharCase Value) 
{ 
	if(CharCase != Value)
	{
		CharCase = Value; 
		
		TString String;
		String.assign(GetText());

		switch(CharCase)
		{
			case ecNormal:
				break;
			case ecLowerCase:
				SetText(LowerCase(String));
				break;
			case ecUpperCase:
				SetText(UpperCase(String));
				break;
		}
	}
}

//-------------------------------------------------------------------
/**
	Clear the content of the string and reset cursor position to 0.
*/
//-------------------------------------------------------------------
void TCustomEdit::Clear(void)
{
	GetText().erase(0, GetText().size());
	SetCursorPos(0);
	SelStart = 0;
	SelEnd = 0;
}

//-------------------------------------------------------------------
/**
	@return <code>true</code> if the string is empty, <code>false</code>
			if not.
*/
//-------------------------------------------------------------------
bool TCustomEdit::IsEmpty(void) const
{
	return GetText().empty();
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
int TCustomEdit::GetMaxCursorPos() const
{
    return GetText().size();
}

//-------------------------------------------------------------------
/**
	@param Value New cursor position.
*/
//-------------------------------------------------------------------
void TCustomEdit::SetCursorPos(int Value)
{
	if(CursorPos != Value)
	{
		CursorPos = Value; 

		if(CursorPos > GetMaxCursorPos())
			CursorPos = GetMaxCursorPos();
		else if(CursorPos < 0)
			CursorPos = 0;
	}
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::CursorHome()
{
    SetCursorPos(0);
	SelStart = 0;
}

//-------------------------------------------------------------------
/**
	Change selection end position too.
*/
//-------------------------------------------------------------------
void TCustomEdit::CursorEnd()
{
    SetCursorPos(GetMaxCursorPos());
	SelEnd = 0;
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::CursorLeft()
{
    SetCursorPos(GetCursorPos() - 1);
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::CursorRight()
{
    SetCursorPos(GetCursorPos() + 1);
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::DeleteLeft()
{
    if(GetReadOnly() == false )
    {
		int SelLength = GetSelectionLength();

        // If we have selected text
        if(SelLength > 0)
        {
            ReplaceSelectedSubstring("");
        }
		// If we don't have selected text
        else if(GetSelectionStart() > 0)
        {
			SetSelectionStart(SelStart - 1);
			SetSelectionEnd(GetSelectionStart());
			SetCursorPos(GetSelectionStart());

			TString Str = GetText();
            Str.erase(GetSelectionStart(), 1);
            SetText(Str);
        }
    }
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::DeleteRight()
{
  if(GetReadOnly() == false )
  {
        // If we have selected text
        if(GetSelectionLength() > 0)
        {
            ReplaceSelectedSubstring("");
        }
        else if(GetSelectionStart() < (int)GetText().size())
        {
            TString Str = GetText();
            Str.erase(GetSelectionStart(), 1);
            SetText(Str);
        }
    }  
}

//-------------------------------------------------------------------
/**
	@note It doesn't change the cursor position.
*/
//-------------------------------------------------------------------
void TCustomEdit::SetSelectionStart(int Value) 
{
	if(SelStart != Value)
	{
		SelStart = Value; 

		if(SelStart > (int)GetText().size())
			SelStart = (int)GetText().size();
		else if(SelStart < 0)
			SelStart = 0;
	}
}

//-------------------------------------------------------------------
/**
	It doesn't change the cursor position.
*/
//-------------------------------------------------------------------
void TCustomEdit::SetSelectionEnd(int Value)
{
	if(SelEnd != Value)
	{
		SelEnd = Value; 

		if(SelEnd > (int)GetText().size())
			SelEnd = (int)GetText().size();
		else if(SelEnd < 0)
			SelEnd = 0;
	}
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
int TCustomEdit::GetSelectionLength(void)
{
	// Check if selection end is greater than selection start
	if(SelEnd > SelStart)
		return SelEnd - SelStart;

	return 0;
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
TString TCustomEdit::GetSelection(void) 
{ 
    return GetText().substr(SelStart, GetSelectionLength());
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TCustomEdit::ReplaceSelectedSubstring(TString Str) 
{ 
    ReplaceSelectedSubstring(Str.c_str());
}

//-------------------------------------------------------------------
/**
	Also adjust selection start, selection end and cursor position.
*/
//-------------------------------------------------------------------
void TCustomEdit::ReplaceSelectedSubstring(const char* Str)
{ 
	TString CurrentText = GetText();
        
	CurrentText.erase(SelStart, GetSelectionLength());
	CurrentText.insert(SelStart, Str);

    SetText(CurrentText);

    SelStart += strlen(Str);
	SelEnd = SelStart;
	
    SetCursorPos(SelStart);	
}

//-------------------------------------------------------------------
//  ParseSkin()
//  20-Apr-2007   rzv   created
//-------------------------------------------------------------------
void TCustomEdit::ParseSkin(TiXmlElement* XmlElement)
{
	TWinControl::ParseSkin(XmlElement);
	
	const char *value = NULL;
	
	// Set caret color
	value = XmlElement->Attribute("CaretColor");
	if(value != NULL)
		sscanf(value, "%x", &ColorCaret);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



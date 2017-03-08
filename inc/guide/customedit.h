#ifndef T_CUSTOMEDIT_H
#define T_CUSTOMEDIT_H
//-------------------------------------------------------------------
//  CLASS
//  TCustomEdit
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TEdit
#include "guide/ndefdllclass.h"

#ifndef T_WINCONTROL_H
#include "guide/wincontrol.h"
#endif

enum TEditCharCase { ecNormal, ecUpperCase, ecLowerCase };

//-------------------------------------------------------------------
class N_PUBLIC TCustomEdit : public TWinControl
{
    TEditCharCase CharCase;
	char PasswordChar;
	bool Modified;
	bool AutoSelect;
	bool AutoSize;
	bool HideSelection;
	bool ReadOnly;
	int	MaxLength;	
    int CursorPos;
	int SelStart;
    int SelEnd;
	TColor ColorCaret;

public:
	TCustomEdit();
	virtual ~TCustomEdit();
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

	/// Set the maximum allowed length of the string.
	void SetMaxLength(int Value);
	/// Retrieve the maximum allowed length of the string.
	int GetMaxLength(void) const { return MaxLength; }

	/// Set to true when the text is modified.
	void SetModified(bool Value) { Modified = Value; }
	/// Retrieve the Modified state.
	bool GetModified(void) const { return Modified; }

	/// Set the selection color.
	void SetCaretColor(TColor Value) { ColorCaret = Value; }
	/// Get the selection color.
	TColor GetCaretColor(void) const { return ColorCaret; }

	// Specify if the control is readonly or not.
	inline void SetReadOnly(bool Value);
    // Retrieve the ReadOnly state of the control.
	inline bool GetReadOnly(void) const;
	// Specify if the text will be selected when the control will receive focus.
	inline void SetAutoSelect(bool Value);
	// Retrieve the value of the control's AutoSelect property.
	inline bool GetAutoSelect(void) const;
	// Specify if the selected text will remain selected after the control will loose the focus.
	inline void SetHideSelection(bool Value);
	// Retrieve the value of the control's HideSelection property.
	inline bool GetHideSelection(void) const;
	// Specify the kind of the case for the control's text.
	void SetCharCase(TEditCharCase Value);
	// Retrieve the character's chase of the text.
	inline TEditCharCase GetCharCase(void) const;
	// Specify if the control will adjust its height to fit the size of the font.
	void SetAutoSize(bool Value);
	// Retrieve the value of the control's AutoSize property.
	inline bool GetAutoSize(void) const;
    /// Set the character that will be used for a password edit control.
	void SetPasswordChar(char Value);
	// Retrieve the character used for password edit control.
	inline char GetPasswordChar(void) const;

	/// Clear text.
	void Clear(void);
	/// Verify if string is empty.
	bool IsEmpty(void) const;

	/// Set cursor position.
	virtual void SetCursorPos(int Value);
	/// Get the current cursor position.
	virtual int GetCursorPos(void) const { return CursorPos; }
	/// Set cursor position to the beginning of the string.
	virtual void CursorHome(void);
	/// Set cursor position to the end of the string.
	virtual void CursorEnd(void);
	/// Move the cursor one position to the left.
	virtual void CursorLeft(void);
	/// Move the cursor one position to the right.
	virtual void CursorRight(void);
	/// Delete the selection or the character to the left of the cursor position
	virtual void DeleteLeft(void);
	/// Delete the selection or the character to the right of the cursor position
	virtual void DeleteRight(void);

	void SetSelectionStart(int Value);
	int GetSelectionStart(void) const { return SelStart; }
	void SetSelectionEnd(int Value);
	int GetSelectionEnd(void) const { return SelEnd; }
	int GetSelectionLength(void);
	TString GetSelection(void);
	void ReplaceSelectedSubstring(TString Str);
	void ReplaceSelectedSubstring(const char* Str);
		
protected:
	// Events

protected:
	TString UpperCase(TString& String);
	TString LowerCase(TString& String);
	/// Get maximum valid cursor position.
	int GetMaxCursorPos() const;
};

/** 
	@brief Specify if the control is readonly or not.
	The text of a readonly edit control can not be modified.
	@param Value <code>true</code>, for a readonly control, 
	             <code>false</code> for a non reaonly control.
*/
inline void TCustomEdit::SetReadOnly(bool Value) { ReadOnly = Value; }
    
/** 
	Retrieve the ReadOnly state of the control.
	@param Value <code>true</code>, if the control is readonly, 
	             <code>false</code> if the control is not readonly.
*/
inline bool TCustomEdit::GetReadOnly(void) const { return ReadOnly; }
	
/** 
	@brief Specify if the text will be selected when the control will receive focus.
	@param Value <code>true</code>, if the control's text should be selected when the 
		   control will receive focus <code>false</code> if not.
*/
inline void TCustomEdit::SetAutoSelect(bool Value) { AutoSelect = Value; }
	
/** 
	Retrieve the value of the control's AutoSelect property.
	@see <code>SetAutoSelect</code>
*/
inline bool TCustomEdit::GetAutoSelect(void) const { return AutoSelect; }

/** 
	@brief Specify if the selected text will remain selected after
	       the control will loose the focus.
	@param Value <code>true</code>, if the control's text should stay 
                 selected even after the control will loose the focus
	             <code>false</code> if not.
*/
inline void TCustomEdit::SetHideSelection(bool Value) { HideSelection = Value; }
	
/** 
	Retrieve the value of the control's HideSelection property.
	@see <code>SetHideSelection</code>
*/
inline bool TCustomEdit::GetHideSelection(void) const { return HideSelection; }
	
/** 
	Retrieve the character's chase of the text.
	@see <code>SetCharCase</code>
*/
inline TEditCharCase TCustomEdit::GetCharCase(void) const { return CharCase; }
	
/** 
	Retrieve the value of the control's AutoSize property.
	@see <code>SetAutoSize</code>
*/
inline bool TCustomEdit::GetAutoSize(void) const { return AutoSize; }
		
/** 
	Retrieve the character used for password edit control.
	@see <code>SetPasswordChar</code>
*/
inline char TCustomEdit::GetPasswordChar(void) const { return PasswordChar; }

//-------------------------------------------------------------------
#endif 


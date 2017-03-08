#ifndef T_EDIT_H
#define T_EDIT_H
//-------------------------------------------------------------------
//  CLASS
//  TEdit
//
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TEdit
#include "guide/ndefdllclass.h"

#ifndef T_CUSTOMEDIT_H
#include "guide/customedit.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TEdit : public TCustomEdit
{
	TString VisibleText;
    TPoint CaretPos;
    TRect SelRect;
    int LeftCharIndex;
	int TextMovement;
    
public:
	TEdit();
	virtual ~TEdit();
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

	/// Set cursor position.
	virtual void SetCursorPos(int Value);
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

protected:
	// Events	
	virtual void OnPaint(void);
    virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	virtual void OnKeyDown(unsigned short &Key, const TShiftState& Shift);
	virtual void OnKeyUp(unsigned short &Key, const TShiftState& Shift);
	virtual void OnKeyPress(char &Key);
	virtual void OnCaptureChanged(void);
	virtual void OnTextChanged(void);
	virtual void OnFontChanged(void);
	virtual void OnActivate(void);
	virtual void OnDeactivate(void);
	virtual void OnSize(int AWidth, int AHeight);

private:
	TString GetSubstring(int X);
    int GetCharIndex(int X);
    int GetVisibleTextCharIndex(int X);
    void UpdateVisibleText(void);
    void UpdateCaret(void);
    void UpdateSelectionRect(void);
    
    void MoveTextLeft(TString AString);
    void MoveTextRight(TString AString);
};

//-------------------------------------------------------------------
#endif

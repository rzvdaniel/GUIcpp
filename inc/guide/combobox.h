#ifndef T_COMBOBOX_H
#define T_COMBOBOX_H
//-------------------------------------------------------------------
//  CLASS
//  TComboBox
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TComboBox
#include "guide/ndefdllclass.h"

#ifndef T_EDIT_H
#include "guide/edit.h"
#endif

#ifndef T_CUSTOMBUTTON_H
#include "guide/custombutton.h"
#endif

#ifndef T_LISTBOX_H
#include "guide/listbox.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TComboBoxButton : public TCustomButton
{
	
public:
	TComboBoxButton() {}
	virtual ~TComboBoxButton() {}
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void Create(TComponent* AOwner, TRect Rect);

protected:
	// Events
	virtual void OnPaint(void);
};

//-------------------------------------------------------------------
class TComboBox;
class N_PUBLIC TComboListBox : public TCustomListBox
{
public:
	friend class TComboBox;

private:
	TComboBox* ComboBox;

public:
	TComboListBox();
	virtual ~TComboListBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	virtual void ApplySkin(TObject* Object);
	virtual void Assign(TObject* Object);

	void SetScrollStyle(TScrollStyle Value);

protected:
	// Events
	virtual void OnPaint(void); 
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	virtual void OnClick(void);

protected:
	virtual void InsertingItem(int Index);
	virtual void RemovingItem(int Index);
	virtual void ClearingItems(void);
};

//-------------------------------------------------------------------

class N_PUBLIC TComboBox : public TEdit
{
protected:
	TComboBoxButton* Button;
	TComboListBox* ListBox;

public:
	TComboBox();
	virtual ~TComboBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	TComboListBox* GetListBox(void) const { return ListBox; }
		
protected:
	// Events
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnButtonClick(void);
};

//-------------------------------------------------------------------
#endif 


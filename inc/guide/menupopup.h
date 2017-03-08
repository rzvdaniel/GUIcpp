#ifndef T_MENUPOPUP_H
#define T_MENUPOPUP_H
//-------------------------------------------------------------------
//  CLASS
//  TPopupMenu
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TPopupMenu
#include "guide/ndefdllclass.h"

#ifndef T_MENU_H
#include "guide/menu.h"
#endif

//-------------------------------------------------------------------
//  TPopupMenuItem
//-------------------------------------------------------------------
class N_PUBLIC TPopupMenuItem : public TMenuItem
{
public:
	TPopupMenuItem();
	virtual ~TPopupMenuItem();
	virtual void Create(TComponent* AOwner);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnClick(void);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);
	virtual void OnTextChanged(void); 
	virtual void OnCaptureChanged(void);

};

//-------------------------------------------------------------------
enum TPopupAlignment { paLeft, paRight, paCenter };

//-------------------------------------------------------------------
class N_PUBLIC TPopupMenu : public TMenu
{
	TPopupAlignment Alignment;

public:
	TPopupMenu();
	virtual ~TPopupMenu();	
	virtual void Create(TComponent* AOwner);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);
	
	void SetAlignment(TPopupAlignment Value) { Alignment = Value; }
	TPopupAlignment GetAlignment(void) const { return Alignment; }

protected:	
	virtual void InsertingItem(int Index);
	virtual void RemovingItem(int Index);
	virtual void ClearingItems(void);

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnSize(int AWidth, int AHeight);
	virtual void OnShow(void);
};

//-------------------------------------------------------------------
#endif 


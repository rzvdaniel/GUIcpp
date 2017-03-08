#ifndef T_MENUMAIN_H
#define T_MENUMAIN_H
//-------------------------------------------------------------------
//  CLASS
//  TMainMenuItem
//  TMainMenu
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TMainMenu
#include "guide/ndefdllclass.h"

#ifndef T_MENU_H
#include "guide/menu.h"
#endif

//-------------------------------------------------------------------
//  TMainMenu
//-------------------------------------------------------------------
class N_PUBLIC TMainMenu : public TMenu
{		
	friend class TMainMenuItem;

	bool Clicked;
	TMenu* VisibleMenu;

public:
	TMainMenu();
	virtual ~TMainMenu();	
	virtual void Create(TComponent* AOwner, TAlign Alignment = alTop);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

	void SetAlign(TAlign Value);
	void SetClicked(bool Value) { Clicked = Value; }
	bool GetClicked(void) const { return Clicked; }

protected:	
	virtual void InsertingItem(int Index);
	virtual void RemovingItem(int Index);
	virtual void ClearingItems(void);
	
protected:
	// Events
	virtual void OnPaint(void);	

private:
	TMenu* GetVisibleMenu(void) { return VisibleMenu; }
	void SetVisibleMenu(TMenu* AMenu) { VisibleMenu = AMenu; }
};

//-------------------------------------------------------------------
//  TMainMenuItem
//-------------------------------------------------------------------
class N_PUBLIC TMainMenuItem : public TMenuItem
{

public:
	TMainMenuItem();
	virtual ~TMainMenuItem();
	virtual void Create(TComponent* AOwner);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnClick(void);
	virtual void OnKeyDown(unsigned short &Key, const TShiftState& Shift);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);	  
	virtual void OnTextChanged(void);  
	virtual void OnCaptureChanged(void);
};

//-------------------------------------------------------------------
#endif 


#ifndef T_MENU_H
#define T_MENU_H
//-------------------------------------------------------------------
//  CLASS
//  TMenu
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TMenu
#include "guide/ndefdllclass.h"

#ifndef T_COLLECTION_H
#include "guide/collection.h"
#endif

#ifndef T_WINCONTROL_H
#include "guide/wincontrol.h"
#endif

#ifndef T_IMAGE_H
#include "guide/image.h"
#endif

enum TMenuAlignment { maLeft, maTop, maRight, maBottom };

//-------------------------------------------------------------------
class TMenu;
class N_PUBLIC TMenuItem : public TWinControl, public TCollectionItem
{
	int ExtraWidth;
	int ExtraHeight;
	TColor CaptionColorSelected;
	TColor CaptionColorUnselected;
	TColor CaptionColorDisabled;

protected:
    TMenu* Menu;
	TMenuAlignment MenuAlignment;   

public:
	TMenuItem();
	virtual ~TMenuItem();
	virtual void Create(TComponent* AOwner);
	virtual void ParseSkin(TiXmlElement* XmlElement);

	void SetExtraWidth(int Value) { ExtraWidth = Value; }
	int GetExtraWidth(void) const { return ExtraWidth; }

	void SetExtraHeight(int Value) { ExtraHeight = Value; }
	int GetExtraHeight(void) const { return ExtraHeight; }

	void SetCaptionColorSelected(TColor Value) { CaptionColorSelected = Value; }
	TColor GetCaptionColorSelected(void) const { return CaptionColorSelected; }
	
	void SetCaptionColorUnselected(TColor Value) { CaptionColorUnselected = Value; }
	TColor GetCaptionColorUnselected(void) const { return CaptionColorUnselected; }

	void SetCaptionColorDisabled(TColor Value) { CaptionColorDisabled = Value; }
	TColor GetCaptionColorDisabled(void) const { return CaptionColorDisabled; }

    void SetMenu(TMenu* AMenu);
	TMenu* GetMenu(void) const { return Menu; }
	
	void SetMenuAlignment(TMenuAlignment Value) { MenuAlignment = Value; }
	TMenuAlignment GetMenuAlignment(void) const { return MenuAlignment; }
    
protected:
	// Events
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);
};

//-------------------------------------------------------------------
class TMenu;
class N_PUBLIC TMenuItems : public TCollection
{
	TMenu* Menu;

public:
	TMenuItems(TMenu* AMenu);
	virtual ~TMenuItems() {}

	TMenu* GetMenu(void) const { return Menu; }

	void Insert(int Index, TCollectionItem* Item);
	void Append(TCollectionItem* Item);
	void Remove(int Index);
	void Clear(void);
};

//-------------------------------------------------------------------
class N_PUBLIC TMenu : public TWinControl 
{	
	friend class TMenuItems;
	TMenuItem* SelectedItem;

public:
	TMenuItems* Items;

public:
	TMenu();
	virtual ~TMenu();	
	virtual void Create(TComponent* AOwner);
		
	void SetSelectedItem(TMenuItem* ASelectedItem) { SelectedItem = ASelectedItem; }
	TMenuItem* GetSelectedItem(void) const { return SelectedItem; }

protected:
	virtual void InsertingItem(int Index);
	virtual void RemovingItem(int Index);
	virtual void ClearingItems(void);

protected:
	// Events
	virtual void OnHide(void);  
};

//-------------------------------------------------------------------
#endif 


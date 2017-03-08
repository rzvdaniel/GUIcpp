#ifndef T_CUSTOMLISTBOX_H
#define T_CUSTOMLISTBOX_H
//-------------------------------------------------------------------
//  CLASS
//  TCustomListBox
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TCustomListBox
#include "guide/ndefdllclass.h"

#ifndef T_STRINGS_H
#include "guide/strings.h"
#endif

#ifndef T_SCROLLWINCTRL_H
#include "guide/scrollwinctrl.h"
#endif

enum TListBoxItemStates { liSelected, liFocused, liDisabled };

typedef stl::set< TListBoxItemStates, stl::less<TListBoxItemStates> > TListBoxItemState;

//-------------------------------------------------------------------
class N_PUBLIC TListBoxItem : public TStringItem
{	
	TListBoxItemState State;
	TTexture* Icon;

public:
	TListBoxItem();
	virtual ~TListBoxItem() {}

	TListBoxItemState GetState(void) const { return State; }

	void InsertState(TListBoxItemStates Value);
	void RemoveState(TListBoxItemStates Value);	
	bool HasState(TListBoxItemStates Value);

	void SetIcon(TTexture* AIcon) { Icon = AIcon; }
	TTexture* GetIcon(void) const { return Icon; }
};

//-------------------------------------------------------------------
class TCustomListBox;
class N_PUBLIC TListBoxItems : public TStrings
{
	TCustomListBox* ListBox;

public:
	TListBoxItems(TCustomListBox* AListBox);
	virtual ~TListBoxItems() {}

	TCustomListBox* GetListBox(void) const { return ListBox; }

	void Insert(int Index, TCollectionItem* Item);
	void Append(TCollectionItem* Item);
	void Remove(int Index);
	void Clear(void);
};

enum TListBoxStyle { lbStandard, lbOwnerDrawFixed, lbOwnerDrawVariable };


typedef CBFunctor3<TWinControl*, int, int&> TMeasureItemEvent;
typedef CBFunctor4<TWinControl*, int, const TRect&, const TListBoxItemState&> TDrawItemEvent;

//-------------------------------------------------------------------
class N_PUBLIC TCustomListBox : public TScrollingWinControl
{
	friend class TListBoxItems;

	/// Determines whether the user can select more than one element at a time from the list box	
	bool MultiSelect;
	/// Determines if the user can select a sequential range of items in the list box.	
	bool ExtendedSelect;
	/// The height of an item
	float ItemHeight;
	/// Determines whether the list box is standard or owner-draw
	TListBoxStyle Style;
	/// Focused item
	TListBoxItem* FocusedItem;

protected:
	int FirstItemIndex;

public:
	/// Items of the list box
	TListBoxItems* Items;

public:
	TMeasureItemEvent FOnMeasureItem;
	TDrawItemEvent FOnDrawItem;
	TNotifyEvent FOnSelectionChange;

public:
	TCustomListBox();
	virtual ~TCustomListBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	void SetStyle(TListBoxStyle Value) { Style = Value; }
	TListBoxStyle GetStyle(void) const { return Style; }

	/// Get the item's height
	void SetItemHeight(float Value) { ItemHeight = Value; }
	float GetItemHeight(void) const { return ItemHeight; }

	/// Determines if the user can select multiple items
	void SetMultiSelect(bool Value) { MultiSelect = Value; }
	bool GetMultiSelect(void) const { return MultiSelect; }
	
	/// Determines if the user can select a sequential range of items in the list box.
	void SetExtendedSelect(bool Value) { ExtendedSelect = Value; }
	bool GetExtendedSelect(void) const { return ExtendedSelect; }
	
public:
	// Event handlers
	virtual void CMMeasureItem(int Index, int& AHeight);
	virtual void CMDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State);
	virtual void CMSelectionChange(void);

protected:
	// Events
	virtual void OnMeasureItem(int Index, int& AHeight);
	virtual void OnDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State);
	virtual void OnSelectionChange(void);

protected:
	void SetFocusedItem(TListBoxItem* AItem);
	TListBoxItem* GetFocusedItem(void) const { return FocusedItem; }
	
	int GetMaxVisibleItems(void);
	int ItemAtPos(const TPoint& Pos);
	virtual void InsertingItem(int Index);
	virtual void RemovingItem(int Index);
	virtual void ClearingItems(void);
};

//-------------------------------------------------------------------
#endif 


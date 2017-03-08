#define N_IMPLEMENTS TCustomListBox
//-------------------------------------------------------------------
//  listbox.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include <math.h>
#include "guide/customlistbox.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
/**
*/
TListBoxItem::TListBoxItem() 
{ 
	Icon = NULL; 
}

//-------------------------------------------------------------------
//  InsertState()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBoxItem::InsertState(TListBoxItemStates Value)
{
	if(!State.count(Value))
		State.insert(Value);
}

//-------------------------------------------------------------------
//  HasState()
//  08-Oct-2004   rzv   created
//-------------------------------------------------------------------
bool TListBoxItem::HasState(TListBoxItemStates Value)
{
	if(State.count(Value))
		return true;

	return false;
}

//-------------------------------------------------------------------
//  RemoveState()
//  08-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TListBoxItem::RemoveState(TListBoxItemStates Value)
{
	if(State.count(Value))
		State.erase(Value);
}

//-------------------------------------------------------------------
//  TListBoxItems()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
TListBoxItems::TListBoxItems(TCustomListBox* AListBox) 
{
	ListBox = AListBox;
}

//-------------------------------------------------------------------
//  Insert()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBoxItems::Insert(int Index, TCollectionItem* Item)
{
	TStrings::Insert(Index, Item);

	// Tell the parent list box that we're inserting a new item
	if(ListBox != NULL)
		ListBox->InsertingItem(Index);
}

//-------------------------------------------------------------------
//  Append()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBoxItems::Append(TCollectionItem* Item)
{
	TStrings::Append(Item);

	// Tell the parent list box that we're appending a new item
	if(ListBox != NULL)
		ListBox->InsertingItem(ListBox->Items->Count() - 1);
}

//-------------------------------------------------------------------
//  Remove()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBoxItems::Remove(int Index)
{	
	// Tell the parent list box that we're removing an item
	if(ListBox != NULL)
		ListBox->RemovingItem(Index);

	TStrings::Remove(Index);
}

//-------------------------------------------------------------------
//  Clear()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBoxItems::Clear(void)
{	
	// Tell the parent list box that we're clearing the items
	if(ListBox != NULL)
		ListBox->ClearingItems();

	TStrings::Clear();
}

//-------------------------------------------------------------------
//  TCustomListBox()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
TCustomListBox::TCustomListBox()
{
	MultiSelect = true;
	ExtendedSelect = false;
	ItemHeight = 0;
	FirstItemIndex = 0;
	FocusedItem = NULL;
	Style = lbStandard;
	Items = NULL;
}

//-------------------------------------------------------------------
//  ~TCustomListBox()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
TCustomListBox::~TCustomListBox()
{	
	if(Items != NULL)
		delete Items;
}

//-------------------------------------------------------------------
//  Create()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::Create(TComponent* AOwner, const TRect& Rect)
{		
	TScrollingWinControl::Create(AOwner, Rect);

	// Create the Items
	Items = new TListBoxItems(this);

	// Set the default item height to the height of font.
	// Warning! Check if we have a valid font because a TListBox
	// object is created with the Parent == Screen into the skin
	// load stage and at that moment, the Screen object does not
	// has a font, yet.
	if(GetFont() != NULL)
		ItemHeight = GetFont()->GetHeight();
}

//-------------------------------------------------------------------
//  SetFocusedItem()
//  08-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::SetFocusedItem(TListBoxItem* AItem)
{
	if(FocusedItem != NULL)
		FocusedItem->RemoveState(liFocused);
	
	if(AItem != NULL)
		AItem->InsertState(liFocused);

	FocusedItem = AItem;

	CMSelectionChange();
}

//-------------------------------------------------------------------
//  GetMaxVisibleItems()
//  28-Sep-2004   rzv   created
//-------------------------------------------------------------------
int TCustomListBox::GetMaxVisibleItems(void)
{
	int MaxVisibleItems = GetHeight()/GetItemHeight();

	if(MaxVisibleItems > Items->Count())
		MaxVisibleItems = Items->Count();

	return MaxVisibleItems;
}

//-------------------------------------------------------------------
//  ItemAtPos()
//  29-Sep-2004   rzv   created
//-------------------------------------------------------------------
int TCustomListBox::ItemAtPos(const TPoint& Pos)
{
	div_t Div = div(Pos.y - GetTextMargins().top, GetItemHeight());
	int ItemIndex = FirstItemIndex + Div.quot;

	if(ItemIndex < 0 || ItemIndex >= Items->Count())
		ItemIndex = -1;

	return ItemIndex;
}

//-------------------------------------------------------------------
//  InsertingItem()
//  28-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::InsertingItem(int Index)
{
	if(Style == lbStandard || Style == lbOwnerDrawFixed)
	{
		int ItemsHeight = Items->Count() * GetItemHeight();

		// If we have more items that the list box can display in its visible area,
		// decrease the thumb's size according with their number. If the size of the
		// thumb reach its minimum size, move it one step at the top.
		if(ItemsHeight > GetHeight())
		{
			if(VertScrollBar != NULL)
			{
				// Display both scroll bars, even if not both are necessary.
				// TODO! Display unnecessary scrollbars without thumb (as disabled). 
				if(!VertScrollBar->GetVisible())
					VertScrollBar->SetVisible(true);

				if(HorzScrollBar != NULL && !HorzScrollBar->GetVisible())
					HorzScrollBar->SetVisible(true);
								
				VertScrollBar->SetMax(VertScrollBar->GetMax() + 1);

				TScrollThumb* Thumb = VertScrollBar->GetThumb();
				Thumb->SetSize(Thumb->GetSize() - GetFont()->GetHeight());

				VertScrollBar->CMScroll(scBottom, 0);
			}
		}
	}
	else
	{
		// TODO! Manage the other styles too.
	}
}

//-------------------------------------------------------------------
//  RemovingItem()
//  29-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::RemovingItem(int Index)
{
}

//-------------------------------------------------------------------
//  ClearingItems()
//  29-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::ClearingItems(void)
{
	if(VertScrollBar != NULL)
	{
		VertScrollBar->Reset();

		if(VertScrollBar->GetVisible() == true)
			VertScrollBar->SetVisible(false);
	}

	if(HorzScrollBar != NULL)
	{
		HorzScrollBar->Reset();

		if(HorzScrollBar->GetVisible() == true)
			HorzScrollBar->SetVisible(false);
	}

	FirstItemIndex = 0;
	FocusedItem = NULL;
}

//-------------------------------------------------------------------
//  CMMeasureItem()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::CMMeasureItem(int Index, int& AHeight)
{
	if(FOnMeasureItem)
		FOnMeasureItem(this, Index, AHeight);
	else
		OnMeasureItem(Index, AHeight);
}

//-------------------------------------------------------------------
//  CMDrawItem()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::CMDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State)
{
	if(FOnDrawItem)
		FOnDrawItem(this, Index, Rect, State);
	else
		OnDrawItem(Index, Rect, State);
}

//-------------------------------------------------------------------
//  CMSelectionChange()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::CMSelectionChange(void)
{
	if(FOnSelectionChange)
		FOnSelectionChange();

	OnSelectionChange();
}

//-------------------------------------------------------------------
//  OnMeasureItem()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::OnMeasureItem(int Index, int& AHeight)
{
	if(Style == lbStandard || Style == lbOwnerDrawFixed)
		AHeight = GetItemHeight();
}

//-------------------------------------------------------------------
//  CMDrawItem()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::OnDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State)
{
	// Nothing here
}

//-------------------------------------------------------------------
//  OnSelectionChange()
//  20-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TCustomListBox::OnSelectionChange(void)
{
	// Nothing here
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



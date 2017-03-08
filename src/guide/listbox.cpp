#define N_IMPLEMENTS TListBox
//-------------------------------------------------------------------
//  listbox.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/listbox.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TListBox()
//  21-July-2002   rzv   created
//-------------------------------------------------------------------
TListBox::TListBox() 
{
}

//-------------------------------------------------------------------
//  ~TListBox()
//  21-July-2002   rzv   created
//-------------------------------------------------------------------
TListBox::~TListBox()
{	
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TListBox::Create(TComponent* AOwner, const TRect& Rect)
{
	TCustomListBox::Create(AOwner, Rect);	
    
	ApplySkin(Skin->ListBox);

	SetCurrentGrid(GetGrid("Active"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::Assign(TObject* Object)
{
	TCustomListBox::Assign(Object);
}

//-------------------------------------------------------------------
/**
*/
void TListBox::ApplySkin(TObject* Object)
{
	TCustomListBox::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  SetScrollStyle()
//  25-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TListBox::SetScrollStyle(TScrollStyle Value)
{
	// Let the base TScrollingWinControl class to create scroll bars.
	TScrollingWinControl::SetScrollStyle(Value);

	// We ca use scroll bars, if any
	if(VertScrollBar != NULL)
		VertScrollBar->FOnScroll = makeFunctor((TScrollEvent*)0,*this, &TListBox::OnVertScroll);

	if(HorzScrollBar != NULL)
		HorzScrollBar->FOnScroll = makeFunctor((TScrollEvent*)0,*this, &TListBox::OnHorzScroll);
}

//-------------------------------------------------------------------
//  OnPaint()
//  21-July-2002   rzv   created
//-------------------------------------------------------------------
void TListBox::OnPaint(void) 
{
	// Render current grid
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	int Offset = 0;

	if(GetStyle() == lbStandard)
	{
		// Set the pen color for text
		Canvas->Pen->SetColor(GetCaptionColor());

		for(int i=FirstItemIndex; i<FirstItemIndex + GetMaxVisibleItems(); i++)
		{
			TListBoxItem* Item = (TListBoxItem*)Items->GetItem(i);
			
			// Selected item rect
			if(GetActive() && Item->HasState(liSelected))
			{
				Canvas->Brush->SetTexture(NULL);
				Canvas->Brush->SetColor(GetSelectionColor());
				Canvas->FillRect(GetTextMargins().left, Offset + GetTextMargins().top, GetWidth() - GetTextMargins().left - GetTextMargins().right, GetItemHeight());
			}

			// Item string
			Canvas->Pen->SetStyle(psSolid);
			Canvas->Text(GetTextMargins().left, GetTextMargins().top + Offset, Item->GetString());

			Offset += GetItemHeight();
		}	
	}
	else if(GetStyle() == lbOwnerDrawFixed)
	{
		for(int i=FirstItemIndex; i<FirstItemIndex + GetMaxVisibleItems(); i++)
		{			
			TListBoxItem* Item = (TListBoxItem*)Items->GetItem(i);
			CMDrawItem(i, TRect(GetTextMargins().left, GetTextMargins().top + Offset, GetWidth() - GetTextMargins().left - GetTextMargins().right, GetItemHeight()), Item->GetState());		
			Offset += GetItemHeight();
		}	
	}
	else if(GetStyle() == lbOwnerDrawVariable)
	{
		for(int i=FirstItemIndex; i<FirstItemIndex + GetMaxVisibleItems(); i++)
		{			
			TListBoxItem* Item = (TListBoxItem*)Items->GetItem(i);
			int AHeight = GetItemHeight();
			CMMeasureItem(i, AHeight);
			CMDrawItem(i, TRect(GetTextMargins().left, GetTextMargins().top + Offset, GetWidth() - GetTextMargins().left - GetTextMargins().right, AHeight), Item->GetState());		
			Offset += AHeight;
		}	
	}

	TCustomListBox::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  29-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{	
	TCustomListBox::OnMouseDown(Button, Shift, X, Y);

	// Get the item index the cursor is over it
	int Index = ItemAtPos(TPoint(X,Y));
	
	// Get the item at specified index
	TListBoxItem* Item = (TListBoxItem*)Items->GetItem(Index);

	if(Item == NULL)
		return;
	
	// Shift key is pressed
	if(Shift.count(ssShift) && GetMultiSelect() == true)
	{
		if(GetFocusedItem() != NULL)
		{		
			int FocusedItemIndex = GetFocusedItem()->GetIndex();
			if(FocusedItemIndex > Index)
			{
				for(int i=Index; i<=FocusedItemIndex; i++)
				{
					TListBoxItem* ListItem = (TListBoxItem*)Items->GetItem(i);
					ListItem->InsertState(liSelected);
				}
			}
			else
			{	
				for(int i=FocusedItemIndex; i<=Index; i++)
				{
					TListBoxItem* ListItem = (TListBoxItem*)Items->GetItem(i);
					ListItem->InsertState(liSelected);
				}	
			}
		}
	}
	// Ctrl key is pressed
	else if(Shift.count(ssCtrl) && GetMultiSelect() == true)
	{
		if(Item->HasState(liSelected))
			Item->RemoveState(liSelected);
		else
			Item->InsertState(liSelected);
	}
	// No Shift or Ctrl key is pressed
	else
	{
		// Unselect all items
		for(int i=0; i<Items->Count(); i++)
		{
			TListBoxItem* AItem = (TListBoxItem*)Items->GetItem(i);
			if(AItem->HasState(liSelected))
				AItem->RemoveState(liSelected);
		}
		
		// Select the item under the mouse cursor
		Item->InsertState(liSelected);
	}

	// Set focused item
	SetFocusedItem(Item);
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  29-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TCustomListBox::OnMouseUp(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  29-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::OnMouseMove(const TShiftState& Shift, int X, int Y)
{
	TCustomListBox::OnMouseMove(Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnActivate()
//  28-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::OnActivate(void)
{
	TCustomListBox::OnActivate();
	
	SetCurrentGrid(GetGrid("Active"));	
}

//-------------------------------------------------------------------
//  OnDeactivate()
//  28-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::OnDeactivate(void)
{	
	TCustomListBox::OnDeactivate();
	
	SetCurrentGrid(GetGrid("Inactive"));	
}

//-------------------------------------------------------------------
//  CMDrawItem()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::OnDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State)
{
	TCustomListBox::OnDrawItem(Index, Rect, State);
}

//-------------------------------------------------------------------
//  OnVertScroll()
//  28-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::OnVertScroll(TScrollCode ScrollCode, int &ScrollPos)
{
	FirstItemIndex = ScrollPos;	
}

//-------------------------------------------------------------------
//  OnHorzScroll()
//  28-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TListBox::OnHorzScroll(TScrollCode ScrollCode, int &ScrollPos)
{
}

//-------------------------------------------------------------------
/**
*/
void TListBox::ParseSkin(TiXmlElement* XmlElement)
{
	TCustomListBox::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


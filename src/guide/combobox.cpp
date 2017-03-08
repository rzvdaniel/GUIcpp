#define N_IMPLEMENTS TComboBox
//-------------------------------------------------------------------
//  combobox.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/combobox.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//
//  CLASS TComboBoxButton
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//  Create()
//  30-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TComboBoxButton::Create(TComponent* AOwner, TRect Rect)
{
	TCustomButton::Create(AOwner, Rect);

	ApplySkin(Skin->ComboBoxButton);
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TComboBoxButton::Assign(TObject* Object)
{
	TCustomButton::Assign(Object);
}

//-------------------------------------------------------------------
void TComboBoxButton::ApplySkin(TObject* Object)
{
	TCustomButton::ApplySkin(Object);

	SetCurrentGrid(GetGrid("Active"));
}

//-------------------------------------------------------------------
//  OnPaint()
//  30-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TComboBoxButton::OnPaint(void)
{
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	TCustomButton::OnPaint();
}

//-------------------------------------------------------------------
//
//  CLASS TComboListBox
//
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//  TComboListBox()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
TComboListBox::TComboListBox()
{
	ComboBox = NULL;
}

//-------------------------------------------------------------------
//  ~TComboListBox()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
TComboListBox::~TComboListBox()
{
}

//-------------------------------------------------------------------
//  Create()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TComboListBox::Create(TComponent* AOwner, const TRect& Rect)
{
	TCustomListBox::Create(AOwner, Rect);

	ApplySkin(Skin->ComboListBox);
	
	SetScrollStyle(ssNone);
	SetMultiSelect(false);
	SetCurrentGrid(GetGrid("Normal"));
}

//-------------------------------------------------------------------
void TComboListBox::Assign(TObject* Object)
{
	TCustomListBox::Assign(Object);
}

//-------------------------------------------------------------------
void TComboListBox::ApplySkin(TObject* Object)
{
	TCustomListBox::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  SetScrollStyle()
//  06-Jan-2004   rzv   created
//-------------------------------------------------------------------
void TComboListBox::SetScrollStyle(TScrollStyle Value)
{
	// Don't let the user to accidentaly change the scroll style
	// to something different from ssNone. We don't need scroll
	// bars for this control. So, don't call the base class function:
	// TCustomListBox::SetScrollStyle(Value);
}

//-------------------------------------------------------------------
//  InsertingItem()
//  01-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TComboListBox::InsertingItem(int Index)
{	
	int ItemHeight;
	CMMeasureItem(Index, ItemHeight);
	
	SetHeight(GetHeight() + ItemHeight);
}

//-------------------------------------------------------------------
//  RemovingItem()
//  01-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TComboListBox::RemovingItem(int Index)
{
	int ItemHeight;
	CMMeasureItem(Index, ItemHeight);
	
	SetHeight(GetHeight() - ItemHeight);
}

//-------------------------------------------------------------------
//  ClearingItems()
//  01-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TComboListBox::ClearingItems(void)
{
	SetHeight(0);
}

//-------------------------------------------------------------------
//  OnPaint()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TComboListBox::OnPaint(void) 
{
	// Render current grid
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	int Offset = 0;

	if(GetStyle() == lbStandard)
	{
		// Set the pen color for string rendering
		Canvas->Pen->SetColor(clBlack);

		for(int i=FirstItemIndex; i<FirstItemIndex + GetMaxVisibleItems(); i++)
		{
			TListBoxItem* Item = (TListBoxItem*)Items->GetItem(i);
			
			// Focused item rect
			if(GetActive() && Item->HasState(liFocused))
			{
				Canvas->Brush->SetTexture(NULL);
				Canvas->Brush->SetColor(GetSelectionColor());
				Canvas->FillRect(0, Offset, GetWidth(), GetItemHeight());	
			}
			
			// Item string
			Canvas->Text(GetTextMargins().left, GetTextMargins().top + Offset, Item->GetString());

			Offset += GetItemHeight();
		}	
	}
	else if(GetStyle() == lbOwnerDrawFixed)
	{
		for(int i=0; i<Items->Count(); i++)
		{			
			TListBoxItem* Item = (TListBoxItem*)Items->GetItem(i);
			CMDrawItem(i, TRect(0, Offset, GetWidth(), GetItemHeight()), Item->GetState());		
			Offset += GetItemHeight();
		}	
	}
	else if(GetStyle() == lbOwnerDrawVariable)
	{
		for(int i=0; i<Items->Count(); i++)
		{			
			TListBoxItem* Item = (TListBoxItem*)Items->GetItem(i);
			int AHeight = GetItemHeight();
			CMMeasureItem(i, AHeight);
			CMDrawItem(i, TRect(0, Offset, GetWidth(), AHeight), Item->GetState());		
			Offset += AHeight;
		}	
	}

	TCustomListBox::OnPaint();
}

//-------------------------------------------------------------------
//  OnClick()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TComboListBox::OnClick(void)
{
	if(GetFocusedItem() != NULL)
		ComboBox->SetText(GetFocusedItem()->GetString());
		
	SetVisible(false);
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TComboListBox::OnMouseMove(const TShiftState& Shift, int X, int Y)
{	
	int Index = ItemAtPos(TPoint(X, Y));
	TListBoxItem* Item = (TListBoxItem*)Items->GetItem(Index);

	if(Item != NULL)
		SetFocusedItem(Item);

	TCustomListBox::OnMouseMove(Shift, X, Y);
}

//-------------------------------------------------------------------
//
//  CLASS TComboBox
//
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//  TComboBox()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
TComboBox::TComboBox()
{
}

//-------------------------------------------------------------------
//  ~TComboBox()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
TComboBox::~TComboBox()
{
}

//-------------------------------------------------------------------
//  Create()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TComboBox::Create(TComponent* AOwner, const TRect& Rect)
{
	TCustomEdit::Create(AOwner, Rect);

	ApplySkin(Skin->ComboBox);
	
	// Default value for button
	int ButtonWidth = 22;
	// If defined in Skin fiel, overwrite
	if(Skin->ComboBoxButton != NULL)
		ButtonWidth = Skin->ComboBoxButton->GetWidth();

	// Create the combobox button
	Button = new TComboBoxButton;
	Button->Create(this, TRect(GetWidth() - ButtonWidth, 0, ButtonWidth, GetHeight()));
	Button->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TComboBox::OnButtonClick);

	ListBox = new TComboListBox;
	ListBox->Create(AOwner, TRect(GetLeft(), GetTop() + GetHeight(), GetWidth(), 0));
	ListBox->SetVisible(false);
	ListBox->ComboBox = this;

	//SetAutoSelect(true);
	SetCurrentGrid(GetGrid("Unfocused"));
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TComboBox::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TEdit::OnMouseDown(Button, Shift, X, Y);

	SetActiveControl(NULL);
}

//-------------------------------------------------------------------
//  OnButtonClick()
//  12-Nov-2003   rzv   created
//-------------------------------------------------------------------
void TComboBox::OnButtonClick(void)
{
	ListBox->SetVisible(!ListBox->GetVisible());
	if(ListBox->GetVisible())
	{
		ListBox->SetCapture();
		ListBox->BringToFront();
		TWinControl* ParentCtrl = (TWinControl*)GetParent();
		ParentCtrl->SetActiveControl(ListBox);
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



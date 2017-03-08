#define N_IMPLEMENTS TMenu
//-------------------------------------------------------------------
//  menu.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/menu.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TMenuItem
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//  TMenuItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMenuItem::TMenuItem()
{
	ExtraWidth = 0;
	ExtraHeight = 0;
	CaptionColorSelected = clWhite;
	CaptionColorUnselected = clBlack;
	CaptionColorDisabled = clGray;
	Menu = NULL;
	MenuAlignment = maBottom;
}

//-------------------------------------------------------------------
//  ~TMenuItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMenuItem::~TMenuItem()
{
}

//-------------------------------------------------------------------
//  Create()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenuItem::Create(TComponent* AOwner)
{
	TWinControl::Create(AOwner, TRect(0,0,0,0));
}

//-------------------------------------------------------------------
//  SetMenu()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenuItem::SetMenu(TMenu* AMenu) 
{ 	
	Menu = AMenu; 

	if(Menu != NULL)
	{
		Menu->SetVisible(false);

		TControl* CtrlParent = (TControl*)GetParent();
		if(CtrlParent != NULL)
		{
			switch(MenuAlignment)
			{
			case maBottom:
				Menu->SetLeft(CtrlParent->GetLeft() + GetLeft());
				Menu->SetTop(CtrlParent->GetTop() + GetTop() + GetHeight());
				break;
			case maTop:
				Menu->SetLeft(CtrlParent->GetLeft() + GetLeft());
				Menu->SetTop(CtrlParent->GetTop() + GetTop() - Menu->GetHeight());
				break;
			case maRight:
				Menu->SetLeft(CtrlParent->GetLeft() + GetLeft() + GetWidth());
				Menu->SetTop(CtrlParent->GetTop() + GetTop());
				break;
			case maLeft:
				Menu->SetLeft(CtrlParent->GetLeft() + GetLeft() - Menu->GetWidth());
				Menu->SetTop(CtrlParent->GetTop() + GetTop());
				break;
			}
		}
	}		
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenuItem::OnMouseMove(const TShiftState& Shift, int X, int Y)
{
	TWinControl::OnMouseMove(Shift, X, Y);
}

//-------------------------------------------------------------------
//  ParseSkin()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenuItem::ParseSkin(TiXmlElement* XmlElement)
{
	TWinControl::ParseSkin(XmlElement);

	const char *value = NULL;

	// Set the extra width
	value = XmlElement->Attribute("ExtraWidth");
	if(value != NULL)
		sscanf(value, "%d", &ExtraWidth);

	// Set the extra height
	value = XmlElement->Attribute("ExtraHeight");
	if(value != NULL)
		sscanf(value, "%d", &ExtraHeight);

	// Set the caption color selected
	value = XmlElement->Attribute("CaptionColorSelected");
	if(value != NULL)
		sscanf(value, "%x", &CaptionColorSelected);

	// Set the caption color unselected
	value = XmlElement->Attribute("CaptionColorUnselected");
	if(value != NULL)
		sscanf(value, "%x", &CaptionColorUnselected);

	// Set the caption color disabled
	value = XmlElement->Attribute("CaptionColorDisabled");
	if(value != NULL)
		sscanf(value, "%x", &CaptionColorDisabled);
}

//-------------------------------------------------------------------
//  TMenuItems
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//  TMenuItems()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMenuItems::TMenuItems(TMenu* AMenu) 
{
	Menu = AMenu;
}

//-------------------------------------------------------------------
//  Insert()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenuItems::Insert(int Index, TCollectionItem* Item)
{
	TCollection::Insert(Index, Item);

	// Tell the parent menu that we are inserting a new item
	if(Menu != NULL)
		Menu->InsertingItem(Index);
}

//-------------------------------------------------------------------
//  Append()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenuItems::Append(TCollectionItem* Item)
{
	TCollection::Append(Item);

	// Tell the parent menu that we're appending a new item
	if(Menu != NULL)
		Menu->InsertingItem(Menu->Items->Count() - 1);
}

//-------------------------------------------------------------------
//  Remove()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenuItems::Remove(int Index)
{	
	// Tell the parent menu that we're removing an item
	if(Menu != NULL)
		Menu->RemovingItem(Index);

	TCollection::Remove(Index);
}

//-------------------------------------------------------------------
//  Clear()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenuItems::Clear(void)
{	
	// Tell the parent menu that we're clearing the items
	if(Menu != NULL)
		Menu->ClearingItems();

	TCollection::Clear();
}


//-------------------------------------------------------------------
//  TMenu
//-------------------------------------------------------------------



//-------------------------------------------------------------------
//  TMenu()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMenu::TMenu()
{
	Items = NULL;
	SelectedItem = NULL;
}

//-------------------------------------------------------------------
//  ~TMenu()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMenu::~TMenu()
{
	if(Items != NULL)
		delete Items;
}

//-------------------------------------------------------------------
//  Create()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenu::Create(TComponent* AOwner)
{	
	TWinControl::Create(AOwner, TRect(0,0,0,0));
	
	// Create the Items
	Items = new TMenuItems(this);
}

//-------------------------------------------------------------------
//  InsertingItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenu::InsertingItem(int Index)
{
	TMenuItem* Item = (TMenuItem*)Items->GetItem(Index);
	Item->SetParent(this);
}

//-------------------------------------------------------------------
//  RemovingItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenu::RemovingItem(int Index)
{
}

//-------------------------------------------------------------------
//  ClearingItems()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenu::ClearingItems(void)
{
}

//-------------------------------------------------------------------
//  OnShow()
//  05-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMenu::OnHide(void)
{
	TWinControl::OnHide();
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



#define N_IMPLEMENTS TPopupMenu
//-------------------------------------------------------------------
//  menupopup.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/menupopup.h"
#include "guide/menumain.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TPopupMenuItem
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//  TPopupMenuItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TPopupMenuItem::TPopupMenuItem()
{
}

//-------------------------------------------------------------------
//  ~TPopupMenuItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TPopupMenuItem::~TPopupMenuItem()
{
}

//-------------------------------------------------------------------
//  Create()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenuItem::Create(TComponent* AOwner)
{
	TMenuItem::Create(AOwner);

	ApplySkin(Skin->PopupMenuItem);
	
	SetMenuAlignment(maRight);
	SetCurrentGrid(GetGrid("Unselected"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenuItem::Assign(TObject* Object)
{
	TMenuItem::Assign(Object);
}

//-------------------------------------------------------------------
void TPopupMenuItem::ApplySkin(TObject* Object)
{
	TMenuItem::ApplySkin(Object);

	TPopupMenuItem* AControl = (TPopupMenuItem*)Object;
	if(AControl != NULL)
	{
		SetExtraWidth(AControl->GetExtraWidth());
		SetExtraHeight(AControl->GetExtraHeight());
		SetCaptionColorSelected(AControl->GetCaptionColorSelected());
		SetCaptionColorUnselected(AControl->GetCaptionColorUnselected());
	}
}

//-------------------------------------------------------------------
//  OnPaint()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenuItem::OnPaint(void) 
{
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	CaptionY = (GetHeight() - CaptionHeight)/2;

	// Paint caption
	Canvas->Pen->SetColor(GetCaptionColor());	
	Canvas->Text(GetExtraWidth()/2, CaptionY, GetCaption());	

    TMenuItem::OnPaint();	
}

//-------------------------------------------------------------------
//  OnClick()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenuItem::OnClick(void)
{		
	TMenuItem::OnClick();

	// Hide parent control (usually a popup menu)
	TControl* CtrlParent = (TControl*)GetParent();
	if(CtrlParent != NULL)
		CtrlParent->Hide();
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenuItem::OnMouseMove(const TShiftState& Shift, int X, int Y)
{	
	TMenuItem::OnMouseMove(Shift, X, Y);
	
	if(!GetCaptured())
	{
		SetCapture();	
		SetCaptionColor(GetCaptionColorSelected());

		if(GetGrid("Selected") != NULL)
			SetCurrentGrid(GetGrid("Selected"));
	}	
	else
	{
		ControlToScreen(X, Y);
		TRect Rect = GetControlRect();		
		if(!Rect.PtInRect(TPoint(X, Y)))
			ReleaseCapture();	
	}
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenuItem::OnTextChanged(void)
{
	TMenuItem::OnTextChanged();
	
	// Adjust the width and height
	SetWidth(CaptionWidth + GetExtraWidth());
	SetHeight(CaptionHeight + GetExtraHeight());
}

//-------------------------------------------------------------------
//  OnCaptureChanged()
//  07-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenuItem::OnCaptureChanged(void)
{
	TMenuItem::OnCaptureChanged();	
	
	if(GetGrid("Unselected") != NULL)
		SetCurrentGrid(GetGrid("Unselected"));

	SetCaptionColor(GetCaptionColorUnselected());
}

//-------------------------------------------------------------------
//  ParseSkin()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenuItem::ParseSkin(TiXmlElement* XmlElement)
{
	TMenuItem::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  TPopupMenu
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//  TPopupMenu()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TPopupMenu::TPopupMenu()
{
	Alignment = paLeft;
}

//-------------------------------------------------------------------
//  ~TPopupMenu()
//  08-Aug-2003   rzv   created
//-------------------------------------------------------------------
TPopupMenu::~TPopupMenu()
{
}

//-------------------------------------------------------------------
//  Create()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::Create(TComponent* AOwner)
{
	TMenu::Create(AOwner);

	SetVisible(false);

	ApplySkin(Skin->PopupMenu);	
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::Assign(TObject* Object)
{
	TMenu::Assign(Object);
}

//-------------------------------------------------------------------
void TPopupMenu::ApplySkin(TObject* Object)
{
	TMenu::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  InsertingItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::InsertingItem(int Index)
{
	TMenu::InsertingItem(Index);

	TMenuItem* Item = (TMenuItem*)Items->GetItem(Index);
	if(Item != NULL)
	{
		// Check if the item's width is smaller than the menu width
		if(Item->GetWidth() < GetWidth())
		{
			// Set the width of the menu item to the width of the popup menu
			Item->SetWidth(GetWidth());
		}
		else
		{
			// Set the width of the popup menu to the width of the menu item
			SetWidth(Item->GetWidth());
		}

		// Adjust the menu's height
		SetHeight(GetHeight() + Item->GetHeight());
	}
}

//-------------------------------------------------------------------
//  RemovingItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::RemovingItem(int Index)
{
	TMenu::RemovingItem(Index);
}

//-------------------------------------------------------------------
//  ClearingItems()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::ClearingItems(void)
{
	TMenu::ClearingItems();
}

//-------------------------------------------------------------------
//  OnPaint()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::OnPaint(void) 
{
	TMenu::OnPaint();
}

//-------------------------------------------------------------------
//  OnShow()
//  05-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::OnShow(void)
{
	TMenu::OnShow();

	Screen->SetVisibleMenu(this);
}

//-------------------------------------------------------------------
//  OnSize()
//  05-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::OnSize(int AWidth, int AHeight)
{
	TMenu::OnSize(AWidth, AHeight);
	
	int i;

	// Adjust the width of all items
	for(i=0; i<Items->Count(); i++) 
	{
		TMenuItem* Item = (TMenuItem*)Items->GetItem(i);
		if(Item != NULL)
			Item->SetWidth(AWidth);
	}

	// Adjust the top of all items
	for(i = 0; i < Items->Count(); i++) 
	{
		TMenuItem* Item = (TMenuItem*)Items->GetItem(i);
		if(Item != NULL)
			Item->SetTop(i * Item->GetHeight());
	}
}

//-------------------------------------------------------------------
//  ParseSkin()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TPopupMenu::ParseSkin(TiXmlElement* XmlElement)
{
	TMenu::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



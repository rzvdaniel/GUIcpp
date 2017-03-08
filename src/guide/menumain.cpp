#define N_IMPLEMENTS TMainMenu
//-------------------------------------------------------------------
//  menumain.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/menumain.h"
#include "guide/menupopup.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/debug.h"
#include <typeinfo>

//-------------------------------------------------------------------
//  TMainMenu
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//  TMainMenu()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMainMenu::TMainMenu()
{
	Clicked = false;
	VisibleMenu = NULL;
}

//-------------------------------------------------------------------
//  ~TMainMenu()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMainMenu::~TMainMenu()
{
}

//-------------------------------------------------------------------
//  Create()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenu::Create(TComponent* AOwner, TAlign Alignment)
{
	TMenu::Create(AOwner);

	ApplySkin(Skin->MainMenu);	

	SetAlign(Alignment);	
	SetCurrentGrid(GetGrid("Normal"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenu::Assign(TObject* Object)
{
	TMenu::Assign(Object);
}

//-------------------------------------------------------------------
void TMainMenu::ApplySkin(TObject* Object)
{
	TMenu::ApplySkin(Object);
}

//-------------------------------------------------------------------
/**
Constrain the menu to be aligned only at the top or at the 
bottom of its parent. Not left or right aligment is allowed.
@param Value	The menu alignment.
*/
//-------------------------------------------------------------------
void TMainMenu::SetAlign(TAlign Value)
{
	// Constrain the menu alignment only to top and bottom
	if(Value != alTop || Value != alBottom)
		Value = alTop;

	TMenu::SetAlign(Value);
}

//-------------------------------------------------------------------
//  InsertingItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenu::InsertingItem(int Index)
{
	TMenu::InsertingItem(Index);

	TMenuItem* Item = (TMenuItem*)Items->GetItem(Index);
	if(Item != NULL)
	{
		int Offset = 0;

		for(int i=0; i<Items->Count(); i++) 
		{
			TMenuItem* MenuItem = (TMenuItem*)Items->GetItem(i);
			MenuItem->SetLeft(Offset);
			Offset += MenuItem->GetWidth();

			if(MenuItem->GetHeight() > GetHeight())
				SetHeight(MenuItem->GetHeight());
		}
	}
}

//-------------------------------------------------------------------
//  RemovingItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenu::RemovingItem(int Index)
{
}

//-------------------------------------------------------------------
//  ClearingItems()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenu::ClearingItems(void)
{
}

//-------------------------------------------------------------------
//  OnPaint()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenu::OnPaint(void) 
{	
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);

	TMenu::OnPaint();
}

//-------------------------------------------------------------------
//  ParseSkin()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenu::ParseSkin(TiXmlElement* XmlElement)
{
	TMenu::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  TMainMenuItem
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//  TMainMenuItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMainMenuItem::TMainMenuItem()
{
}

//-------------------------------------------------------------------
//  ~TMainMenuItem()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
TMainMenuItem::~TMainMenuItem()
{
}

//-------------------------------------------------------------------
//  Create()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::Create(TComponent* AOwner)
{
	TMenuItem::Create(AOwner);

	ApplySkin(Skin->MainMenuItem);

	SetMenuAlignment(maBottom);
	SetCurrentGrid(GetGrid("Unselected"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::Assign(TObject* Object)
{
	TMenuItem::Assign(Object);

	TMainMenuItem* AControl = (TMainMenuItem*)Object;
	if(AControl != NULL)
	{
		SetExtraWidth(AControl->GetExtraWidth());
		SetExtraHeight(AControl->GetExtraHeight());
	}
}

//-------------------------------------------------------------------
void TMainMenuItem::ApplySkin(TObject* Object)
{
	TMenuItem::ApplySkin(Object);

	TMainMenuItem* AControl = (TMainMenuItem*)Object;
	if(AControl != NULL)
	{
		SetExtraWidth(AControl->GetExtraWidth());
		SetExtraHeight(AControl->GetExtraHeight());
	}
}

//-------------------------------------------------------------------
//  OnPaint()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::OnPaint(void)
{	    
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	CaptionX = (GetWidth() - CaptionWidth)/2;
	CaptionY = (GetHeight() - CaptionHeight)/2;

	// Paint caption
	Canvas->Pen->SetColor(GetCaptionColor());
	Canvas->Text(CaptionX, CaptionY, GetCaption());	
	
	TMenuItem::OnPaint();	
}

//-------------------------------------------------------------------
/**
*/
void TMainMenuItem::OnClick(void)
{		
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TMenuItem::OnMouseDown(Button, Shift, X, Y);

	TMainMenu* ParentMenu = (TMainMenu*)GetParent();
	TMenu* VisibleMenu = ParentMenu->GetVisibleMenu();
	if(VisibleMenu != NULL)
		VisibleMenu->Hide();

	if(Menu != NULL)
	{
		Menu->Show();
		ParentMenu->SetVisibleMenu(Menu);
	}
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TMenuItem::OnMouseUp(Button, Shift, X, Y);

	if(!GetCaptured())
	{
		SetCapture();	
		if(GetGrid("MouseOver") != NULL)
			SetCurrentGrid(GetGrid("MouseOver"));
	}
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::OnMouseMove(const TShiftState& Shift, int X, int Y)
{    
	TMenuItem::OnMouseMove(Shift, X, Y);
	   
	if(!GetCaptured())
	{
		SetCapture();	
		if(GetGrid("MouseOver") != NULL)
			SetCurrentGrid(GetGrid("MouseOver"));
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
//  OnKeyDown()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::OnKeyDown(unsigned short &Key, const TShiftState& Shift)
{
	// Not implemented, yet.
	if(Key == T_KEY_LEFT)
	{
		t_printf("Left arrow\n");
	}
	else if(Key == T_KEY_RIGHT)
	{
		t_printf("Right arrow\n");
	}
	
	TMenuItem::OnKeyDown(Key, Shift);
}

//-------------------------------------------------------------------
/**
*/
void TMainMenuItem::OnCaptureChanged(void)
{
	TMenuItem::OnCaptureChanged();	

	if(GetGrid("Unselected") != NULL)
		SetCurrentGrid(GetGrid("Unselected"));
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::OnTextChanged(void)
{
	TMenuItem::OnTextChanged();
	
	// Adjust the width and height
	SetWidth(CaptionWidth + GetExtraWidth());
	SetHeight(CaptionHeight + GetExtraHeight());
}

//-------------------------------------------------------------------
//  ParseSkin()
//  04-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TMainMenuItem::ParseSkin(TiXmlElement* XmlElement)
{
	TMenuItem::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



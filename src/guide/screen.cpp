#define N_IMPLEMENTS TScreen
//-------------------------------------------------------------------
//  screen.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include <stdio.h>

#include "guide/screen.h"
#include "guide/menu.h"
#include "guide/skin.h"
#include "guide/glserver.h"
#include "guide/canvas.h"
#include "guide/texture.h"
#include "guide/debug.h"

// The singleton
TScreen* TScreen::Singleton = NULL;

//-------------------------------------------------------------------
//  TScreen()
//  21-July-2002   rzv   created
//-------------------------------------------------------------------
TScreen::TScreen()
{
	Singleton = this;	
	CapturedControl = NULL;
	ControlUnderCursor = NULL;
	FileServer = NULL;
	GfxServer = NULL;
	FormsList = NULL;
	ModalFormsList = NULL;
	VisibleMenu = NULL;
}

//-------------------------------------------------------------------
//  ~TScreen()
//  21-July-2002   rzv   created
//-------------------------------------------------------------------
TScreen::~TScreen()
{
	if(Skin != NULL)
		delete Skin;

	if(FileServer != NULL)
		delete FileServer;
		
	if(GfxServer != NULL)
		delete GfxServer;

	if(ModalFormsList != NULL)
		delete ModalFormsList;
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
bool TScreen::Create(const TRect& Rect)
{
    // Create the file server
	FileServer = new TFileServer;

	// Create graphic server
	GfxServer = new TGlServer;
	GfxServer->Width = Rect.right - Rect.left;
	GfxServer->Height = Rect.bottom - Rect.top;
	
    // Create the canvas. Need a canvas for the screen. For example,
	// the screen render the mouse cursor. Because it render something, 
	// we need an already created Canvas. 
	// As you can see, this is a hack, because, normally, every
	// control create it's own canvas in TControl::Create(). But
	// we skip the base class initialization, so need to create the
	// canvas by hand.
	Canvas = new TCanvas(this);
	
	SetBounds(Rect.left, Rect.top, Rect.right, Rect.bottom);

	return true;
}

//-------------------------------------------------------------------
/**
	Load the skin and initialize default font and mouse cursor.
*/
//-------------------------------------------------------------------
bool TScreen::LoadSkin(const char* Filename)
{
	// Create and load the skin
	Skin = new TSkin;
	if(!Skin->Load(Filename))
	{
		t_printf("TScreen: Skin could not be loaded or it is invalid.\n");
		return false;
	}

	// Set the default font
	SetFont(Skin->GetDefaultFont());
	// Set the default mouse cursor
	SetMouseCursor(Skin->GetDefaultMouseCursor());

	return true;
}

//-------------------------------------------------------------------
//  Close()
//  20-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::Close(void)
{
	t_error("Pure virtual function called.");
}

//-------------------------------------------------------------------
//  Run()
//  24-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::Run(void)
{	
	t_error("Pure virtual function called.");
}

//-------------------------------------------------------------------
//  Idle()
//  07-Jan-2004   rzv   created
//-------------------------------------------------------------------
void TScreen::Idle(void)
{
	t_error("Pure virtual function called.");
}

//-------------------------------------------------------------------
//  GetMainForm()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
TForm* TScreen::GetMainForm(void)
{
	if(FormsList != NULL)
	{
		TFormsList::iterator iter;
		for(iter = FormsList->begin(); 
			iter != FormsList->end(); 
			iter++)
		{
			TForm* Form = (TForm*)(*iter);	
			if(Form->GetMain() == true)
				return Form;
		}
	}

	return NULL;
}

//-------------------------------------------------------------------
//  SetClearColor()
//  19-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::SetClearColor(float R, float G, float B, float A)
{
	GfxServer->ClearColor[0] = R;
	GfxServer->ClearColor[1] = G;
	GfxServer->ClearColor[2] = B;
	GfxServer->ClearColor[3] = A;
}

//-------------------------------------------------------------------
//  GetClearColor()
//  19-Aug-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::GetClearColor(float& R, float& G, float& B, float& A)
{
	R = GfxServer->ClearColor[0];
	G = GfxServer->ClearColor[1];
	B = GfxServer->ClearColor[2];
	A = GfxServer->ClearColor[3];
}

//-------------------------------------------------------------------
//  SetMousePosition()
//  23-March-2004   rzv   created
//-------------------------------------------------------------------
void TScreen::SetMousePosition(int X, int Y)
{
	t_error("Pure virtual function called.");
}

//-------------------------------------------------------------------
//  InsertModalForm()
//  20-Jan-2004   rzv   created
//-------------------------------------------------------------------
void TScreen::InsertModalForm(TForm* AModalForm)
{
	if(AModalForm != NULL) 
	{
		if(ModalFormsList == NULL)							
			ModalFormsList = new TModalFormsList;  
		
		ModalFormsList->push_back(AModalForm);
	}
}

//-------------------------------------------------------------------
//  RemoveModalForm()
//  20-Jan-2004   rzv   created
//-------------------------------------------------------------------
void TScreen::RemoveModalForm(TForm* AModalForm)
{
	if(ModalFormsList != NULL)
	{
		if(AModalForm != NULL) 
			ModalFormsList->remove(AModalForm);

		if(ModalFormsList->empty()) 
		{                          
			delete ModalFormsList;             
			ModalFormsList = NULL;
		}
	}
}

//-------------------------------------------------------------------
//  InsertForm()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScreen::InsertForm(TForm* AForm)
{
	if(AForm != NULL) 
	{
		if(FormsList == NULL)							
			FormsList = new TFormsList;  
		
		FormsList->push_back(AForm);
	}
}

//-------------------------------------------------------------------
//  RemoveForm()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScreen::RemoveForm(TForm* AForm)
{
	if(FormsList != NULL)
	{
		if(AForm != NULL) 
			FormsList->remove(AForm);

		if(FormsList->empty()) 
		{                          
			delete FormsList;             
			FormsList = NULL;
		}
	}
}

//-------------------------------------------------------------------
//  SetVisibleMenu()
//  08-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::SetVisibleMenu(TMenu* AVisibleMenu) 
{ 
    VisibleMenu = AVisibleMenu; 	
}

//-------------------------------------------------------------------
//  GetVisibleMenu()
//  08-Dec-2003   rzv   created
//-------------------------------------------------------------------
TMenu* TScreen::GetVisibleMenu(void) const 
{ 
    return VisibleMenu; 
}

//-------------------------------------------------------------------
//  OnPaint()
//  05-March-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::OnPaint(void) 
{	
	TControl::OnPaint();	
	
	// Paint forms
	if(FormsList != NULL)
	{
		TFormsList::iterator iter;
		for(iter = FormsList->begin(); 
			iter != FormsList->end(); 
			iter++)
		{
			PushClipRect();

			TForm* Form = (TForm*)(*iter);
			if(Form->GetVisible())
				Form->CMPaint();

			PopClipRect();
		}
	}
		
	// Find a mouse cursor to paint
	TMouseCursor* Cursor = NULL;
	if(ControlUnderCursor != NULL)
		Cursor = ControlUnderCursor->GetMouseCursor();
		
	// If the current control don't have a mouse cursor assigned, get one from the screen
	if(Cursor == NULL)
		Cursor = GetMouseCursor();
	
	// Paint mouse cursor
	if(Cursor != NULL)
	{
		TPoint Hotspot = Cursor->GetHotspot();
		Canvas->Brush->SetColor(0xEEFFFFFF);
		Canvas->Brush->SetTexture(Cursor->GetTexture());
		Canvas->FillRect(MousePosition.x - Hotspot.x, MousePosition.y - Hotspot.y, 
			Cursor->GetWidth(), Cursor->GetHeight());
	}
}

//-------------------------------------------------------------------
//  HandleInputMessage()
//  04-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::HandleInputMessage(TMessage* Message)
{
	//-------------------------------------------------------------------
	// Note: 
	// Windows tell us what mouse button is pressed
	// (within WM_LBUTTONDOWN, WM_RBUTTONDOWN or WM_MBUTTONDOWN messages),
	// but don't tell what mouse button is release when WM_LBUTTONUP,
	// WM_RBUTTONUP, WM_MBUTTONUP messages are posted!
	//
	// WM_LBUTTONDOWN msg=513; wParam=1; lParam=...;
	// WM_RBUTTONDOWN msg=513; wParam=2; lParam=...;
	// WM_LBUTTONUP msg=514; wParam=0; !? lParam=...; 
	// WM_RBUTTONUP msg=514; wParam=0; !? lParam=...; 
	//
	// So, hack the wParam for mouse up windows events.
	//-------------------------------------------------------------------
	
	#ifdef __WIN32__
	static int WParam = 0;
	#endif

	switch(Message->Msg)
	{
		case CM_MOUSEDOWN:
		{
			#ifdef __WIN32__
			WParam = Message->WParam;
			#endif
		}
		case CM_MOUSEUP:
		{
			#ifdef __WIN32__
			Message->WParam = WParam;
			#endif
		}
		case CM_MOUSEMOVE:
			HandleMouseMessage((TWMMouse*)Message);
			break;
		case CM_CHAR:
		case CM_KEYDOWN:
		case CM_KEYUP:
			HandleKeyboardMessage((TWMKey*)Message);
			break;
	}
}

//-------------------------------------------------------------------
//  HandleMouseMessage()
//  04-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::HandleMouseMessage(TWMMouse* Message)
{
	MousePosition = TPoint(Message->XPos, Message->YPos);

	TControl* Control = NULL;

	// If we have a captured control, give to it all the messages.
	if(CapturedControl != NULL)
	{		
		ControlUnderCursor = CapturedControl;
		Control = ControlUnderCursor;	
	}
	else
	{
		// If we have a modal form, give to it all the messages.
		if(ModalFormsList != NULL && !ModalFormsList->empty())
		{
			Control = ModalFormsList->back();
		}
		else
		{	
			// Find a child control.
			ControlUnderCursor = ControlFromPoint(MousePosition);
			if(ControlUnderCursor != NULL && 
			   ControlUnderCursor->GetEnabled())
			{
				Control = ControlUnderCursor;
			}
			else
			{
				// If no control was found, send all the messages to 
				// the parent screen.
				Control = this; 
			}
		}
	}

	if(Control == this)
		return;
		
	// Now we have a valid control. Send the messages to it.
	switch(Message->Msg)
	{
		case CM_MOUSEDOWN:			
			Control->CMMouseDown(TMouseButton(Message->Keys), Message->XPos, Message->YPos); 
			break;
		case CM_MOUSEUP:
			Control->CMMouseUp(TMouseButton(Message->Keys), Message->XPos, Message->YPos); 
			break;
		case CM_MOUSEMOVE:
			Control->CMMouseMove(Message->XPos, Message->YPos); 
			break;
	}
}

//-------------------------------------------------------------------
//  HandleKeyboardMessage()
//  04-Jan-2003   rzv   created
//-------------------------------------------------------------------
void TScreen::HandleKeyboardMessage(TWMKey* Message)
{
	if(Message->Msg == CM_KEYDOWN)
	{
		switch(Message->KeyData)
		{
			case T_KEY_SHIFT:
				ShiftState.insert(ssShift);
				break;
			case T_KEY_PRIOR:
				ShiftState.insert(ssAlt);
				break;
			case T_KEY_CONTROL:
				ShiftState.insert(ssCtrl);
				break;
		}

		CMKeyDown((unsigned short&)Message->KeyData, ShiftState);

	}
	else if(Message->Msg == CM_KEYUP)
	{
		switch(Message->KeyData)
		{
			case T_KEY_SHIFT:
				ShiftState.erase(ssShift);
				break;
			case T_KEY_PRIOR:
				ShiftState.erase(ssAlt);
				break;
			case T_KEY_CONTROL:
				ShiftState.erase(ssCtrl);
				break;
		}

		CMKeyUp((unsigned short&)Message->KeyData, ShiftState);
	}
	else if(Message->Msg == CM_CHAR)
	{
		if(ShiftState.count(ssShift))
		{
			//Message->CharCode -= 32;
		}

		CMKeyPress((char&)(Message->CharCode));
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

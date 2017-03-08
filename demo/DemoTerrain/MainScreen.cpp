//-------------------------------------------------------------------
//  TMainScreen.cpp
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "MainForm.h"
#include "MainScreen.h"
#include "Proto.h"

//-------------------------------------------------------------------
//  TMainScreen()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
TMainScreen::TMainScreen()
{	
	Proto = NULL;
}

//-------------------------------------------------------------------
//  ~TMainScreen()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
TMainScreen::~TMainScreen()
{
	if(Proto != NULL)
		delete Proto;
}

//-------------------------------------------------------------------
//  Create()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
void TMainScreen::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);

	SetCaption("Terrain");
	SetColor(0x40FFFFFF);
	SetCastShadows(false);

	// Our main form is in fact our owner form
	MainForm = (TMainForm*)AOwner;

	int YOffset = 90;
	
	ButtonNew = new TButton;
	ButtonNew->Create(this, TRect(GetWidth()/2 - 128, YOffset, 256, 32));
	ButtonNew->SetCaption("New terrain");
	ButtonNew->FOnClick = makeFunctor((TNotifyEvent*)0, *this, &TMainScreen::OnButtonNew);
	YOffset += 60;

	ButtonLoad = new TButton;
	ButtonLoad->Create(this, TRect(GetWidth()/2 - 128, YOffset, 256, 32));
	ButtonLoad->SetCaption("Load terrain");	
	ButtonLoad->SetEnabled(false);	
	YOffset += 60;

	ButtonReturn = new TButton;
	ButtonReturn->Create(this, TRect(GetWidth()/2 - 128, YOffset, 256, 32));
	ButtonReturn->SetCaption("Return");	
	ButtonReturn->FOnClick = makeFunctor((TNotifyEvent*)0, *this, &TMainScreen::OnButtonReturn);
	YOffset += 60;

	ButtonOptions = new TButton;
	ButtonOptions->Create(this, TRect(GetWidth()/2 - 128, YOffset, 256, 32));
	ButtonOptions->SetCaption("Options");
	ButtonOptions->SetEnabled(false);	
	YOffset += 60;

	ButtonCredits = new TButton;
	ButtonCredits->Create(this, TRect(GetWidth()/2 - 128, YOffset, 256, 32));
	ButtonCredits->SetCaption("Credits");	
	ButtonCredits->SetEnabled(false);	
	YOffset += 60;

	ButtonQuit = new TButton;
	ButtonQuit->Create(this, TRect(GetWidth()/2 - 128, YOffset, 256, 32));
	ButtonQuit->SetCaption("Quit");		
	ButtonQuit->FOnClick = makeFunctor((TNotifyEvent*)0, *this, &TMainScreen::OnButtonQuit);
	YOffset += 120;
}

//-------------------------------------------------------------------
//  OnPaint()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
void TMainScreen::OnPaint(void) 
{
	// Fill body
	//Canvas->Brush->SetColor(GetColor());
	//Canvas->FillRect(TRect(0, 0, GetWidth(), GetHeight()));
	        
	TForm::OnPaint();
}

//-------------------------------------------------------------------
//  OnButtonNew()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
void TMainScreen::OnButtonNew(void)
{
	// Destroy the old proto (if any)
	if(Proto != NULL)
	{
		delete Proto;
		Proto = NULL;
	}

	// Create a new proto.
	Proto = new CProto;
	Proto->Init();

	MainForm->SetProto(Proto);
	MainForm->SetGameStarted(true);
	MainForm->SetActiveControl(NULL);

	// Hide this form
	SetVisible(false);
}

//-------------------------------------------------------------------
//  OnButtonReturn()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
void TMainScreen::OnButtonReturn(void)
{
	// If we have a proto, return to it
	if(Proto != NULL)
	{
		MainForm->SetGameStarted(true);
		MainForm->SetActiveControl(NULL);

		// Hide this form
		SetVisible(false);
	}
}

//-------------------------------------------------------------------
//  OnButtonQuit()
//  09-Feb-2004   rzv    created
//-------------------------------------------------------------------
void TMainScreen::OnButtonQuit(void)
{
	// Close application
	Screen->Close();
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


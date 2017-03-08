//-------------------------------------------------------------------
//  TMainForm.cpp
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "MainForm.h"
#include "Proto.h"

//-------------------------------------------------------------------
//  TMainForm()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
TMainForm::TMainForm()
{
	Proto = NULL;
	GameStarted = false;
}

//-------------------------------------------------------------------
//  ~TMainForm()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
TMainForm::~TMainForm()
{
}

//-------------------------------------------------------------------
//  Create()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
void TMainForm::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);

	MainScreen = new TMainScreen;
	MainScreen->Create(this, TRect(100, 50, 600, GetHeight() - 100), true);
}

//-------------------------------------------------------------------
//  OnPaint()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
void TMainForm::OnPaint(void)
{
	// If the proto is valid and the game is started
	if(GameStarted == true && Proto != NULL)
	{
		// Begin the user scene. This is gui specific and should be
		// called before any user scene. This is a must!
		Canvas->BeginUserScene();

		// Render the proto
		Proto->Render(GetWidth(), GetHeight());
	
		// End the user scene
		Canvas->EndUserScene();	
	}
	
	TWinControl::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
void TMainForm::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	// Capture the mouse movement even if outside of control
	if(!GetCaptured())
		SetCapture();

	// Store the mouse positions
	MouseX = X;
	MouseY = Y;

	TForm::OnMouseDown(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
void TMainForm::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	// Release the mouse capture
	if(GetCaptured())
		ReleaseCapture();

	// Store the mouse positions
	MouseX = X;
	MouseY = Y;

	TForm::OnMouseUp(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseMove()	
// Anybody could use the OnMouseMove for his own interests.
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
void TMainForm::OnMouseMove(const TShiftState& Shift, int X, int Y)
{
	// If the mouse is captured and we're moving it...
	if(GetCaptured())
	{
		// Mouse movement
		int DX = MouseX - X;
		int DY = MouseY - Y;

		if(Proto != NULL)
		{
			// Use specific implementation of the proto
			Proto->GetCamera()->UpdateDirection((float)DX/100.0f, (float)DY/100.0f);
		}

		// The new mouse positions
		MouseX = X;
		MouseY = Y;
	}

	TForm::OnMouseMove(Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnKeyDown()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
void TMainForm::OnKeyDown(unsigned short &Key, const TShiftState& Shift)
{
	if(Proto != NULL)
	{		
		if(Key == T_KEY_UP)
			Proto->GetCamera()->SetSpeed(Proto->GetCamera()->GetSpeed() + 1);
		else if(Key == T_KEY_DOWN)
			Proto->GetCamera()->SetSpeed(Proto->GetCamera()->GetSpeed()/2);	
	}
	
	if(Key == T_KEY_ESCAPE)
	{
		// Bring the main menu on the screen
		MainScreen->SetVisible(true);
		// Pause the game
		//SetGameStarted(false);
	}

	TForm::OnKeyDown(Key, Shift);
}

//-------------------------------------------------------------------
//  OnKeyUp()
//  09-Feb-2004   E    created
//-------------------------------------------------------------------
void TMainForm::OnKeyUp(unsigned short &Key, const TShiftState& Shift)
{
	// This does nothing, but is here for you to see it exists.
	TForm::OnKeyUp(Key, Shift);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


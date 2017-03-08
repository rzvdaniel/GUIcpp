//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2004 Ricas -- R.Predescu
//
//  Description:
//
//  This tutorial presents you the modality you can create
//  standard buttons, placed on a form. Also you can see how
//  you can attach an OnClick() event to a standard control
//  (in this case, a simple button).
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Form1.h"

//-------------------------------------------------------------------
//  TForm1()
//  07-June-2004   rzv    created
//-------------------------------------------------------------------
TForm1::TForm1()
{
}

//-------------------------------------------------------------------
//  ~TForm1()
//  07-June-2004   rzv    created
//-------------------------------------------------------------------
TForm1::~TForm1()
{
}

//-------------------------------------------------------------------
//  Create()
//  22-Dec-2003   rzv    created
//-------------------------------------------------------------------
void TForm1::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{
	// First, call the base class Create() function
	TForm::Create(AOwner, Rect, HasCaption);
	
	// Set the form's caption
	SetCaption("Tutorial1");
	
	// Creates the button and place it at the bottom of our form
	Button1 = new TButton;
	Button1->Create(this, TRect(GetWidth()/2 - 30, GetHeight() - 50, 60, 32));
	Button1->SetCaption("Close");
	
	// This will set the OnClick() event for the button to OnButton1Click() function.
	Button1->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnButton1Click);
}

//-------------------------------------------------------------------
//  OnButton1Click()
//  07-June-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnButton1Click(void)
{
	// Close application
	Screen->Close();
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


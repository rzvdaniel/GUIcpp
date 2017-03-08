//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2004 Ricas -- R.Predescu
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
	SetCaption("Modal");
	
	// Create the Ok button
	Close = new TButton;
	Close->Create(this, TRect(GetWidth()/2 - 70, GetHeight() - 50, 60, 32));
	Close->SetCaption("Close");
	Close->SetModalResult(mrOk);
	
	Button1 = new TButton;
	Button1->Create(this, TRect(GetWidth()/2 + 30, GetHeight() - 50, 60, 32));
	Button1->SetCaption("Form2");
	// This will set the OnClick() event for the button to OnButton1Click() function.
	Button1->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnButton1Click);

	// Create the second form
	Form2 = new TForm2;
	Form2->Create(this, TRect(200, 100, 200, 200), true);
	Form2->ShowModal();
}

//-------------------------------------------------------------------
//  OnButton1Click()
//  07-June-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnButton1Click(void)
{
	// Show the second form
	if(Form2->ShowModal() == mrOk)
	{
	    // Do something if the user pressed the Form2's Ok button
    }
}

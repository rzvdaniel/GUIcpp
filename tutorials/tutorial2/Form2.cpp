//-------------------------------------------------------------------
//  Form2.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Form2.h"

//-------------------------------------------------------------------
//  TForm2()
//  07-June-2004   rzv    created
//-------------------------------------------------------------------
TForm2::TForm2()
{
}

//-------------------------------------------------------------------
//  ~TForm2()
//  07-June-2004   rzv    created
//-------------------------------------------------------------------
TForm2::~TForm2()
{
}

//-------------------------------------------------------------------
//  Create()
//  22-Dec-2003   rzv    created
//-------------------------------------------------------------------
void TForm2::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{
	// First, call the base class Create() function
	TForm::Create(AOwner, Rect, HasCaption);
	
	// Set the form's caption
	SetCaption("Form2 -- Modal");
	
	// Create the Ok button
	Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 50, GetHeight() - 50, 50, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);

	// Create the Cancel button
	Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 10, GetHeight() - 50, 60, 32));
	Cancel->SetCaption("Cancel");
	Cancel->SetModalResult(mrCancel);
}

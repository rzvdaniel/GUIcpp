//-------------------------------------------------------------------
//  Form2.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Form2.h"

//-------------------------------------------------------------------
//  TForm2()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
TForm2::TForm2()
{
}

//-------------------------------------------------------------------
//  ~TForm2()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
TForm2::~TForm2()
{
}

//-------------------------------------------------------------------
//  Create()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TForm2::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{
	// First, call the base class Create() function
	TForm::Create(AOwner, Rect, HasCaption);
	
	// Set the form's caption
	SetCaption("Form2");

	// Transparent yellow
	SetColor(0x80AAFFFF); 

	TLabel* Label1 = new TLabel;
	Label1->Create(this, TRect(10, GetHeight()/2, GetWidth() - 20, 18));
	Label1->SetColor(0x40EEEEEE);
	Label1->SetTextAlignment(taCenter);
	Label1->SetCaption("Press ESC to exit!");

	// Create the Ok button
	Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 50, GetHeight() - 50, 50, 32));
	Ok->SetCaption("Ok");
	Ok->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm2::OnOkClick);
	
	// Create the Cancel button
	Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 10, GetHeight() - 50, 60, 32));
	Cancel->SetCaption("Cancel");
	Cancel->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm2::OnCancelClick);

}

//-------------------------------------------------------------------
//  OnOkClick()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TForm2::OnOkClick(void)
{
	Hide();
}

//-------------------------------------------------------------------
//  OnCancelClick()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TForm2::OnCancelClick(void)
{
	Hide();
}

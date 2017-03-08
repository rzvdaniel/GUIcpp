//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2007 Razvan Predescu
//	rzvdaniel@yahoo.com
//
//  Description:
//
//  This tutorial is intented to show you how to use a hand made skin
//  for GUIde.
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Form1.h"

TForm1::TForm1()
{
}

TForm1::~TForm1()
{
}

void TForm1::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{
	// First, call the base class Create() function
	TForm::Create(AOwner, Rect, HasCaption);
	
	// Set the form's caption
	SetCaption("Tutorial A");
	
	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 70, GetHeight() - 50, 50, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);

	TButton* Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 10, GetHeight() - 50, 70, 32));
	Cancel->SetCaption("Cancel");
	Cancel->SetModalResult(mrCancel);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


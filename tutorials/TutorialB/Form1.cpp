//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2007 Razvan Predescu
//	rzvdaniel@yahoo.com
//
//  Description:
//
//  This tutorial is intented to show you how to use an edit box.
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
	TForm::Create(AOwner, Rect, HasCaption);
	
	// Set the form's caption
	SetCaption("Tutorial B");
	
	int YOffset = 50;

	TEdit* Edit1 = new TEdit;
	Edit1->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 32));
	Edit1->SetText("0123456789");
	Edit1->SetAutoSelect(true);
	YOffset += 40;

	TEdit* Edit2 = new TEdit;
	Edit2->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 32));
	Edit2->SetText("Auto size");
	YOffset += 45;

	TEdit* Edit3 = new TEdit;
	Edit3->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 32));
	Edit3->SetText("Upper case");
	Edit3->SetCharCase(ecUpperCase);
	YOffset += 40;

	TEdit* Edit4 = new TEdit;
	Edit4->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 32));
	Edit4->SetText("Max length = 18");
	Edit4->SetMaxLength(15);
	YOffset += 40;

	TEdit* Edit5 = new TEdit;
	Edit5->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 32));
	Edit5->SetText("Read only");
	Edit5->SetReadOnly(true);
	YOffset += 40;

	TEdit* Edit6 = new TEdit;
	Edit6->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 32));
	Edit6->SetText("Hide selection");
	Edit6->SetHideSelection(false);
	YOffset += 40;

	TEdit* Edit7 = new TEdit;
	Edit7->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 32));
	Edit7->SetText("Coming soon: Password");
	Edit7->SetPasswordChar('*');
	YOffset += 40;

	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 25, GetHeight() - 50, 50, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


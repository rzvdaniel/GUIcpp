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
	SetCaption("Tutorial C");
	
	int XOffset = GetWidth()/2;
	int YOffset = 100;

	// Group box for the radio buttons
	TGroupBox* GroupBox1 = new TGroupBox;
	GroupBox1->Create(this, TRect(60, 60, GetWidth() - 120, GetHeight() - 140));
	GroupBox1->SetColor(clGray);
	GroupBox1->SetCaption("Bitmap Buttons");

	TBitBtn* BitBtn1 = new TBitBtn;
	BitBtn1->Create(this, TRect(XOffset - 60, YOffset, 120, 32));
	BitBtn1->SetCaption("Disabled");
	BitBtn1->LoadPicture("../res/tutorials/flexSportFootball.tga", 1);
	BitBtn1->SetEnabled(false);
	YOffset += 50;

	TBitBtn* BitBtn2 = new TBitBtn;
	BitBtn2->Create(this, TRect(XOffset - 60, YOffset, 120, 32));
	BitBtn2->SetCaption("Ignore");
	BitBtn2->LoadPicture("../res/tutorials/flexSportBasketball.tga", 1);
	YOffset += 50;

	TBitBtn* BitBtn3 = new TBitBtn;
	BitBtn3->Create(this, TRect(XOffset - 60, YOffset, 120, 32));
	BitBtn3->SetCaption("Cancel");
	BitBtn3->LoadPicture("../res/tutorials/flexSportSoccer.tga", 1);
	BitBtn3->SetLayout(blGlyphRight);
	YOffset += 50;

	/*
	TBitBtn* BitBtn4 = new TBitBtn;
	BitBtn4->Create(this, TRect(XOffset - 40, YOffset, 80, 32));
	BitBtn4->SetCaption("No");
	BitBtn4->LoadPicture("../res/tutorials/flexSportRaquet.tga", 1);
	BitBtn4->SetLayout(blGlyphTop);
	YOffset += 50;

	TBitBtn* BitBtn5 = new TBitBtn;
	BitBtn5->Create(this, TRect(XOffset - 50, YOffset, 100, 32));
	BitBtn5->SetCaption("Retry");
	BitBtn5->LoadPicture("../res/tutorials/flexSportGolf.tga", 1);
	BitBtn5->SetLayout(blGlyphBottom);
	YOffset += 50;
	*/

	TBitBtn* BitBtn6 = new TBitBtn;
	BitBtn6->Create(this, TRect(XOffset - 60, YOffset, 120, 32));
	BitBtn6->SetCaption("Text only");

	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 90, GetHeight() - 50, 70, 32));
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


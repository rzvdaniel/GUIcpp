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
	SetCaption("BitBtn");
	
	int XOffset = GetWidth()/2;
	int YOffset = 70;
	
	TBitBtn* BitBtn1 = new TBitBtn;
	BitBtn1->Create(this, TRect(XOffset - 40, YOffset, 80, 36));
	BitBtn1->SetCaption("Ok");
	BitBtn1->LoadPicture("../res/tutorials/bkYes.tga", 1);
	BitBtn1->SetColor(0x80FFBBBB);
	BitBtn1->SetEnabled(false);
	YOffset += 50;
	
	TBitBtn* BitBtn2 = new TBitBtn;
	BitBtn2->Create(this, TRect(XOffset - 60, YOffset, 120, 36));
	BitBtn2->SetCaption("Ignore");
	BitBtn2->LoadPicture("../res/tutorials/bkIgnore.tga", 1);
	BitBtn2->SetColor(0x80BBBBBB);
	YOffset += 50;
	
	TBitBtn* BitBtn3 = new TBitBtn;
	BitBtn3->Create(this, TRect(XOffset - 60, YOffset, 120, 36));
	BitBtn3->SetCaption("Cancel");
	BitBtn3->LoadPicture("../res/tutorials/bkCancel.tga", 1);
	BitBtn3->SetColor(0x80BBBBFF);
	BitBtn3->SetLayout(blGlyphRight);
	YOffset += 50;
	
	TBitBtn* BitBtn4 = new TBitBtn;
	BitBtn4->Create(this, TRect(XOffset - 40, YOffset, 80, 70));
	BitBtn4->SetCaption("No");
	BitBtn4->LoadPicture("../res/tutorials/bkNo.tga", 1);
	BitBtn4->SetColor(0x80FFFFFF);
	BitBtn4->SetLayout(blGlyphTop);
	YOffset += 84;
	
	TBitBtn* BitBtn5 = new TBitBtn;
	BitBtn5->Create(this, TRect(XOffset - 50, YOffset, 100, 60));
	BitBtn5->SetCaption("Retry");
	BitBtn5->LoadPicture("../res/tutorials/bkRetry.tga", 1);
	BitBtn5->SetColor(0x80BBFFBB);
	BitBtn5->SetLayout(blGlyphBottom);
	YOffset += 74;
	
	TBitBtn* BitBtn6 = new TBitBtn;
	BitBtn6->Create(this, TRect(XOffset - 60, YOffset, 120, 34));
	BitBtn6->SetCaption("Text only");
	
	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 40, GetHeight() - 50, 80, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

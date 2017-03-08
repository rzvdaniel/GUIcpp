//-------------------------------------------------------------------
//  Test3.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "tests/Test3.h"

//-------------------------------------------------------------------
//  TTest3()
//  18-Aug-2004   rzv    created
//-------------------------------------------------------------------
TTest3::TTest3()
{
}

//-------------------------------------------------------------------
//  ~TTest3()
//  18-Aug-2004   rzv    created
//-------------------------------------------------------------------
TTest3::~TTest3()
{
}

//-------------------------------------------------------------------
//  Create()
//  18-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TTest3::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);
	
	SetCaption("Test3");
		
	int XOffset = GetWidth()/2;
	int YOffset = 120;

	// Group box for the radio buttons
	TGroupBox* GroupBox1 = new TGroupBox;
	GroupBox1->Create(this, TRect(60, 60, GetWidth() - 120, GetHeight() - 150));
	GroupBox1->SetColor(clGray);
	GroupBox1->SetCaption("Bitmap Buttons");
	
	TBitBtn* BitBtn1 = new TBitBtn;
	BitBtn1->Create(this, TRect(XOffset - 140, YOffset, 120, 0));
	BitBtn1->SetCaption("Disabled");
	BitBtn1->LoadPicture("../res/tutorials/flexSportFootball.tga", 1);
	BitBtn1->SetEnabled(false);
	YOffset += 50;
	
	TBitBtn* BitBtn2 = new TBitBtn;
	BitBtn2->Create(this, TRect(XOffset - 140, YOffset, 120, 0));
	BitBtn2->SetCaption("Ignore");
	BitBtn2->LoadPicture("../res/tutorials/flexSportBasketball.tga", 1);
	YOffset += 50;
	
	TBitBtn* BitBtn3 = new TBitBtn;
	BitBtn3->Create(this, TRect(XOffset - 140, YOffset, 120, 0));
	BitBtn3->SetCaption("Cancel");
	BitBtn3->LoadPicture("../res/tutorials/flexSportSoccer.tga", 1);
	BitBtn3->SetLayout(blGlyphRight);
	YOffset = 120;
	
	TBitBtn* BitBtn4 = new TBitBtn;
	BitBtn4->Create(this, TRect(XOffset + 40, YOffset, 120, 32));
	BitBtn4->SetCaption("No");
	BitBtn4->LoadPicture("../res/tutorials/flexSportRaquet.tga", 1);
	BitBtn4->SetLayout(blGlyphLeft);
	YOffset += 50;
	
	TBitBtn* BitBtn5 = new TBitBtn;
	BitBtn5->Create(this, TRect(XOffset + 40, YOffset, 120, 32));
	BitBtn5->SetCaption("Retry");
	BitBtn5->LoadPicture("../res/tutorials/flexSportGolf.tga", 1);
	BitBtn5->SetLayout(blGlyphRight);
	YOffset += 50;
	
	TBitBtn* BitBtn6 = new TBitBtn;
	BitBtn6->Create(this, TRect(XOffset + 40, YOffset, 120, 0));
	BitBtn6->SetCaption("Text only");
	
	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 90, GetHeight() - 50, 70, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);

	TButton* Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 10, GetHeight() - 50, 70, 0));
	Cancel->SetCaption("Cancel");
	Cancel->SetModalResult(mrCancel);	
}

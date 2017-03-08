//-------------------------------------------------------------------
//  Test1.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/skin.h"
#include "guide/debug.h"
#include "tests/Test1.h"

//-------------------------------------------------------------------
//  TTest1()
//  05-Nov-2003   rzv    created
//-------------------------------------------------------------------
TTest1::TTest1()
{
}

//-------------------------------------------------------------------
//  ~TTest1()
//  05-Nov-2003   rzv    created
//-------------------------------------------------------------------
TTest1::~TTest1()
{
}

//-------------------------------------------------------------------
//  Create()
//  05-Nov-2003   rzv    created
//-------------------------------------------------------------------
void TTest1::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);
	
	SetCaption("Test1");

	// Logo image
	/*
	TImage* Image = new TImage;
	Image->Create(this, TRect(GetWidth()/2 - 107, 200, 213, 100));
	Image->LoadPicture("../res/tutorials/moon2.tga");
	Image->SetColor(0xEEFFFFFF);
    */

	/*
	int YOffset = 50;

	Edit1 = new TEdit;
	Edit1->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 20));
	Edit1->FOnTextChanged = makeFunctor((TNotifyEvent*)0,*this, &TTest1::OnEdit1TextChange);	
	YOffset += 40;

	// First label
	TLabel* Label2 = new TLabel;
	Label2->Create(this, TRect(GetWidth()/2 - 100, YOffset, 70, 18));
	Label2->SetColor(0xFFDDDDDD);
	Label2->SetCaption("Num chars:");

	// First label
	Label1 = new TLabel;
	Label1->SetColor(0xFFDDDDDD);
	Label1->Create(this, TRect(GetWidth()/2 - 20, YOffset, 50, 18));
	*/

	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 70, GetHeight() - 50, 50, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);

	TButton* Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 10, GetHeight() - 50, 70, 0));
	Cancel->SetCaption("Cancel");
	Cancel->SetModalResult(mrCancel);	
}

//-------------------------------------------------------------------
//  OnEdit1TextChange()
//  05-Nov-2003   rzv    created
//-------------------------------------------------------------------
void TTest1::OnEdit1TextChange(void)
{
	//char buf[256];
    //sprintf(buf, "%i", Edit1->GetText().size());

	//Label1->SetCaption(buf);	
}

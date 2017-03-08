//-------------------------------------------------------------------
//  Test8.cpp
//  (C) 2008 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/skin.h"
#include "tests/Test8.h"

//-------------------------------------------------------------------
/**
*/
TTest8::TTest8()
{
}

//-------------------------------------------------------------------
/**
*/
TTest8::~TTest8()
{
}

//-------------------------------------------------------------------
/**
*/
void TTest8::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);
	
	SetCaption("Test8");

	// Logo image
	TImage* Image = new TImage;
	Image->Create(this, TRect(GetWidth()/2 - 107, 200, 16, 16));
	Image->LoadPicture("../res/skins/aqua/icons/folder.tga");
	Image->SetColor(0xEEFFFFFF);

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
/**
*/
void TTest8::OnPaint(void) 
{	
	TForm::OnPaint();

	Canvas->Brush->SetTexture(Skin->GetIcon("folder", iconSmall));
	Canvas->FillRect(100, 100, 16, 16);
	Canvas->Brush->SetTexture(NULL);
}

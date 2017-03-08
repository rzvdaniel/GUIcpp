//-------------------------------------------------------------------
//  Test9.cpp
//  (C) 2008 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/skin.h"
#include "tests/Test9.h"

//-------------------------------------------------------------------
/**
*/
TTest9::TTest9()
{
}

//-------------------------------------------------------------------
/**
*/
TTest9::~TTest9()
{
}

//-------------------------------------------------------------------
/**
*/
void TTest9::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);
	
	SetCaption("Test9");

	// Left
	TPanel* Panel1 = new TPanel;
	Panel1->Create(this, TRect(0,0,40, 100));
	Panel1->SetAlign(alLeft);
	Panel1->SetColor(0x80AAAAFF);

	TPanel* Panel2 = new TPanel;
	Panel2->Create(this, TRect(0,0,60, 100));
	Panel2->SetAlign(alLeft);
	Panel2->SetColor(0x80FFAAAA);
	
	// Top
	TPanel* Panel4 = new TPanel;
	Panel4->Create(this, TRect(0,0,40, 100));
	Panel4->SetAlign(alTop);
	Panel4->SetColor(0x80FFFFAA);
	

	// Right
	TPanel* Panel3 = new TPanel;
	Panel3->Create(this, TRect(0,0,40, 100));
	Panel3->SetAlign(alRight);
	Panel3->SetColor(0x80AAFFAA);

	
	// Bottom
	TPanel* Panel5 = new TPanel;
	Panel5->Create(this, TRect(0,0,40, 100));
	Panel5->SetAlign(alTop);
	Panel5->SetColor(0x80AAFFFF);
	

	Panel2->SetAlign(alRight);

	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 70, GetHeight() - 50, 50, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);

	TButton* Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 10, GetHeight() - 50, 70, 0));
	Cancel->SetCaption("Cancel");
	Cancel->SetModalResult(mrCancel);	
}


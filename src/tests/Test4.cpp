//-------------------------------------------------------------------
//  Test4.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "tests/Test4.h"
//#include <GL/glext.h>

 
//-------------------------------------------------------------------
//  TTest4()
//  30-Aug-2004   rzv    created
//-------------------------------------------------------------------
TTest4::TTest4()
{
}

//-------------------------------------------------------------------
//  ~TTest4()
//  30-Aug-2004   rzv    created
//-------------------------------------------------------------------
TTest4::~TTest4()
{
}

//-------------------------------------------------------------------
//  Create()
//  30-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TTest4::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);

	SetCaption("Edit box");

	int YOffset = 50;
	
	TEdit* Edit1 = new TEdit;
	Edit1->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 24));
	Edit1->SetText("0123456789");
	//Edit1->SetText("0123456789ABCDEFGHIJKLMNOQPRSTUVXYW");
	//Edit1->SetAutoSelect(true);
	YOffset += 40;
	
	TEdit* Edit2 = new TEdit;
	Edit2->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 24));
	Edit2->SetText("Auto size");
	Edit2->SetAutoSize(true);
	Edit2->SetFont(Screen->GetFont("Verdana.ttf", 14));
	Edit2->SetColor(0x80AAAAFF);
	YOffset += 45;
	
	TEdit* Edit3 = new TEdit;
	Edit3->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 24));
	Edit3->SetText("Upper case");
	Edit3->SetCharCase(ecUpperCase);
	Edit3->SetColor(0x80FFAAAA);
	YOffset += 40;

	TEdit* Edit4 = new TEdit;
	Edit4->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 24));
	Edit4->SetText("Max length = 18");
	Edit4->SetMaxLength(15);
	Edit4->SetColor(0x80AAFFAA);
	YOffset += 40;
	
	TEdit* Edit5 = new TEdit;
	Edit5->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 24));
	Edit5->SetText("Read only");
	Edit5->SetReadOnly(true);
	Edit5->SetColor(0x80FFFFAA);
	YOffset += 40;
	
	TEdit* Edit6 = new TEdit;
	Edit6->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 24));
	Edit6->SetText("Hide selection");
	Edit6->SetHideSelection(false);
	Edit6->SetColor(0x80AAFFFF);
	YOffset += 40;
	
	TEdit* Edit7 = new TEdit;
	Edit7->Create(this, TRect(GetWidth()/2 - 100, YOffset, 200, 24));
	Edit7->SetText("Password");
	Edit7->SetPasswordChar('*');
	YOffset += 40;
	
	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 25, GetHeight() - 50, 50, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

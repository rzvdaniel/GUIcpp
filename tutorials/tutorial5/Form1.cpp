//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Form1.h"

//-------------------------------------------------------------------
//  TForm1()
//  05-Nov-2003   rzv    created
//-------------------------------------------------------------------
TForm1::TForm1()
{
}

//-------------------------------------------------------------------
//  ~TForm1()
//  05-Nov-2003   rzv    created
//-------------------------------------------------------------------
TForm1::~TForm1()
{
}

//-------------------------------------------------------------------
//  Create()
//  05-Nov-2003   rzv    created
//-------------------------------------------------------------------
void TForm1::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);
	
	SetCaption("Tutorial5");
	
	// Group box for the radio buttons
	GroupBox1 = new TGroupBox;
	GroupBox1->Create(this, TRect(10, 30, GetWidth() - 20, 120));
	GroupBox1->SetCaption("Group box 1");

	// An offset to help positioning the buttons
	int Offset = 32;

	// Radio buttons
	RadioBtn1 = new TRadioBtn;
	RadioBtn1->Create(this, TRect(16, Offset, 16, 16));
	RadioBtn1->SetCaption("I like it.");
	RadioBtn1->SetCheckState(cbDown);
	RadioBtn1->SetParent(GroupBox1);
	Offset += 24;

	RadioBtn2 = new TRadioBtn;
	RadioBtn2->Create(this, TRect(16, Offset, 16, 16));
	RadioBtn2->SetCaption("I think it could be useful.");
	RadioBtn2->SetParent(GroupBox1);
	Offset += 24;

	RadioBtn3 = new TRadioBtn;
	RadioBtn3->Create(this, TRect(16, Offset, 16, 16));
	RadioBtn3->SetCaption("What the hell is this ?");	
	RadioBtn3->SetParent(GroupBox1);
	
	// We will group all the radio buttons together
	RadioGroup = new TGroup;
	RadioGroup->InsertComponent(RadioBtn1);
	RadioGroup->InsertComponent(RadioBtn2);
	RadioGroup->InsertComponent(RadioBtn3);

	// Disable1 button
	Disable1 = new TButton;
	Disable1->Create(this, TRect(GroupBox1->GetWidth() - 80, GroupBox1->GetHeight()/2 - 16, 64, 32));
	Disable1->SetCaption("Disable");
	Disable1->SetParent(GroupBox1);
	Disable1->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnDisable1Click);
	
	// Group box for the check buttons
	GroupBox2 = new TGroupBox;
	GroupBox2->Create(this, TRect(10, 200, GetWidth() - 20, 120));
	GroupBox2->SetCaption("Group box 2");

	// Reset the offset for a new begining
	Offset = 32;

	// Check buttons
	CheckBtn1 = new TCheckBtn;
	CheckBtn1->Create(this, TRect(16, Offset, 16, 16));
	CheckBtn1->SetCaption("Tell me more.");
	CheckBtn1->SetCheckState(cbDown);
	CheckBtn1->SetParent(GroupBox2);
	Offset += 24;

	CheckBtn2 = new TCheckBtn;
	CheckBtn2->Create(this, TRect(16, Offset, 16, 16));
	CheckBtn2->SetCaption("This looks good.");
	CheckBtn2->SetCheckState(cbDown);
	CheckBtn2->SetParent(GroupBox2);
	Offset += 24;

	CheckBtn3 = new TCheckBtn;
	CheckBtn3->Create(this, TRect(16, Offset, 16, 16));
	CheckBtn3->SetCaption("This is ugly.");
	CheckBtn3->SetParent(GroupBox2);
	
	// Disable2 button
	Disable2 = new TButton;
	Disable2->Create(this, TRect(GroupBox2->GetWidth() - 80, GroupBox2->GetHeight()/2 - 16, 64, 32));
	Disable2->SetCaption("Disable");
	Disable2->SetParent(GroupBox2);
	Disable2->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnDisable2Click);

	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 25, GetHeight() - 50, 50, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

//-------------------------------------------------------------------
//  OnVoteClick()
//  10-Sep-2003   rzv    created
//-------------------------------------------------------------------
void TForm1::OnDisable1Click(void)
{
	RadioBtn1->SetEnabled(!RadioBtn1->GetEnabled());
	RadioBtn2->SetEnabled(!RadioBtn2->GetEnabled());
	RadioBtn3->SetEnabled(!RadioBtn3->GetEnabled());
}

//-------------------------------------------------------------------
//  OnSendClick()
//  10-Sep-2003   rzv    created
//-------------------------------------------------------------------
void TForm1::OnDisable2Click(void)
{
	CheckBtn1->SetEnabled(!CheckBtn1->GetEnabled());
	CheckBtn2->SetEnabled(!CheckBtn2->GetEnabled());
	CheckBtn3->SetEnabled(!CheckBtn3->GetEnabled());
}



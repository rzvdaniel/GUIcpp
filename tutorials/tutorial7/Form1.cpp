//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2004 Ricas -- R.Predescu
//
//  Description:
//  This tutorial shows you how you can embed GUIde into an already 
//  existing Windows - OpenGL application.
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
	SetCaption("Form1");
	// Transparent yellow
	SetColor(0x80AAFFFF); 

	TLabel* Label1 = new TLabel;
	Label1->Create(this, TRect(10, GetHeight()/2, GetWidth() - 20, 18));
	Label1->SetColor(0x40EEEEEE);
	Label1->SetTextAlignment(taCenter);
	Label1->SetCaption("Press ESC to exit!");

	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 40, GetHeight() - 50, 80, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

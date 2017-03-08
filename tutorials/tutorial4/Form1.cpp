//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2004 Ricas -- R.Predescu
//
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Form1.h"

//-------------------------------------------------------------------
//  TTutorial1()
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
	SetCaption("About");

	// Logo image
	Image = new TImage;
	Image->Create(this, TRect(GetWidth()/2 - 64, 100, 213, 100));
	Image->LoadPicture("../res/tutorials/moon.tga");
	Image->SetColor(0xEEFFFFFF);
		
	int YOffset = 260;

	// First label
	Label1 = new TLabel;
	Label1->Create(this, TRect(GetWidth()/2 - 114, YOffset, 228, 18));
	Label1->SetColor(0x80E0C0C0);
	Label1->SetTextAlignment(taCenter);
	Label1->SetCaption("Created by Razvan Predescu");
	
	YOffset += 30;

	// Second label
	Label2 = new TLabel;
	Label2->Create(this, TRect(GetWidth()/2 - 114, YOffset, 228, 18));
	Label2->SetColor(0x80C0C0C0);
	Label2->SetTextAlignment(taCenter);
	Label2->SetCaption("Email: ricas@techemail.com");
	
	YOffset += 30;
	
	// Third label
	Label3 = new TLabel;
	Label3->Create(this, TRect(GetWidth()/2 - 114, YOffset, 228, 18));
	Label3->SetColor(0x80C0C0E0);
	Label3->SetTextAlignment(taCenter);
	Label3->SetCaption("Web: guide.jejik.com");
	
	YOffset += 30;
	
	// Fourth label
	Label4 = new TLabel;
	Label4->Create(this, TRect(GetWidth()/2 - 114, YOffset, 228, 18));
	Label4->SetColor(0x80C0E0C0);
	Label4->SetTextAlignment(taCenter);
	Label4->SetCaption("(C) 2004 Ricas");

	// Create the Ok button
	Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 25, GetHeight() - 50, 50, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

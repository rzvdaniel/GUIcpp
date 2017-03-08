//-------------------------------------------------------------------
//  About.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "About.h"
#include "guide/vcl.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TFormAbout()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
TFormAbout::TFormAbout()
{
}

//-------------------------------------------------------------------
//  ~TFormAbout()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
TFormAbout::~TFormAbout()
{
}

//-------------------------------------------------------------------
//  Create()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TFormAbout::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);

	SetCaption("About");
	SetColor(0x80AAFFFF); // Transparent yellow

	// Ok button
	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 32, GetHeight() - 50, 64, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);

	// 'MD2 Viewer v1.0' label
	TLabel* Label0 = new TLabel;
	Label0->Create(this, TRect(1, 50, GetWidth()-2, 18));
	Label0->SetColor(0x01FFFFFF); // transparent white
	Label0->SetCaptionColor(clBlack);
	Label0->SetTextAlignment(taCenter);
	Label0->SetCaption("MD2 Viewer v1.1");

	// 'Created by' label
	TLabel* Label1 = new TLabel;
	Label1->Create(this, TRect(1, 80, GetWidth()-2, 18));
	Label1->SetColor(0x01FFFFFF); // transparent white
	Label1->SetCaptionColor(clGray);
	Label1->SetTextAlignment(taCenter);
	Label1->SetCaption("Created by");

	// 'Razvan Predescu' label
	TLabel* Label2 = new TLabel;
	Label2->Create(this, TRect(1, 100, GetWidth()-2, 18));
	Label2->SetColor(0x01FFFFFF); // transparent white
	Label2->SetTextAlignment(taCenter);
	Label2->SetCaption("Razvan Predescu");

	// 'Razvan Predescu' label
	TLabel* Label3 = new TLabel;
	Label3->Create(this, TRect(1, 130, GetWidth()-2, 18));
	Label3->SetColor(0x01FFFFFF); // transparent white
	Label3->SetTextAlignment(taCenter);
	Label3->SetCaption("Original md2 viewer code by:");

	// 'Razvan Predescu' label
	TLabel* Label4 = new TLabel;
	Label4->Create(this, TRect(1, 150, GetWidth()-2, 18));
	Label4->SetColor(0x01FFFFFF); // transparent white
	Label4->SetTextAlignment(taCenter);
	Label4->SetCaption("Mustata Bogdan (LoneRunner)");

	// 'Copyright 2004' label
	TLabel* Label5 = new TLabel;
	Label5->Create(this, TRect(1, 180, GetWidth()-2, 18));
	Label5->SetColor(0x01FFFFFF); // transparent white
	Label5->SetCaptionColor(clGray);
	Label5->SetTextAlignment(taCenter);
	Label5->SetCaption("Copyright (C) 2008");

	// 'Lt. Lone Wolves Game Development' label
	TLabel* Label6 = new TLabel;
	Label6->Create(this, TRect(1, 200, GetWidth()-2, 18));
	Label6->SetColor(0x01FFFFFF); // transparent white
	Label6->SetTextAlignment(taCenter);
	Label6->SetCaption("Razvan Predescu (Ricas)");
}



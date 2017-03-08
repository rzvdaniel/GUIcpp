//-------------------------------------------------------------------
//  Help.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "Help.h"
#include "guide/vcl.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TFormHelp()
//  08-Oct-2004   rzv    created
//-------------------------------------------------------------------
TFormHelp::TFormHelp()
{
}

//-------------------------------------------------------------------
//  ~TFormHelp()
//  08-Oct-2004   rzv    created
//-------------------------------------------------------------------
TFormHelp::~TFormHelp()
{
}

//-------------------------------------------------------------------
//  Create()
//  08-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TFormHelp::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{
	TForm::Create(AOwner, Rect, HasCaption);

	SetCaption("Help");
	SetColor(0x80AAFFFF); // Transparent yellow

	// Zoom
	TLabel* LabelUse = new TLabel;
	LabelUse->Create(this, TRect(0, 70, GetWidth(), 18));
	LabelUse->SetTextAlignment(taCenter);
	LabelUse->SetCaption("How to use:");
	LabelUse->SetColor(0x01FFFFFF); // transparent white

	// Zoom
	TLabel* Label0 = new TLabel;
	Label0->Create(this, TRect(0, 100, GetWidth(), 18));
	Label0->SetTextAlignment(taCenter);
	Label0->SetCaption("SHIFT + LEFT MOUSE BUTTON  =  ZOOM");
	Label0->SetColor(0x01FFFFFF); // transparent white

	// Rotate
	TLabel* Label1 = new TLabel;
	Label1->Create(this, TRect(0, 130, GetWidth(), 18));
	Label1->SetTextAlignment(taCenter);
	Label1->SetCaption("LEFT MOUSE BUTTON  =  ROTATE");
	Label1->SetColor(0x01FFFFFF); // transparent white

	// Translate
	TLabel* Label2 = new TLabel;
	Label2->Create(this, TRect(0, 160, GetWidth(), 18));
	Label2->SetTextAlignment(taCenter);
	Label2->SetCaption("ARROW KEYS  =  TRANSLATE");
	Label2->SetColor(0x01FFFFFF); // transparent white

	// Translate
	TLabel* Label3 = new TLabel;
	Label3->Create(this, TRect(0, 190, GetWidth(), 18));
	Label3->SetTextAlignment(taCenter);
	Label3->SetCaption("RIGHT CLICK  =  POPUP MENU");
	Label3->SetColor(0x01FFFFFF); // transparent white

	// Ok button
	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 32, GetHeight() - 50, 64, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

//-------------------------------------------------------------------
//  Test5.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "tests/Test5.h"

//-------------------------------------------------------------------
//  TTest5()
//  10-Sep-2004   rzv    created
//-------------------------------------------------------------------
TTest5::TTest5()
{
}

//-------------------------------------------------------------------
//  ~TTest5()
//  10-Sep-2004   rzv    created
//-------------------------------------------------------------------
TTest5::~TTest5()
{
}

//-------------------------------------------------------------------
//  Create()
//  10-Sep-2004   rzv    created
//-------------------------------------------------------------------
void TTest5::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);
	
	SetCaption("Test5");

	ListBox1 = new TListBox;
	ListBox1->Create(this, TRect(50, 50, GetWidth() - 100, GetHeight() - 120));
	ListBox1->SetScrollStyle(ssBoth);
	ListBox1->VertScrollBar->SetLargeChange(5);

	TButton* Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 60, GetHeight() - 50, 80, 0));
	Cancel->SetCaption("Cancel");
	Cancel->SetEnabled(false);
	
	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 90, GetHeight() - 50, 50, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);	
	
	Btn = new TButton;
	Btn->Create(this, TRect(GetWidth()/2 - 20, GetHeight() - 50, 60, 0));
	Btn->SetCaption("Add");

	// This will set the OnClick() event for the button to OnButton1Click() function.
	Btn->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TTest5::OnButton1Click);

	TListBoxItem* Item;
	static int i;
	for(i=0; i<40; i++)
	{
		TString Str("Hello!");

		char buf[128];
		sprintf( buf, "%d", i);
		Str.append(buf);

		Item = new TListBoxItem;
		Item->SetString(Str);
		ListBox1->Items->Append(Item);
	}
}

//-------------------------------------------------------------------
//  OnButton1Click()
//  07-June-2004   rzv    created
//-------------------------------------------------------------------
void TTest5::OnButton1Click(void)
{
	TListBoxItem* Item;
	static bool first = true;
	static int i;

	if(first == true)
	{
		for(i=0; i<20; i++)
		{
			TString Str("Hello!");
			
			char buf[128];
			sprintf( buf, "%d", i);
			Str.append(buf);

			Item = new TListBoxItem;
			Item->SetString(Str);
			ListBox1->Items->Append(Item);
		}

		first = false;
	}
	else
	{		
		TString Str("Hello!");

		char buf[128];
		sprintf( buf, "%d", i);
		Str.append(buf);

		Item = new TListBoxItem;
		Item->SetString(Str);
		ListBox1->Items->Append(Item);

		i++;
	}
}
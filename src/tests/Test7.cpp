//-------------------------------------------------------------------
//  Test7.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/skin.h"
#include "guide/opendialog.h"
#include "guide/debug.h"
#include "tests/Test7.h"

//-------------------------------------------------------------------
//  TTest7()
//  05-Oct-2004   rzv    created
//-------------------------------------------------------------------
TTest7::TTest7()
{
}

//-------------------------------------------------------------------
//  ~TTest7()
//  05-Oct-2004   rzv    created
//-------------------------------------------------------------------
TTest7::~TTest7()
{
}

//-------------------------------------------------------------------
//  Create()
//  05-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TTest7::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);

	SetCaption("Test7");

	// Main menu
	TMainMenu* MainMenu1 = new TMainMenu;
	MainMenu1->Create(this, alTop);

	TMainMenuItem* File = new TMainMenuItem;
	File->Create(this);
	File->SetCaption("File");

	TMainMenuItem* Edit = new TMainMenuItem;
	Edit->Create(this);
	Edit->SetCaption("Edit");

	MainMenu1->Items->Append(File);
	MainMenu1->Items->Append(Edit);

	// File menu
	TPopupMenu* FileMenu = new TPopupMenu;
	FileMenu->Create(this);

	TPopupMenuItem* FileNew = new TPopupMenuItem;
	FileNew->Create(this);
	FileNew->SetCaption("New Ctrl+N");

	//TPopupMenuItem* FileOpen = new TPopupMenuItem;
	FileOpen = new TPopupMenuItem;
	FileOpen->Create(this);
	FileOpen->SetCaption("Open Ctrl+O");
	FileOpen->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TTest7::OnFileOpen);

	TPopupMenuItem* FileSave = new TPopupMenuItem;
	FileSave->Create(this);
	FileSave->SetCaption("Save Ctrl+S");

	TPopupMenuItem* FileExit = new TPopupMenuItem;
	FileExit->Create(this);
	FileExit->SetCaption("Exit Ctrl+C");

	FileMenu->Items->Append(FileNew);
	FileMenu->Items->Append(FileOpen);
	FileMenu->Items->Append(FileSave);
	FileMenu->Items->Append(FileExit);

	File->SetMenu(FileMenu);

	// Edit menu
	TPopupMenu* EditMenu = new TPopupMenu;
	EditMenu->Create(this);

	TPopupMenuItem* EditCut = new TPopupMenuItem;
	EditCut->Create(this);
	EditCut->SetCaption("Cut Ctrl+X");

	TPopupMenuItem* EditCopy = new TPopupMenuItem;
	EditCopy->Create(this);
	EditCopy->SetCaption("Copy Ctrl+C");

	TPopupMenuItem* EditPaste = new TPopupMenuItem;
	EditPaste->Create(this);
	EditPaste->SetCaption("Paste Ctrl+V");

	EditMenu->Items->Append(EditCut);
	EditMenu->Items->Append(EditCopy);
	EditMenu->Items->Append(EditPaste);

	Edit->SetMenu(EditMenu);

	// Popup menu
	TPopupMenu* PopupMenu1 = new TPopupMenu;
	PopupMenu1->Create(this);

	TPopupMenuItem* PopupItem1 = new TPopupMenuItem;
	PopupItem1->Create(this);
	PopupItem1->SetCaption("Popup Item 1");

	TPopupMenuItem* PopupItem2 = new TPopupMenuItem;
	PopupItem2->Create(this);
	PopupItem2->SetCaption("Popup Item 2");

	TPopupMenuItem* PopupItem3 = new TPopupMenuItem;
	PopupItem3->Create(this);
	PopupItem3->SetCaption("Popup Item 3");

	TPopupMenuItem* PopupItem4 = new TPopupMenuItem;
	PopupItem4->Create(this);
	PopupItem4->SetCaption("Popup Ite4");

	PopupMenu1->Items->Append(PopupItem1);
	PopupMenu1->Items->Append(PopupItem2);
	PopupMenu1->Items->Append(PopupItem3);
	PopupMenu1->Items->Append(PopupItem4);

	SetPopupMenu(PopupMenu1);

	OpenDialog = new TOpenDialog;
	OpenDialog->Create(NULL, TRect(200, 100, 450, 400), true);

	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 25, GetHeight() - 50, 50, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

//-------------------------------------------------------------------
//  Create()
//  05-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TTest7::OnFileOpen(void)
{
	OpenDialog->SetTitle("Open");
	OpenDialog->SetFilter("All files (*.*)|*.*");

	if(OpenDialog->Execute() == mrOk)
	{
		if(!OpenDialog->GetFileName().empty())
		{
			t_printf("%s\n", OpenDialog->GetFileName());
			//EditModel->SetText(OpenDialog->GetFileName());
		}
	}	
}

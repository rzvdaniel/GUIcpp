//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Form1.h"

//-------------------------------------------------------------------
//  TForm1()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
TForm1::TForm1()
{
}

//-------------------------------------------------------------------
//  ~TForm1()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
TForm1::~TForm1()
{
}

//-------------------------------------------------------------------
//  Create()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{
	// First, call the base class Create() function
	TForm::Create(AOwner, Rect, HasCaption);
	
	// Create the second form
	Form2 = new TForm2;
	Form2->Create(this, TRect(200, 100, 400, 300), true);

	// Main menu
	TMainMenu* MainMenu1 = new TMainMenu;
	MainMenu1->Create(this, alTop);

	TMainMenuItem* File = new TMainMenuItem;
	File->Create(this);
	File->SetCaption("File");

	TMainMenuItem* Edit = new TMainMenuItem;
	Edit->Create(this);
	Edit->SetCaption("Edit");

	TMainMenuItem* View = new TMainMenuItem;
	View->Create(this);
	View->SetCaption("View");

	MainMenu1->Items->Append(File);
	MainMenu1->Items->Append(Edit);
	MainMenu1->Items->Append(View);

	// File menu
	TPopupMenu* FileMenu = new TPopupMenu;
	FileMenu->Create(this);

	FileNew = new TPopupMenuItem;
	FileNew->Create(this);
	FileNew->SetCaption("New Ctrl+N");

	FileOpen = new TPopupMenuItem;
	FileOpen->Create(this);
	FileOpen->SetCaption("Open Ctrl+O");

	FileSave = new TPopupMenuItem;
	FileSave->Create(this);
	FileSave->SetCaption("Save Ctrl+S");

	FileExit = new TPopupMenuItem;
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

	EditCut = new TPopupMenuItem;
	EditCut->Create(this);
	EditCut->SetCaption("Cut Ctrl+X");

	EditCopy = new TPopupMenuItem;
	EditCopy->Create(this);
	EditCopy->SetCaption("Copy Ctrl+C");

	EditPaste = new TPopupMenuItem;
	EditPaste->Create(this);
	EditPaste->SetCaption("Paste Ctrl+V");

	EditMenu->Items->Append(EditCut);
	EditMenu->Items->Append(EditCopy);
	EditMenu->Items->Append(EditPaste);

	Edit->SetMenu(EditMenu);

	// View menu
	TPopupMenu* ViewMenu = new TPopupMenu;
	ViewMenu->Create(this);

	ViewForm2 = new TPopupMenuItem;
	ViewForm2->Create(this);
	ViewForm2->SetCaption("Toggle Form2");
	ViewForm2->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnViewForm2Click);

	ViewMenu->Items->Append(ViewForm2);

	View->SetMenu(ViewMenu);
}

//-------------------------------------------------------------------
//  OnPaint()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnPaint(void)
{
	// Here is our trick! Overwrite the OnPaint method for this
	// form so the user can not see its background. For this, call
	// TWinControl::OnPaint() instead of TForm::OnPaint().

	// We need this to render child controls this form may have
	TWinControl::OnPaint();

	// Now we'll have an invisible form rendered at top of the 3D scene
}

//-------------------------------------------------------------------
//  OnViewForm2Click()
//  21-Oct-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnViewForm2Click(void)
{
	Form2->SetVisible(!Form2->GetVisible());
}

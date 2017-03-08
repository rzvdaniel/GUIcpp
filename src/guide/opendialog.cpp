#define N_IMPLEMENTS TOpenDialog
//-------------------------------------------------------------------
//  opendialog.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/opendialog.h"
#include "guide/screen.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TOpenDialog()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
TOpenDialog::TOpenDialog()
{
	Files = NULL;
	Title.assign("Open");
	Filter.assign("All Files (*.*)|*.*;");
	FilterIndex = 0;
}

//-------------------------------------------------------------------
//  ~TOpenDialog()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
TOpenDialog::~TOpenDialog()
{	
}

//-------------------------------------------------------------------
//  Create()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TOpenDialog::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{
	// Fixed dimensions for dialog
	TRect FixedRect(Rect.left, Rect.top, 450, 400);

	TForm::Create(AOwner, FixedRect, HasCaption);

	FileListBox = new TFileListBox;
	FileListBox->Create(this, TRect(230, 60, 200, GetHeight() - 150));
	FileListBox->FOnSelectionChange = makeFunctor((TNotifyEvent*)0, *this, &TOpenDialog::OnFileListBoxSelectionChange);

	DirectoryListBox = new TDirectoryListBox;
	DirectoryListBox->Create(this, TRect(20, 60, 200, GetHeight() - 150));
	DirectoryListBox->SetFileList(FileListBox);
	
	DriveComboBox = new TDriveComboBox;
	DriveComboBox->Create(this, TRect(20, 30, 200, 0));
	DriveComboBox->SetDirectoryListBox(DirectoryListBox);

	FilterComboBox = new TFilterComboBox;
	FilterComboBox->Create(this, TRect(230, 30, 200, 0));
	FilterComboBox->SetFilter(Filter);
	FilterComboBox->SetFileListBox(FileListBox);

	EditBox = new TEdit;
	EditBox->Create(this, TRect(20, DirectoryListBox->GetTop() + DirectoryListBox->GetHeight() + 10, GetWidth() - 40, 0));

	Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 100, EditBox->GetTop() + EditBox->GetHeight() + 15, 50, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);

	Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 20, EditBox->GetTop() + EditBox->GetHeight() + 15, 50, 0));
	Cancel->SetCaption("Cancel");
	Cancel->SetModalResult(mrCancel);

	SetVisible(false);
}

//-------------------------------------------------------------------
//  SetTitle()
//  08-Jan-2004   rzv   created
//-------------------------------------------------------------------
void TOpenDialog::SetTitle(TString ATitle)
{
	SetCaption(ATitle);
}

//-------------------------------------------------------------------
//  Execute()
//  25-Dec-2003   rzv   created
//-------------------------------------------------------------------
TModalResult TOpenDialog::Execute(void)
{
	return ShowModal();
}

//-------------------------------------------------------------------
//  GetFileName()
//  24-Dec-2003   rzv   created
//-------------------------------------------------------------------
TString TOpenDialog::GetFileName(void) 
{
	return EditBox->GetText();
}

//-------------------------------------------------------------------
//  SetFilter()
//  24-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TOpenDialog::SetFilter(const TString& AFilter)
{
	if(AFilter.compare(Filter))
	{
		Filter.assign(AFilter);
		FilterComboBox->SetFilter(AFilter);	
	}
}

//-------------------------------------------------------------------
//  SetFilterIndex()
//  24-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TOpenDialog::SetFilterIndex(int Value)
{
	if(FilterIndex != Value)
	{
		if(Value >= 0 && Value < FilterComboBox->GetListBox()->Items->Count())
			FilterIndex = Value;
		else
			FilterIndex = 0;

		TListBoxItems* ListBoxItems = (TListBoxItems*)FilterComboBox->GetListBox()->Items;
		TListBoxItem* Item = (TListBoxItem*)ListBoxItems->GetItem(FilterIndex);
		FilterComboBox->SetText(Item->GetString());	
	}
}

//-------------------------------------------------------------------
//  SetInitialDir()
//  24-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TOpenDialog::SetInitialDir(TString AInitialDir)
{
	DirectoryListBox->SetDirectory(AInitialDir);
}

//-------------------------------------------------------------------
//  GetInitialDir()
//  24-Dec-2003   rzv   created
//-------------------------------------------------------------------
TString TOpenDialog::GetInitialDir(void) const
{
	return DirectoryListBox->GetDirectory();
}

//-------------------------------------------------------------------
//  OnSelectionChange()
//  26-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TOpenDialog::OnFileListBoxSelectionChange(void)
{
	EditBox->SetText(FileListBox->GetFileName());
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


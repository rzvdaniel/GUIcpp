//-------------------------------------------------------------------
//  Test6.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "tests/Test6.h"

//-------------------------------------------------------------------
//  TTest6()
//  29-Sep-2004   rzv    created
//-------------------------------------------------------------------
TTest6::TTest6()
{
}

//-------------------------------------------------------------------
//  ~TTest6()
//  29-Sep-2004   rzv    created
//-------------------------------------------------------------------
TTest6::~TTest6()
{
}

//-------------------------------------------------------------------
//  Create()
//  29-Sep-2004   rzv    created
//-------------------------------------------------------------------
void TTest6::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);
	
	SetCaption("List box");

	FileListBox1 = new TFileListBox;
	FileListBox1->Create(this, TRect(320, 50, 250, GetHeight() - 140));
	FileListBox1->SetScrollStyle(ssBoth);

	DirectoryListBox1 = new TDirectoryListBox;
	DirectoryListBox1->Create(this, TRect(40, 50, 250, GetHeight() - 140));
	DirectoryListBox1->SetScrollStyle(ssBoth);
	DirectoryListBox1->SetFileList(FileListBox1);

	DriveComboBox1 = new TDriveComboBox;
	DriveComboBox1->Create(this, TRect(40, GetHeight() - 80, 250, 0));
	DriveComboBox1->SetDirectoryListBox(DirectoryListBox1);

	FilterComboBox1 = new TFilterComboBox;
	FilterComboBox1->Create(this, TRect(320, GetHeight() - 80, 250, 0));
	FilterComboBox1->SetFileListBox(FileListBox1);
	FilterComboBox1->SetFilter("All files|*.*&Text files|*.txt;*.doc&Source files|*.cpp;*.cxx");

	// Debug only
	/*
	TFileServer* FileServer = Screen->GetFileServer();

#	ifdef __LINUX__
	DirectoryListBox1->SetDirectory("/root/Projects/guide/linux/");
#	elif __WIN32__
	DirectoryListBox1->SetCwd("D://guide/bin/");
#	endif

	t_printf("Current working dir: %s\n", FileServer->GetCwd());
	t_printf("Num entries in cwd: %d\n", FileServer->GetNumEntries());
	t_printf("Num directories in cwd: %d\n", FileServer->GetNumDirectories());
	t_printf("Num files in cwd: %d\n", FileServer->GetNumFiles());
	*/
   // End Debug only

	TButton* Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 25, GetHeight() - 40, 50, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);	
}

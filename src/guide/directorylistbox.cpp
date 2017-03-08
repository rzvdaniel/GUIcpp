#define N_IMPLEMENTS TDirectoryListBox
//-------------------------------------------------------------------
//  directorylistbox.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/directorylistbox.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TDirectoryListBox()
//  20-Dec-2003   rzv   created
//-------------------------------------------------------------------
TDirectoryListBox::TDirectoryListBox()
{
	FileList = NULL;
	DirLabel = NULL;
}

//-------------------------------------------------------------------
//  ~TDirectoryListBox()
//  20-Dec-2003   rzv   created
//-------------------------------------------------------------------
TDirectoryListBox::~TDirectoryListBox()
{	
}

//-------------------------------------------------------------------
//  Create()
//  20-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TDirectoryListBox::Create(TComponent* AOwner, const TRect& Rect)
{		
	TListBox::Create(AOwner, Rect);
		
	SetStyle(lbOwnerDrawFixed);
	SetScrollStyle(ssBoth);	
	SetDirectory(Screen->GetFileServer()->GetCwd());

	// Warning! Check if we have a valid font because a TDirectoryListBox
	// object is created with the Parent == Screen into the skin load stage
	// and at that moment, the Screen object does not has a font, yet.
	if(GetFont() != NULL)
	{
		float MaxHeight = (GetFont()->GetHeight() < Skin->GetIconSize(iconSmall) ? Skin->GetIconSize(iconSmall) : GetFont()->GetHeight());
		SetItemHeight(MaxHeight);
	}
}

//-------------------------------------------------------------------
//  SetDrive()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
#ifdef __WIN32__
void TDirectoryListBox::SetDrive(char Value)
{
	if(Drive != Value)
	{
		TFileServer* FileServer = Screen->GetFileServer();
		
		// New drive value
		Drive = Value; 

		// Set the new drive as current.
		FileServer->ChangeDrive(Drive);
				
		SetDirectory(FileServer->GetCwd());	
	}
}
#endif

//-------------------------------------------------------------------
//  SetDrive()
//  25-July-2005   rzv   created
//-------------------------------------------------------------------
#ifdef __LINUX__
void TDirectoryListBox::SetDrive(const char* Value)
{
		TFileServer* FileServer = Screen->GetFileServer();
	
		// Set the new drive as current.
		FileServer->ChangeDrive(Value);
				
		SetDirectory(FileServer->GetCwd());	
}

//-------------------------------------------------------------------
//  GetDrive()
//  25-July-2005   rzv   created
//-------------------------------------------------------------------
const char* TDirectoryListBox::GetDrive(void) const
{
	return Screen->GetFileServer()->GetDrive();	
}
#endif

//-------------------------------------------------------------------
//  SetDirectory()
//  21-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TDirectoryListBox::SetDirectory(TString Value) 
{ 
	SetDirectory(Value.c_str());
}

//-------------------------------------------------------------------
//  SetDirectory()
//  21-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TDirectoryListBox::SetDirectory(const char* Value) 
{ 				
	if(Directory.compare(Value)) 
	{
		TEntry Entry;
		TFileServer* FileServer = Screen->GetFileServer();

		Items->Clear();	
		Directory.assign(Value); 
		FileServer->SetCwd(Value);

		int NumEntries = FileServer->GetNumEntries();
		for(int i=0; i<=NumEntries; i++)
		{
			FileServer->GetEntry(Entry, i);
			if(Entry.GetAttrib().count(eaSubdir))
			{
				TListBoxItem* Item = new TListBoxItem;
				Item->SetString(Entry.GetName());

				// TODO! A better approach is to have different icons for different kind
				// of folders (common, shared, ftp etc).
				Item->SetIcon(Skin->GetIcon("folder", iconSmall));

				Items->Append(Item);
			}
		}
		
		if(FileList != NULL)
			FileList->SetDirectory(Directory);

		if(DirLabel != NULL)
			DirLabel->SetCaption(Directory);
	}
}

//-------------------------------------------------------------------
//  SetFileList()
//  22-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TDirectoryListBox::SetFileList(TFileListBox* AFileList) 
{ 
	FileList = AFileList; 

	if(FileList != NULL)
		FileList->SetDirectory(Directory);
}

//-------------------------------------------------------------------
//  OnDoubleClick()
//  21-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TDirectoryListBox::OnDoubleClick(void)
{	
	TListBox::OnDoubleClick();

	TListBoxItem* Item = GetFocusedItem();
	if(Item != NULL)
	{
		TString String = Screen->GetFileServer()->GetCwd();

		// It works on Linux and Windows.
		String.append("/");
		String.append(Item->GetString());
	
		if(String[3] == '//')
			String.erase(3, 1);

		SetDirectory(String);
	}
}

//-------------------------------------------------------------------
/**
*/
void TDirectoryListBox::OnDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State)
{
	// Selected item rect
	TListBoxItem* Item = (TListBoxItem*)Items->GetItem(Index);
	if(GetActive() && Item->HasState(liSelected))
	{
		Canvas->Brush->SetColor(GetSelectionColor());
		Canvas->FillRect(Rect.left, Rect.top, Rect.right, Rect.bottom);
	}

	// Item string
	Canvas->Pen->SetColor(GetCaptionColor());
	Canvas->Pen->SetStyle(psSolid);
	
	if(Item->GetIcon() != NULL)
	{
		// Render Icon
		Canvas->Brush->SetColor(clWhite);
		Canvas->Brush->SetTexture(Item->GetIcon());
		Canvas->FillRect(Rect.left, Rect.top, Skin->GetIconSize(iconSmall), Skin->GetIconSize(iconSmall));
		Canvas->Brush->SetTexture(NULL);
		
		int top = GetFont()->GetHeight() - Skin->GetIconSize(iconSmall);

		// Render string
		Canvas->Text(Rect.left + Skin->GetIconSize(iconSmall), Rect.top + abs(top), Item->GetString());
	}
	else
		Canvas->Text(Rect.left, Rect.top, Item->GetString());
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



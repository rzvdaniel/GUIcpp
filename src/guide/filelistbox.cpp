#define N_IMPLEMENTS TFileListBox
//-------------------------------------------------------------------
//  filelistbox.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/filelistbox.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TFileListBox()
//  20-Dec-2003   rzv   created
//-------------------------------------------------------------------
TFileListBox::TFileListBox()
{
	Mask.assign("*.*");
	ShowGlyphs = false;
}

//-------------------------------------------------------------------
//  ~TFileListBox()
//  20-Dec-2003   rzv   created
//-------------------------------------------------------------------
TFileListBox::~TFileListBox()
{	
}

//-------------------------------------------------------------------
//  Create()
//  20-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TFileListBox::Create(TComponent* AOwner, const TRect& Rect)
{		
	TListBox::Create(AOwner, Rect);

	SetScrollStyle(ssVertical);
	SetStyle(lbOwnerDrawFixed);
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
//  SetDirectory()
//  21-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TFileListBox::SetDirectory(TString Value) 
{ 
	SetDirectory(Value.c_str());
}

//-------------------------------------------------------------------
//  SetDirectory()
//  21-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TFileListBox::SetDirectory(const char* Value) 
{ 		
	// (Directory != Value)
	if(Directory.compare(Value)) 
	{
		Directory.assign(Value); 
		Screen->GetFileServer()->SetCwd(Value);
		Update();
	}
}

//-------------------------------------------------------------------
//  SetMask()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TFileListBox::SetMask(TString Value) 
{ 
	SetMask(Value.c_str());
}

//-------------------------------------------------------------------
//  SetMask()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TFileListBox::SetMask(const char* Value) 
{
	if(Mask.compare(Value))
	{
		Mask.assign(Value); 
		Update();
	}
}

//-------------------------------------------------------------------
//  Update()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TFileListBox::Update(void) 
{
	Items->Clear();	

	TStringList Extensions;
	TString Separators;
	Separators.assign("*.;");
	split(Mask, Separators, Extensions);
	
	TEntry Entry;
	TFileServer* FileServer = Screen->GetFileServer();
	int NumEntries = FileServer->GetNumEntries();

	for(int i=0;i<=NumEntries;i++)
	{
		FileServer->GetEntry(Entry, i);
		if(!(Entry.GetAttrib().count(eaSubdir)))
		{
			if(Extensions.size() != 0)
			{
				TStringList::iterator iter;
				for(iter = Extensions.begin(); iter != Extensions.end(); iter++)
				{
					if(FileServer->CheckExtension(Entry.GetName().c_str(), (*iter).c_str()))
					{
						TListBoxItem* Item = new TListBoxItem;
						Item->SetString(Entry.GetName());

						// TODO! A better approach is to have different icons for different kind
						// of folders (common, shared, ftp etc).
						Item->SetIcon(Skin->GetIcon("file", iconSmall));

						Items->Append(Item);
					}
				}
			}
			else
			{
				TListBoxItem* Item = new TListBoxItem;
				Item->SetString(Entry.GetName());

				// TODO! A better approach is to have different icons for different kind
				// of folders (common, shared, ftp etc).
				Item->SetIcon(Skin->GetIcon("file", iconSmall));

				Items->Append(Item);
			}
		}
	}	
}

//-------------------------------------------------------------------
//  GetFileName()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
TString TFileListBox::GetFileName(void)
{
	TString Str;

	TListBoxItem* Item = GetFocusedItem();
	if(Item != NULL)
		Str.assign(Item->GetString());

	return Str;
}

//-------------------------------------------------------------------
/**
*/
void TFileListBox::OnDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State)
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



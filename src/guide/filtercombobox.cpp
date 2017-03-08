#define N_IMPLEMENTS TFilterComboBox
//-------------------------------------------------------------------
//  filtercombobox.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/filtercombobox.h"
#include "guide/strings.h"
#include "guide/screen.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TFilterComboBox()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
TFilterComboBox::TFilterComboBox()
{
	FileList = NULL;
	Mask = "*.*";
}

//-------------------------------------------------------------------
//  ~TFilterComboBox()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
TFilterComboBox::~TFilterComboBox()
{	
}

//-------------------------------------------------------------------
//  Create()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TFilterComboBox::Create(TComponent* AOwner, const TRect& Rect)
{		
	TComboBox::Create(AOwner, Rect);	
}

//-------------------------------------------------------------------
//  SetFilter()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TFilterComboBox::SetFilter(const TString& AFilter)
{
	ListBox->Items->Clear();
	ListBox->SetHeight(0);

	TStringList Lines;
	TString Separators;
	Separators.assign("&");

	split(AFilter, Separators, Lines);

	if(Lines.size() != 0)
	{
		// Extract the lines from filter
		TStringList::iterator iter;
		for(iter = Lines.begin(); iter != Lines.end(); iter++)
		{
			TListBoxItem* Item = new TListBoxItem;
			Item->SetString((*iter));
			ListBox->Items->Append(Item);
		}

		// Fill the text of the filter combobox with the first line
		iter = Lines.begin();
		SetText((*iter));
	}	
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  23-Dec-2003   rzv    created
//-------------------------------------------------------------------
void TFilterComboBox::OnTextChanged(void)
{
	TComboBox::OnTextChanged();

	TStringList Lines;
	TString PseudoFilter(GetText());
	TString Separators("|");
	split(PseudoFilter, Separators, Lines);

	if(Lines.size() != 0)
	{
		// First line is filled with text (e.g. "Text files")
		// Second line contains extensions (e.g. "*.TXT;*.DOC;")
		TStringList::iterator iter = Lines.begin(); 
		
		// We want the second line..
		iter++;

		// Now we have the mask...
		Mask.assign((*iter));

		// Notify the file list box that it should have this mask...
		if(FileList != NULL)
			FileList->SetMask(Mask);
	}	
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



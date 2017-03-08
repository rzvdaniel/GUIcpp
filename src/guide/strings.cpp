#define N_IMPLEMENTS TStrings
//-------------------------------------------------------------------
//  strings.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/strings.h"
#include "guide/debug.h"


//-------------------------------------------------------------------
//  split()
//  (C) Rogue Wave Standard C++ Library User's Guide and Tutorial
//-------------------------------------------------------------------
void split(const TString& text, const TString& separators, TStringList& words)
{
	/*
	// Another split algorithm
	// #include <sstream>
	TStringList Lines;
	TString str;
	TString temp(text);
	std::istringstream iss(temp);
	while (std::getline(iss, str, '&')) {
	Lines.push_back(str);
	}
	*/

	int n = text.length();
	int start, stop;
	start = text.find_first_not_of(separators);
	while ((start >= 0) && (start < n)) 
	{
		stop = text.find_first_of(separators, start);
		if ((stop < 0) || (stop > n)) stop = n;
		words.push_back(text.substr(start, stop - start));
		start = text.find_first_not_of(separators, stop+1);
	}
}

//-------------------------------------------------------------------
//  TStringItem()
//  07-July-2003   rzv   created
//-------------------------------------------------------------------
TStringItem::TStringItem()
{
	Object = NULL;
}

//-------------------------------------------------------------------
//  ~TStringItem()
//  07-July-2003   rzv   created
//-------------------------------------------------------------------
TStringItem::~TStringItem()
{
}

//-------------------------------------------------------------------
//  SetString()
//  07-July-2003   rzv   created
//-------------------------------------------------------------------
void TStringItem::SetString(const TString& AString)
{
	String.assign(AString);
}


//-------------------------------------------------------------------
//  TStrings()
//  07-July-2003   rzv   created
//-------------------------------------------------------------------
TStrings::TStrings() 
{
}

//-------------------------------------------------------------------
//  ~TStrings()
//  07-July-2003   rzv   created
//-------------------------------------------------------------------
TStrings::~TStrings()
{	
}

//-------------------------------------------------------------------
//  GetString()
//  07-July-2003   rzv   created
//-------------------------------------------------------------------
TString TStrings::GetString(int Index)
{	
	TStringItem* Item = (TStringItem*)GetItem(Index);

	if(Item != NULL)
		return Item->GetString();

	return NULL;
}

//-------------------------------------------------------------------
//  GetObject()
//  07-July-2003   rzv   created
//-------------------------------------------------------------------
TObject* TStrings::GetObject(int Index)
{
	TStringItem* Item = (TStringItem*)GetItem(Index);

	if(Item != NULL)
		return Item->GetObject();

	return NULL;
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

#ifndef T_STRINGS_H
#define T_STRINGS_H
//-------------------------------------------------------------------
//  CLASS
//  TStrings
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TStrings
#include "guide/ndefdllclass.h"

#ifndef T_OBJECT_H
#include "guide/object.h"
#endif

#ifndef T_COLLECTION_H
#include "guide/collection.h"
#endif

#ifndef T_STRINGCI_H
#include "string.h"
#endif

#include <list>

//-------------------------------------------------------------------

typedef stl::list<TString> TStringList;

N_EXPORT void split(const TString& text, const TString& separators, TStringList& words);

//-------------------------------------------------------------------
/**
	@class TStringItem
	@brief A TCollectionItem subclass.

	TStringItem items are stored in TStrings collections.
*/
//-------------------------------------------------------------------
class N_PUBLIC TStringItem : public TCollectionItem
{	
	TObject* Object;
	TString String;

public:
	TStringItem();
	virtual ~TStringItem();

	void SetString(const TString& AString);
	TString GetString(void) { return String; }

	void SetObject(TObject* AObject) { Object = AObject; }
	TObject* GetObject(void) const { return Object; }
};



//-------------------------------------------------------------------
/**
	@class TStrings
	@brief A collection of TStringItem items.
*/
//-------------------------------------------------------------------
class N_PUBLIC TStrings : public TCollection
{
public:
	TStrings();
	virtual ~TStrings();
	
	TString GetString(int Index);
	TObject* GetObject(int Index);
};

//-------------------------------------------------------------------
#endif


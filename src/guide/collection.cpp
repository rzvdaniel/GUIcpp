#define N_IMPLEMENTS TCollection
//-------------------------------------------------------------------
//  collection.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include <algorithm>
#include "guide/collection.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
/**
	Constructor TCollectionItem.	
*/
TCollectionItem::TCollectionItem() 
{ 
	Index = -1;
	Collection = NULL;
}

//-------------------------------------------------------------------
/**
	Destructor TCollectionItem.	
*/
TCollectionItem::~TCollectionItem() 
{
}

//-------------------------------------------------------------------
/**
	Constructor TCollection.	
*/
TCollection::TCollection()
{
}

//-------------------------------------------------------------------
/**
	Destructor TCollection.	
*/
TCollection::~TCollection()
{
	Clear();
}

//-------------------------------------------------------------------
/**
	@param Index Index of the item to be returned.
	@return Item at the specified position, or <code>NULL</code> if no
			item was found.
*/
//-------------------------------------------------------------------
TCollectionItem* TCollection::GetItem(int Index)
{
	if(Index >= 0 && Index < Count())
		return Items.at(Index);

	return NULL;
}

//-------------------------------------------------------------------
/**
	@param Index Position where we want to insert the item.
	@param Item Item to be inserted into the collection.
*/
//-------------------------------------------------------------------
void TCollection::Insert(int Index, TCollectionItem* Item)
{
	if(Item != NULL)
	{		
        // Where to insert?
		TCollectionItemsList::iterator Where = Items.begin();
		for(int i=0; i<Index; i++)
			Where++;

		Items.insert(Where, Item);

		// Adjust item's properties
		Item->Index = Index;
		Item->Collection = this;
    }
}

//-------------------------------------------------------------------
/**
	Add the specified item to the end of the collection.

	@param Item Item to be inserted into the collection.
*/
//-------------------------------------------------------------------
void TCollection::Append(TCollectionItem* Item)
{
	if(Item != NULL)
	{
	    Items.push_back(Item);		
		Item->Index = Count() - 1;
		Item->Collection = this;
    }
}

//-------------------------------------------------------------------
/**
	Remove the item at specified position from the collection.

	@param Index Position from where we want to remove the item.
*/
//-------------------------------------------------------------------
void TCollection::Remove(int Index)
{
	// From where to remove?
	TCollectionItemsList::iterator Where = stl::find(Items.begin(), Items.end(), Items.at(Index));
	TCollectionItem* Item = (TCollectionItem*)(*Where);

	if(Item != NULL)
		delete Item;

	// First, erase the item from the list
	Items.erase(Where);	
}

//-------------------------------------------------------------------
/**
	This function also destroys all the items the collection is 
	containing.
*/
//-------------------------------------------------------------------
void TCollection::Clear(void)
{	
	// Deletes all items
	TCollectionItemsList::iterator Where;
	for(Where = Items.begin(); Where != Items.end(); Where++)
	{
		TCollectionItem* Item = (TCollectionItem*)(*Where);
		if(Item != NULL)
			delete Item;
	}

	// Erase all the items from the list
    Items.erase(Items.begin(), Items.end());
}

//-------------------------------------------------------------------
/**
	@return Numbers of items into the collection.
*/
//-------------------------------------------------------------------
int TCollection::Count(void) const
{
	return Items.size();
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

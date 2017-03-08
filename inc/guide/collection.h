#ifndef T_COLLECTION_H
#define T_COLLECTION_H

#undef N_DEFINES
#define N_DEFINES TCollection
#include "guide/ndefdllclass.h"

#include <deque>

//-------------------------------------------------------------------
/**
	@class TCollectionItem
	@brief TCollectionItem represents an item in a collection.
*/
//-------------------------------------------------------------------
class TCollection;
class N_PUBLIC TCollectionItem
{
	/// Item's index
	int Index;
	/// Item's collection
	TCollection* Collection;

public:
	friend class TCollection;

public:
	TCollectionItem();
	virtual ~TCollectionItem();

public:
	/// Returns item's index within the collection.
	int GetIndex(void) const { return Index; }
	/// Returns item's parent collection.
	TCollection* GetCollection(void) const { return Collection; }
};

typedef stl::deque<TCollectionItem*> TCollectionItemsList;

//-------------------------------------------------------------------
/**
	@class TCollection
	@brief Container for TCollectionItem objects.
*/
//-------------------------------------------------------------------
class N_PUBLIC TCollection 
{
	TCollectionItemsList Items;

public:
	TCollection();
	virtual ~TCollection();
	
	// Retrieve the item at the specified position.
	TCollectionItem* GetItem(int Index);

	/// Insert an item at the specified position.
	void Insert(int Index, TCollectionItem* Item);
	/// Append an item to the collection.
	void Append(TCollectionItem* Item);
	/// Remove an item from the collection.
	void Remove(int Index);
	/// Remove all items from the collection.
	void Clear(void);
	/// Returns numbers of items the collection is containing.
	int Count(void) const;	
};
                                                                   
//-------------------------------------------------------------------
#endif


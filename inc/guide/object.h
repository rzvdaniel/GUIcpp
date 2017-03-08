#ifndef T_OBJECT_H
#define T_OBJECT_H
//-------------------------------------------------------------------
//  CLASS
//  TObject
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TObject
#include "guide/ndefdllclass.h"

//-------------------------------------------------------------------

class N_PUBLIC TObject 
{
public:
	TObject() {}
	virtual ~TObject() {}

	virtual void Assign(TObject* Object);
};
                                                                   
//-------------------------------------------------------------------
#endif


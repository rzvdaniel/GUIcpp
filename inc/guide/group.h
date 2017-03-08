#ifndef T_GROUP_H
#define T_GROUP_H
//-------------------------------------------------------------------
//  CLASS
//  TGroup
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TGroup
#include "guide/ndefdllclass.h"

#ifndef T_COMPONENT_H
#include "guide/component.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TGroup
{
	TComponentsList* Components;

public:
	TGroup();
	virtual ~TGroup();
	
	TComponentsList* GetComponents(void) const { return Components; }

	virtual void InsertComponent(TComponent* Component);
	virtual void RemoveComponent(TComponent* Component);	
};

//-------------------------------------------------------------------
#endif


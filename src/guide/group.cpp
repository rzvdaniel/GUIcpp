#define N_IMPLEMENTS TGroup
//-------------------------------------------------------------------
//  group.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/group.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TGroup()
//  30-Nov-2002   rzv   created
//-------------------------------------------------------------------
TGroup::TGroup()
{
	Components = NULL;
}

//-------------------------------------------------------------------
//  ~TGroup()
//  30-Nov-2002   rzv   created
//-------------------------------------------------------------------
TGroup::~TGroup() 
{
	if(Components != NULL)
		delete Components;
}

//-------------------------------------------------------------------
//  InsertComponent()
//  30-Nov-2002   rzv   created
//-------------------------------------------------------------------
void TGroup::InsertComponent(TComponent* Component)
{
	if(Components == NULL)
		Components = new TComponentsList;
	
	if(Component != NULL) {
		Components->push_back(Component);
		Component->SetGroup(this);
	}
}

//-------------------------------------------------------------------
//  RemoveComponent()
//  30-Nov-2002   rzv   created
//-------------------------------------------------------------------
void TGroup::RemoveComponent(TComponent* Component)
{	
	Component->SetGroup(NULL);
	Components->remove(Component);
	if(Components->empty()) {
		delete Components;
		Components = NULL;
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

#define N_IMPLEMENTS TComponent
//-------------------------------------------------------------------
//  component.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/component.h"
#include "guide/group.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TComponent()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
TComponent::TComponent() 
{		
	Group		= NULL;
	Owner		= NULL;
	Components	= NULL;	
}

//-------------------------------------------------------------------
//  ~TComponent()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
TComponent::~TComponent() 
{
	DestroyComponents();

	if(Owner != NULL)
		Owner->RemoveComponent(this);
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TComponent::Create(TComponent* AOwner)
{
	if(AOwner != NULL)
		AOwner->InsertComponent(this);	
}

//-------------------------------------------------------------------
//  InsertComponent()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
void TComponent::InsertComponent(TComponent* Component)
{
	if(Components == NULL)
		Components = new TComponentsList;
	
	if(Component != NULL) 
	{
		Components->push_back(Component);
		Component->SetOwner(this);
	}
}

//-------------------------------------------------------------------
//  RemoveComponent()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
void TComponent::RemoveComponent(TComponent* Component)
{	
	Component->SetOwner(NULL);
	Components->remove(Component);
	if(Components->empty()) 
	{
		delete Components;
		Components = NULL;
	}
}

//-------------------------------------------------------------------
//  DestroyComponents()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
void TComponent::DestroyComponents(void)
{
	TComponent* Instance = NULL;
	while(Components != NULL) 
	{
		Instance = Components->back(); 	
		RemoveComponent(Instance);
		delete Instance;
	} 
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

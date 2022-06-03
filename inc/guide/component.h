#ifndef T_COMPONENT_H
#define T_COMPONENT_H
//-------------------------------------------------------------------
//  CLASS
//  TComponent 
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TComponent
#include "guide/ndefdllclass.h"

#ifndef T_OBJECT_H
#include "guide/object.h"
#endif

#ifndef T_STRINGCI_H
#include "string.h"
#endif

#include <list>

//-------------------------------------------------------------------

class TGroup;
class TComponent;

typedef stl::list<TComponent*> TComponentsList;

//-------------------------------------------------------------------

class N_PUBLIC TComponent : public TObject
{
	TString	Name;
	TGroup*	Group;	
	TComponent*	Owner;

protected:
	TComponentsList* Components;

public:
	TComponent();
	virtual ~TComponent();
	virtual void Create(TComponent* AOwner);

	TString GetName(void) const { return Name; }
	void SetName(const char* AName) { Name = AName; }
	
	TComponent* GetOwner(void) const { return Owner; }
	void SetOwner(TComponent* Component) { Owner = Component; }
	
	void SetGroup(TGroup* AGroup) { Group = AGroup; }
	TGroup* GetGroup(void) const { return Group; }
	
	TComponentsList* GetComponents(void) const { return Components; }

	virtual void InsertComponent(TComponent* Component);
	virtual void RemoveComponent(TComponent* Component);
	virtual void DestroyComponents(void);
};

//-------------------------------------------------------------------
#endif


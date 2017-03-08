#ifndef T_TEST4_H
#define T_TEST4_H
//-------------------------------------------------------------------
//  CLASS
//  TTest4
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif


class TTest4 : public TForm
{
public:  
    TTest4();
    virtual ~TTest4();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
	
};

#endif 

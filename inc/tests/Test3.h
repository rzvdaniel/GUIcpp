#ifndef T_TEST3_H
#define T_TEST3_H
//-------------------------------------------------------------------
//  CLASS
//  TTest3
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif


class TTest3 : public TForm
{
public:  
    TTest3();
    virtual ~TTest3();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
	
};

#endif 

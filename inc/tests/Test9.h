#ifndef T_TEST9_H
#define T_TEST9_H
//-------------------------------------------------------------------
//  CLASS
//  TTest9
//
//  (C) 2008 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TLabel;
class TTest9 : public TForm
{

public:  
    TTest9();
    virtual ~TTest9();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
};

#endif 

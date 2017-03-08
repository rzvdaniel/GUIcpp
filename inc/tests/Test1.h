#ifndef T_TEST1_H
#define T_TEST1_H
//-------------------------------------------------------------------
//  CLASS
//  TTest1
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TEdit;
class TLabel;
class TTest1 : public TForm
{
	TEdit* Edit1;
	TLabel* Label1;

public:  
    TTest1();
    virtual ~TTest1();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
	void OnEdit1TextChange(void);	
};

#endif 

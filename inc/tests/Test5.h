#ifndef T_TEST5_H
#define T_TEST5_H
//-------------------------------------------------------------------
//  CLASS
//  TTest5
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TButton;
class TListBox;
class TTest5 : public TForm
{
	TListBox* ListBox1;
	TButton* Btn;

public:  
    TTest5();
    virtual ~TTest5();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
	void OnButton1Click(void);
	
};

#endif 

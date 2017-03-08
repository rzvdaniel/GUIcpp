#ifndef T_FORM1_H
#define T_FORM1_H
//-------------------------------------------------------------------
//  CLASS
//  TForm1
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM2_H
#include "Form2.h"
#endif

class TButton;
class TForm1 : public TForm
{
    TForm2* Form2;
	TButton* Close;
	TButton* Button1;

public:  
    TForm1();
    virtual ~TForm1();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
	void OnButton1Click(void);	
};

#endif 

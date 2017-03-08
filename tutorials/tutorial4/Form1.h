#ifndef T_FORM1_H
#define T_FORM1_H
//-------------------------------------------------------------------
//  CLASS
//  TForm1
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TImage;
class TLabel;
class TButton;
class TForm1 : public TForm
{
    TImage* Image;
	TLabel* Label1;
	TLabel* Label2;
	TLabel* Label3;
	TLabel* Label4;
	TButton* Ok;

public:  
    TForm1();
    virtual ~TForm1();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
	void OnButton1Click(void);
};

#endif 

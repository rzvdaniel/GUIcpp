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

class TButton;
class TGroupBox;
class TCheckBtn;
class TRadioBtn;
class TForm1 : public TForm
{
    TGroupBox* GroupBox1;
	TGroupBox* GroupBox2;

	TCheckBtn* CheckBtn1;
	TCheckBtn* CheckBtn2;
	TCheckBtn* CheckBtn3;

	TGroup* RadioGroup;
	TRadioBtn* RadioBtn1;
	TRadioBtn* RadioBtn2;
	TRadioBtn* RadioBtn3;
	
	TButton* Disable1;
	TButton* Disable2;

public:  
    TForm1();
    virtual ~TForm1();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
	void OnDisable1Click(void);
	void OnDisable2Click(void);
};

#endif 

#ifndef T_FORM2_H
#define T_FORM2_H
//-------------------------------------------------------------------
//  CLASS
//  TForm2
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TButton;
class TForm2 : public TForm
{
	TButton* Ok;
	TButton* Cancel;

public:  
    TForm2();
    virtual ~TForm2();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
};

#endif 

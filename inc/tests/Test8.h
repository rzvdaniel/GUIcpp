#ifndef T_TEST8_H
#define T_TEST8_H
//-------------------------------------------------------------------
//  CLASS
//  TTest8
//
//  (C) 2008 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TLabel;
class TTest8 : public TForm
{

public:  
    TTest8();
    virtual ~TTest8();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
	void OnPaint(void);
};

#endif 

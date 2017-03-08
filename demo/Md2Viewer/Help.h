#ifndef T_HELP_H
#define T_HELP_H
//-------------------------------------------------------------------
//  CLASS
//  TFormHelp
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TFormHelp : public TForm
{
public:  
    TFormHelp();
    virtual ~TFormHelp();

	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
};

#endif 
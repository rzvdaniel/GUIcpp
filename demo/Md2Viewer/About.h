#ifndef T_ABOUT_H
#define T_ABOUT_H
//-------------------------------------------------------------------
//  CLASS
//  TFormAbout
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TTexture;
class TFormAbout : public TForm
{
public:  

    TFormAbout();
    virtual ~TFormAbout();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
};

#endif 
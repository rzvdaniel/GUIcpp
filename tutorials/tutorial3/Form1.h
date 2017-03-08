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

class TPanel1;
class TButton;
class TForm1 : public TForm
{
    /// Our 3D rendering area
	TPanel1* Panel1;
	/// Simple button
	TButton* Ok;

public:  
    TForm1();
    virtual ~TForm1();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
};

#endif 

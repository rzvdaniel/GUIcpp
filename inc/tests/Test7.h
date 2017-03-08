#ifndef T_TEST7_H
#define T_TEST7_H
//-------------------------------------------------------------------
//  CLASS
//  TTest7
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TOpenDialog;
class TPopupMenuItem;
class TTest7 : public TForm
{
	TOpenDialog* OpenDialog;
	TPopupMenuItem* FileOpen;

public:  
    TTest7();
    virtual ~TTest7();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
	void OnFileOpen(void);	
};

#endif 

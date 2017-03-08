#ifndef T_MAINSCREEN_H
#define T_MAINSCREEN_H
//-------------------------------------------------------------------
//  CLASS
//  TMainScreen
//
//  (C) 2008 Razvan Predescu
//-------------------------------------------------------------------
#ifndef C_PROTO_H
#include "Proto.h"
#endif

#ifndef T_FORM_H
#include "guide/form.h"
#endif

//-------------------------------------------------------------------
class TButton;
class TMainForm;
class TMainScreen : public TForm
{
	/// The proto object
	CProto* Proto;
	/// The main form where scene is rendered
	TMainForm* MainForm;
	/// UI controls
	TButton* ButtonNew;
	TButton* ButtonLoad;
	TButton* ButtonReturn;
	TButton* ButtonOptions;
	TButton* ButtonCredits;
	TButton* ButtonQuit;

public:  
    TMainScreen();
    virtual ~TMainScreen();
	virtual void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	/// Render the intro UI
	void OnPaint(void);
	/// Create a new proto object and delete the old one (if any)
	void OnButtonNew(void);
	/// Back to the running proto (if any)
	void OnButtonReturn(void);
	/// Exit the program
	void OnButtonQuit(void);
};

//-------------------------------------------------------------------
#endif 
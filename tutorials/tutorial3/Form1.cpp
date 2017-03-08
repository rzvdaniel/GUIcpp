//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2004 Ricas -- R.Predescu
//
//  Description:
//
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Panel1.h"
#include "Form1.h"

//-------------------------------------------------------------------
//  TTutorial1()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
TForm1::TForm1()
{
}

//-------------------------------------------------------------------
//  ~TForm1()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
TForm1::~TForm1()
{
}

//-------------------------------------------------------------------
//  Create()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{
	// First, call the base class Create() function
	TForm::Create(AOwner, Rect, HasCaption);
	
	// Set the form's caption
	SetCaption("Tutorial3");
	// Set this form as main form
	SetMain(true);
	
	// We are using this panel as a rendering area (see Panel1.cpp). It's
	// nicer and safer to render into a child control and not directly
	// on the form (but you can do this, if you want). You can insert
	// OpenGL code in any control that responds to the OnPaint event.
	Panel1 = new TPanel1;
	Panel1->Create(this, TRect(10, 40, GetWidth() - 20, GetHeight() - 100));

	// Create the Ok button
	Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 25, GetHeight() - 50, 50, 32));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
}

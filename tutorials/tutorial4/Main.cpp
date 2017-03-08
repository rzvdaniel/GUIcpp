//-------------------------------------------------------------------
//  Tutorial4
//  (C) 2004 Ricas -- R.Predescu
//
//  Description:
//
//  In this tutorial you'll learn how to create an about dialog
//  to use with your programs. An about dialog usually contains 
//  a logo, a short description of your company and a button to
//  close the dialog.
//
//  Classes used: TForm, TButton, TImage, TLabel
//-------------------------------------------------------------------

#include "guide/screenwindows.h"
#include "guide/debug.h"
#include "Form1.h"

int main(void)
{
	// Create the screen
	// Enter the resolution, bithdepth, fullscreen (true - false) and
	// the skin file standard control will use to set their appearance
	TScreenIndependent* Screen = new TScreenIndependent;
	Screen->Create(TRect(0, 0, 800, 600), 16, false, "../res/skins/aqua.xml");

	// Create the about dialog
	TForm1* Form1 = new TForm1;
	Form1->Create(NULL, TRect(200, 50, 400, 500), true);
	Form1->SetMain(true);
	Form1->ShowModal();
	
	// Enter application loop
	Screen->Run();
	
	// Clean up things
	delete Screen;	

	return 0;	
}

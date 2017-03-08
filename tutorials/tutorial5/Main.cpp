//-------------------------------------------------------------------
//  Tutorial5
//  (C) 2004 Ricas -- R.Predescu
//
//  Description:
//
//  Working with check and radio buttons. Also we'll use two group 
//  boxes to place buttons on it.
//
//  Classes used: TForm, TButton, TGroupBox, TCheckBtn, TRadioBtn
//-------------------------------------------------------------------

#include "guide/screenindependent.h"
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
	Form1->Create(NULL, TRect(100, 100, 600, 400), true);
	Form1->SetMain(true);
	Form1->ShowModal();
	
	// Enter application loop
	Screen->Run();
	
	// Clean up things
	delete Screen;	

	return 0;	
}

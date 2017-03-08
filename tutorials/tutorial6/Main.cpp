//-------------------------------------------------------------------
//  Tutorial6
//  (C) 2004 Ricas -- R.Predescu
//
//  Description:
//
//  This tutorial presents you the modality you can create 
//  standard buttons, placed on a form. Also you can see how 
//  you can attach an OnClick() event to a standard control 
//  (in this case, a simple button).
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

	// Create the tutorial's main form.
	TForm1* Form1 = new TForm1;
	Form1->Create(NULL, TRect(100, 50, 600, 500), true);
	Form1->SetMain(true);
	Form1->ShowModal();
	
	// Enter application loop
	Screen->Run();
	
	// Clean up things
	delete Screen;	

	return 0;	
}

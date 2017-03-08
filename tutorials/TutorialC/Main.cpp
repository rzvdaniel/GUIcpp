//-------------------------------------------------------------------
//  TutorialB
//  (C) 2007 Razvan Predescu
//
//  Description:
//
//  This tutorial presents you the modality you can create standard 
//  edit boxes, placed on a form.
//-------------------------------------------------------------------

#include "guide/screenindependent.h"
#include "guide/debug.h"
#include "Form1.h"

int main(void)
{
	// Create the screen
	// Enter the resolution, bit depth, full screen (true - false) and
	// the skin file that standard controls will use to set their appearance
	TScreenIndependent* Screen = new TScreenIndependent;
	Screen->Create(TRect(0, 0, 800, 600), 16, false, "../res/skins/flex.xml");
	Screen->SetClearColor(0.8f, 0.8f, 0.8f, 1.0);

	// Create the tutorial's main form.
	TForm1* Form1 = new TForm1;
	Form1->Create(NULL, TRect(100, 50, 600, 400), true);
	Form1->SetMain(true);
	Form1->ShowModal();

	// Enter application loop
	Screen->Run();
	
	// Clean up things
	delete Screen;	

	return 0;	
}

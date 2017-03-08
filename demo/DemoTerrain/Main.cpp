#include "guide/screenindependent.h"
#include "MainForm.h"

int main(void)
{
	// Create the screen
	// Enter the resolution, bit depth, full screen (true - false) and
	// the skin file standard controls will use to set their appearance
	TScreenIndependent* Screen = new TScreenIndependent;
	Screen->Create(TRect(0, 0, 800, 600), 16, false, "../res/skins/aqua.xml");
	
	// Here the main form is created
	TMainForm* MainForm = new TMainForm;
	MainForm->Create(NULL, TRect(0, 0, 800, 600), false);
	MainForm->SetMain(true);

	// Enter application loop
	Screen->Run();
	
	delete Screen;
	
	return 0;	
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

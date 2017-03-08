#include "guide/screenindependent.h"
#include "Form1.h"

int main(void)
{
	// Create the screen
	// Enter the resolution, bit depth, full screen (true - false) and
	// the skin file standard controls will use to set their appearance
	TScreenIndependent* Screen = new TScreenIndependent;
	Screen->Create(TRect(0, 0, 800, 600), 16, false, "../res/skins/aqua.xml");
	
	TForm1* Form1 = new TForm1;
	Form1->Create(NULL, TRect(100, 50, 600, 500), true);
	Form1->SetMain(true);

	Screen->Run();
	
	delete Screen;
	
	return 0;	
}

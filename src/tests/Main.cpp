#include "tests/Test1.h"
#include "tests/Test2.h"
#include "tests/Test3.h"
#include "tests/Test4.h"
#include "tests/Test5.h"
#include "tests/Test6.h"
#include "tests/Test7.h"
#include "tests/Test8.h"
#include "tests/Test9.h"
#include "guide/screenindependent.h"
#include "guide/debug.h"

int main(void)
{
	TScreenIndependent* Screen = new TScreenIndependent;
	if(!Screen->Create(TRect(0, 0, 1024, 768), 24, false, "../res/skins/aqua.xml"))
	{
		delete Screen;
		return 1;
	}

	Screen->SetClearColor(0.8f, 0.8f, 0.8f, 1.0);

	// Buttons
	TTest1* Test1 = new TTest1;
	Test1->Create(NULL, TRect(100, 50, 400, 300), true);
	Test1->SetMain(true);
	Test1->ShowModal();

	//// GroupBox, Radio & Check buttons
	//TTest2* Test2 = new TTest2;
	//Test2->Create(NULL, TRect(100, 100, 600, 400), true);
	//Test2->SetMain(true);
	//Test2->ShowModal();

	//// Bitmap buttons
	//TTest3* Test3 = new TTest3;
	//Test3->Create(NULL, TRect(100, 50, 600, 500), true);
	//Test3->SetMain(true);
	//Test3->ShowModal();

	//// Edit
	//TTest4* Test4 = new TTest4;
	//Test4->Create(NULL, TRect(100, 50, 600, 400), true);
	//Test4->SetMain(true);
	//Test4->ShowModal();

	//// List box
	//TTest5* Test5 = new TTest5;
	//Test5->Create(NULL, TRect(100, 50, 600, 500), true);
	//Test5->SetMain(true);
	//Test5->ShowModal();

	//// Directory and File list boxes
	//TTest6* Test6 = new TTest6;
	//Test6->Create(NULL, TRect(100, 50, 600, 500), true);
	//Test6->SetMain(true);
	//Test6->ShowModal();

	//// Menu
	//TTest7* Test7 = new TTest7;
	//Test7->Create(NULL, TRect(100, 50, 600, 500), true);
	//Test7->SetMain(true);
	//Test7->ShowModal();

	//// Icons
	//TTest8* Test8 = new TTest8;
	//Test8->Create(NULL, TRect(100, 50, 800, 600), true);
	//Test8->SetMain(true);
	//Test8->ShowModal();

	//// Alignment
	//TTest9* Test9 = new TTest9;
	//Test9->Create(NULL, TRect(100, 50, 800, 600), true);
	//Test9->SetMain(true);
	//Test9->ShowModal();

	Screen->Run();

	delete Screen;

	return 0;	
}

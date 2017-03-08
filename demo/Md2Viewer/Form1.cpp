//-------------------------------------------------------------------
//  Form1.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Panel1.h"
#include "Form1.h"

//-------------------------------------------------------------------
//  TForm1()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
TForm1::TForm1()
{
	Model = NULL;
}

//-------------------------------------------------------------------
//  ~TForm1()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
TForm1::~TForm1()
{
}

//-------------------------------------------------------------------
//  Create()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);

	SetCaption("MD2 viewer");
	SetColor(0x80AAFFFF); // Transparent yellow
	
	Form2 = new TForm2;
	Form2->Create(NULL, TRect(200, 200, 400, 200), true);
	Form2->SetVisible(false);
	Form2->SetMainForm(this);

	// We are using this panel as a rendering area (see Panel1.cpp). It's
	// nicer and safer to render into a child control and not directly
	// on the form (but you can do this, if you want). You can insert
	// OpenGL code in any control that responds to the OnPaint event.
	Panel1 = new TPanel1;
	Panel1->Create(this, TRect(10, 50, GetWidth() - 20, GetHeight() - 110));

	OpenDialog = new TOpenDialog;
	OpenDialog->Create(NULL, TRect(200, 100, 450, 400), true);
	OpenDialog->SetColor(0xFFEEEEEE); // Transparent white

	AboutForm = new TFormAbout;
	AboutForm->Create(NULL, TRect(180, 110, 440, 370), true);
	AboutForm->SetVisible(false);

	HelpForm = new TFormHelp;
	HelpForm->Create(NULL, TRect(180, 130, 440, 330), true);
	HelpForm->SetVisible(false);

	//-------------------------------------------------------------------
	// Main menu
	//-------------------------------------------------------------------
	MainMenu = new TMainMenu;
	MainMenu->Create(this);

	TMenuItem* File = new TMainMenuItem;
	File->Create(this);
	File->SetCaption("File");

	TMenuItem* Options = new TMainMenuItem;
	Options->Create(this);
	Options->SetCaption("Options");
	
	TMenuItem* Help = new TMainMenuItem;
	Help->Create(this);
	Help->SetCaption("Help");

	MainMenu->Items->Insert(0, File);
	MainMenu->Items->Insert(1, Options);
	MainMenu->Items->Insert(2, Help);

	//-------------------------------------------------------------------
	// File menu
	//-------------------------------------------------------------------
	FileMenu = new TPopupMenu;
	FileMenu->Create(this);

	TMenuItem* LoadModel = new TPopupMenuItem;
	LoadModel->Create(this);
	LoadModel->SetCaption("Load Model");

	TMenuItem* LoadSkin = new TPopupMenuItem;
	LoadSkin->Create(this);
	LoadSkin->SetCaption("Load Skin");

	TMenuItem* Exit = new TPopupMenuItem;
	Exit->Create(this);
	Exit->SetCaption("Exit");

	LoadModel->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnFileLoadModel);
	LoadSkin->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnFileLoadSkin);	
	Exit->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnFileExit);
	
	FileMenu->Items->Insert(0, LoadModel);
	FileMenu->Items->Insert(1, LoadSkin);	
	FileMenu->Items->Insert(2, Exit);

	File->SetMenu(FileMenu);

	//-------------------------------------------------------------------
	// Options menu
	//-------------------------------------------------------------------
	OptionsMenu = new TPopupMenu;
	OptionsMenu->Create(this);

	TMenuItem* Wireframe = new TPopupMenuItem;
	Wireframe->Create(this);
	Wireframe->SetCaption("Wireframe");
	Wireframe->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnOptionsWireframe);

	TMenuItem* Solid = new TPopupMenuItem;
	Solid->Create(this);
	Solid->SetCaption("Solid");
	Solid->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnOptionsSolid);	
	
	OptionsMenu->Items->Insert(0, Wireframe);
	OptionsMenu->Items->Insert(1, Solid);	

	Options->SetMenu(OptionsMenu);

	//-------------------------------------------------------------------
	// Help menu
	//-------------------------------------------------------------------
	HelpMenu = new TPopupMenu;
	HelpMenu->Create(this);
	
	TMenuItem* About = new TPopupMenuItem;
	About->Create(this);
	About->SetCaption("About");
	About->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnHelpAbout);	

	TMenuItem* HelpContents = new TPopupMenuItem;
	HelpContents->Create(this);
	HelpContents->SetCaption("Contents");
	HelpContents->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnHelpContents);	

	HelpMenu->Items->Insert(0, About);	
	HelpMenu->Items->Insert(1, HelpContents);

	Help->SetMenu(HelpMenu);

	//-------------------------------------------------------------------
	// Begin popup menu
	//-------------------------------------------------------------------
	
	PopupMenu = new TPopupMenu;
	PopupMenu->Create(this);
 
	TMenuItem* Next = new TPopupMenuItem;
	Next->Create(this);
	Next->SetCaption("Next");
	Next->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnNextAnimation);

	TMenuItem* Prev = new TPopupMenuItem;
	Prev->Create(this);
	Prev->SetCaption("Prev");
	Prev->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnPrevAnimation);

	TMenuItem* All = new TPopupMenuItem;
	All->Create(this);
	All->SetCaption("All");
	All->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnAllAnimations);

	Stop = new TPopupMenuItem;
	Stop->Create(this);
	Stop->SetCaption("Stop");
	Stop->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnToggleAnimations);

	PopupMenu->Items->Insert(0, Next);
	PopupMenu->Items->Insert(1, Prev);
	PopupMenu->Items->Insert(2, All);
	PopupMenu->Items->Insert(3, Stop);
	
	Panel1->SetPopupMenu(PopupMenu);

	//-------------------------------------------------------------------
	// End popup menu
	//-------------------------------------------------------------------

	// Ok button
	Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 32, GetHeight() - 45, 64, 0));
	Ok->SetCaption("Quit");
	Ok->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm1::OnOkClick);
}

//-------------------------------------------------------------------
//  SetStopPopupItemCaption()
//  21-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::SetStopPopupItemCaption(const char* ACaption)
{
	Stop->SetCaption(ACaption);
}

//-------------------------------------------------------------------
//  SetStopPopupItemCaption()
//  21-Jan-2004   rzv    created
//-------------------------------------------------------------------
TString TForm1::GetStopPopupItemCaption(void) const
{
	return Stop->GetCaption();
}

//-------------------------------------------------------------------
//  OnOkClick()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnOkClick(void)
{
	// Close the application
	Screen->Close();
}

//-------------------------------------------------------------------
//  OnFileLoadModel()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnFileLoadModel(void)
{
	Form2->ShowModal();
}

//-------------------------------------------------------------------
//  OnFileLoadSkin()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnFileLoadSkin(void)
{
	if(Model == NULL)
	{
		t_printf("Please load a model first.\n");
		return;
	}

	OpenDialog->SetTitle("Load skin");
	OpenDialog->SetFilter("Skin files (*.BMP;*.TGA)|*.BMP;*.TGA");

	if(OpenDialog->Execute() == mrOk)
	{
		if(!OpenDialog->GetFileName().empty())
		{
			bool Result = Model->LoadSkin(OpenDialog->GetFileName().c_str());
			if(Result == false)
				t_printf("Something wrong happens! Skin not loaded.\n");
		}
	}
}

//-------------------------------------------------------------------
//  OnFileExit()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnFileExit(void)
{
	// Close the application
	Screen->Close();
}

//-------------------------------------------------------------------
//  OnOptionsWireframe()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnOptionsWireframe(void)
{
	if(Model != NULL)
		Model->SetRenderStyle(rsLine);
}

//-------------------------------------------------------------------
//  OnOptionsSolid()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnOptionsSolid(void)
{
	if(Model != NULL)
		Model->SetRenderStyle(rsFill);
}

//-------------------------------------------------------------------
//  OnHelpContents()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnHelpContents(void)
{
	HelpForm->ShowModal();
}

//-------------------------------------------------------------------
//  OnHelpAbout()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnHelpAbout(void)
{
	AboutForm->ShowModal();
}

//-------------------------------------------------------------------
//  OnNextAnimation()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnNextAnimation(void)
{
	if(Model != NULL)
		Model->SetAnimation(Model->GetAnimation() + 1);
}

//-------------------------------------------------------------------
//  OnPrevAnimation()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnPrevAnimation(void)
{
	if(Model != NULL)
		Model->SetAnimation(Model->GetAnimation() - 1);
}

//-------------------------------------------------------------------
//  OnPrevAnim()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnAllAnimations(void)
{
	if(Model != NULL)
		Model->SetAnimation(0);
}

//-------------------------------------------------------------------
//  OnPrevAnim()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm1::OnToggleAnimations(void)
{
	if(Model != NULL)
	{
		Model->SetPause(!Model->GetPause());

		if(Model->GetPause())
			Stop->SetCaption("Start");
		else
			Stop->SetCaption("Stop");
	}
}
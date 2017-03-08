//-------------------------------------------------------------------
//  Form2.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "Md2.h"
#include "Form1.h"
#include "Form2.h"
#include "guide/vcl.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TForm2()
//  13-Jan-2004   rzv    created
//-------------------------------------------------------------------
TForm2::TForm2()
{
	Form1 = NULL;
	Model = NULL;
}

//-------------------------------------------------------------------
//  ~TForm2()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
TForm2::~TForm2()
{
	if(Model != NULL)
		delete Model;
}

//-------------------------------------------------------------------
//  Create()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm2::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TForm::Create(AOwner, Rect, HasCaption);

	// Good place to adjust several of form properties. 
	SetCaption("Load model");
	SetColor(0x80AAFFFF); // Transparent yellow

	// Create open dialog
	OpenDialog = new TOpenDialog;
	OpenDialog->Create(NULL, TRect(200, 100, 450, 400), true);
	OpenDialog->SetColor(0xFFEEEEEE); // Transparent white

	TLabel* Label1 = new TLabel;
	Label1->Create(this, TRect(5, 33, 60, 20));
	Label1->SetColor(0x01FFFFFF);
	Label1->SetCaptionColor(clRed);
	Label1->SetTextAlignment(taRightJustify);
	Label1->SetCaption("Model:");

	EditModel = new TEdit;
	EditModel->Create(this, TRect(70, 33, 256, 0));

	// LoadModel button
	LoadModel = new TButton;
	LoadModel->Create(this, TRect(340, 33, 32, 22));
	LoadModel->SetCaption("..");
	LoadModel->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm2::OnLoadModelClick);

	TLabel* Label2 = new TLabel;
	Label2->Create(this, TRect(5, 63, 60, 20));
	Label2->SetColor(0x01FFFFFF);
	Label2->SetCaptionColor(clRed);
	Label2->SetTextAlignment(taRightJustify);
	Label2->SetCaption("Skin:");

	EditSkin = new TEdit;
	EditSkin->Create(this, TRect(70, 63, 256, 0));

	// LoadSkin button
	LoadSkin = new TButton;
	LoadSkin->Create(this, TRect(340, 63, 32, 22));
	LoadSkin->SetCaption("..");
	LoadSkin->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm2::OnLoadSkinClick);

	// Ok button
	Ok = new TButton;
	Ok->Create(this, TRect(GetWidth()/2 - 64 - 10, GetHeight() - 50, 64, 0));
	Ok->SetCaption("Ok");
	Ok->SetModalResult(mrOk);
	Ok->FOnClick = makeFunctor((TNotifyEvent*)0,*this, &TForm2::OnOkClick);

	// Cancel button
	Cancel = new TButton;
	Cancel->Create(this, TRect(GetWidth()/2 + 10, GetHeight() - 50, 64, 0));
	Cancel->SetCaption("Cancel");
	Cancel->SetModalResult(mrCancel);
}

//-------------------------------------------------------------------
//  OnOkClick()
//  13-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm2::OnOkClick(void)
{
	TString ModelFilename = EditModel->GetText();

	// Load model
	if(!ModelFilename.empty())
	{
		// Load a model only if we don't have already one or if the
		// name of the model we have is different from the one we 
		// want to load
		if(Model == NULL || (Model != NULL && Model->GetName().compare(ModelFilename)))
		{
			TMd2* TempModel = new TMd2;	
			bool Result = TempModel->LoadModel(ModelFilename.c_str());
			if(Result == false)
			{
				t_printf("Model not loaded!\n");
				delete TempModel;
				TempModel = NULL;
			}
			else
			{
				if(Model != NULL)
				{
					delete Model;
					Model = NULL;
				}

				Model = TempModel;
				Form1->SetModel(Model);
				
				if(Form1->GetStopPopupItemCaption().compare("Stop"))
					Form1->SetStopPopupItemCaption("Stop");

				t_printf("Model name: %s\n", ModelFilename.c_str());
			}
		}
	}

	TString SkinFilename = EditSkin->GetText();

	// Load skin
	if(!SkinFilename.empty())
	{
		if(Model == NULL)
		{
			t_printf("Please load a model first.\n");
			return;
		}
		
		// Load a skin only the model hasn't one
		if(Model->GetSkin().compare(SkinFilename))
		{
			bool Result = Model->LoadSkin(SkinFilename.c_str());
			if(Result == false)
				t_printf("Skin not loaded!\n");
		}
	}
}

//-------------------------------------------------------------------
//  OnLoadModelClick()
//  13-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm2::OnLoadModelClick(void)
{	
	OpenDialog->SetTitle("Load model");
	OpenDialog->SetFilter("MD2 files (*.md2)|*.md2");

	if(OpenDialog->Execute() == mrOk)
	{
		if(!OpenDialog->GetFileName().empty())
		{
			EditModel->SetText(OpenDialog->GetFileName().c_str());
		}
	}	
}

//-------------------------------------------------------------------
//  OnLoadSkinClick()
//  13-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TForm2::OnLoadSkinClick(void)
{
	OpenDialog->SetTitle("Load skin");
	OpenDialog->SetFilter("Skin files (*.bmp;*.tga)|*.bmp;*.tga");

	if(OpenDialog->Execute() == mrOk)
	{
		if(!OpenDialog->GetFileName().empty())
		{
			EditSkin->SetText(OpenDialog->GetFileName().c_str());
		}
	}
}

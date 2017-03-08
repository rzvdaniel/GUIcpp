#define N_IMPLEMENTS TForm
//-------------------------------------------------------------------
//  form.cpp
//  (C) 2002 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/form.h"
#include "guide/skin.h"
#include "guide/screen.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TForm()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
TForm::TForm()
{
	CaptionBar = NULL;
	ModalResult = mrNone;
	Main = false;
	MinWidth = 50;
	MinHeight = 23;
}

//-------------------------------------------------------------------
//  ~TForm()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
TForm::~TForm()
{
	if(Screen != NULL)
		Screen->RemoveForm(this);
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TForm::Create(TComponent* AOwner, const TRect& Rect, bool HasCaption)
{	
	TWinControl::Create(AOwner, Rect);

	Screen->InsertForm(this);

	if(HasCaption == true)
	{  
	    // Create captionbar
		CaptionBar = new TCaptionBar; 
		CaptionBar->Create(this, TRect(0, 0, 0, 0));

		// Set the minimum allowed height to the caption's height
		SetMinHeight(CaptionBar->GetHeight());
	}

	ApplySkin(Skin->Form);
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TForm::Assign(TObject* Object)
{
	TWinControl::Assign(Object);
}

//-------------------------------------------------------------------
void TForm::ApplySkin(TObject* Object)
{
	TWinControl::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  SetMain()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TForm::SetMain(bool Value) 
{ 
	if(Main != Value)
	{
		if(Value == true)
		{
			TForm* MainForm = Screen->GetMainForm();
			if(MainForm != NULL)
				MainForm->SetMain(false);
		}

		Main = Value; 	
	}
}

//-------------------------------------------------------------------
//  SetCaption()
//  21-May-2004   rzv   created
//-------------------------------------------------------------------
void TForm::SetCaption(const char* ACaption) 
{	
	TWinControl::SetCaption(ACaption); 

	if(CaptionBar != NULL)
		CaptionBar->SetCaption(ACaption);
}

//-------------------------------------------------------------------
//  SetCaption()
//  21-May-2004   rzv   created
//-------------------------------------------------------------------
void TForm::SetCaption(TString ACaption)
{
	SetCaption(ACaption.c_str());
}

//-------------------------------------------------------------------
//  SetModalResult()
//  24-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TForm::SetModalResult(TModalResult Value)
{
	if(ModalResult != Value)
		ModalResult = Value;
}

//-------------------------------------------------------------------
//  ShowModal()
//  24-Dec-2003   rzv   created
//-------------------------------------------------------------------
TModalResult TForm::ShowModal(void)
{ 
    // This form is now modal
    ModalResult = mrNone;
    
	// Assure it is visible
	SetVisible(true);
	
	// Insert the modal form to the list
	Screen->InsertModalForm(this);

	// Enter the modal loop
	while(ModalResult == mrNone)
		Screen->Idle();
    
	// Remove the modal form from the list
	Screen->RemoveModalForm(this);

	// Close the form
	CMClose();

	return ModalResult;
}

//-------------------------------------------------------------------
//  Close()
//  07-June-2004   rzv   created
//-------------------------------------------------------------------
void TForm::Close(void)
{
	CMClose();
}

//-------------------------------------------------------------------
//  CMClose()
//  29-July-2002   rzv   created
//-------------------------------------------------------------------
void TForm::CMClose(void)
{
	OnClose();

	Hide();

	if(Main == true)
		Screen->Close();
}

//-------------------------------------------------------------------
/**
	This function will paint borders according with the specified 
	border width and color.
*/
//-------------------------------------------------------------------
void TForm::PaintBorders(void)
{
	if(BorderWidth)
	{
		Canvas->Pen->SetColor(BorderColor);

		if(CaptionBar != NULL)
			Canvas->DrawRect(0, CaptionBar->GetHeight(), GetWidth()-BorderWidth, GetHeight()-CaptionBar->GetHeight()-BorderWidth, BorderWidth);
		else
			Canvas->DrawRect(0, 0, GetWidth()-BorderWidth, GetHeight()-BorderWidth, BorderWidth);
	}
}

//-------------------------------------------------------------------
//  OnPaint()
//  21-July-2002   rzv   created
//-------------------------------------------------------------------
void TForm::OnPaint(void) 
{
	Canvas->Brush->SetColor(GetColor());

	// Fill body
	if(GetCaptionBar() != NULL)
		Canvas->FillRect(0, GetCaptionBar()->GetHeight(), GetWidth(), GetHeight() - GetCaptionBar()->GetHeight());	
	else
		Canvas->FillRect(0, 0, GetWidth(), GetHeight());

	TWinControl::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  23-March-2004   rzv    created
//-------------------------------------------------------------------
void TForm::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TWinControl::OnMouseDown(Button, Shift, X, Y);

	BringToFront();	
}

//-------------------------------------------------------------------
//  OnClose()
//  29-July-2002   rzv   created
//-------------------------------------------------------------------
void TForm::OnClose(void)
{
}

//-------------------------------------------------------------------
//  OnShow()
//  22-Apr-2003   rzv   created
//-------------------------------------------------------------------
void TForm::OnShow(void)
{	
}

//-------------------------------------------------------------------
//  OnHide()
//  22-Apr-2003   rzv   created
//-------------------------------------------------------------------
void TForm::OnHide(void)
{
	TControlsList* ScreenControlsList = Screen->GetControls();
	if(ScreenControlsList != NULL)
	{
		TControlsList::reverse_iterator iter;
		for(iter = ScreenControlsList->rbegin(); 
		    iter != ScreenControlsList->rend(); 
			iter++)
		{
			TWinControl* Control = (TWinControl*)(*iter);
			if(Control->GetVisible())
			{
				Control->CMActivate();
				return;
			}
		}
	}
}

//-------------------------------------------------------------------
//  OnSize()
//  23-March-2004   rzv    created
//-------------------------------------------------------------------
void TForm::OnSize(int AWidth, int AHeight)
{
	TWinControl::OnSize(AWidth, AHeight);
	
	if(GetHeight() < MinHeight)
		SetHeight(MinHeight);

	if(GetWidth() < MinWidth)
		SetWidth(MinWidth);	
}

//-------------------------------------------------------------------
//  ParseSkin()
//  05-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TForm::ParseSkin(TiXmlElement* XmlElement)
{
	TWinControl::ParseSkin(XmlElement);
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


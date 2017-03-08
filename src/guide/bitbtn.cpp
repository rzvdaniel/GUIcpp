#define N_IMPLEMENTS TBitBtn
//-------------------------------------------------------------------
//  bitbtn.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/bitbtn.h"
#include "guide/skin.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TBitBtn()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
TBitBtn::TBitBtn()
{		
	Layout = blGlyphLeft;
	Margin = -1;
	Spacing = 4;
	CurrentGlyph = NULL;
	CaptionWidth = 0;
	CaptionHeight = 0;
	GlyphX = 0;
	GlyphY = 0;

	for(int i=0; i<5; i++)
		Glyph[i] = NULL;
}

//-------------------------------------------------------------------
//  ~TBitBtn()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
TBitBtn::~TBitBtn()
{
	for(int i=0;i<5;i++)
	{
		if(Glyph[i] != NULL)
			delete Glyph[i];
	}
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TBitBtn::Create(TComponent* AOwner, TRect Rect)
{
	TCustomButton::Create(AOwner, Rect);

	ApplySkin(Skin->BitBtn);
	
	SetCurrentGrid(GetGrid("Active"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TBitBtn::Assign(TObject* Object)
{
	TCustomButton::Assign(Object);
}

//-------------------------------------------------------------------
void TBitBtn::ApplySkin(TObject* Object)
{
	TCustomButton::ApplySkin(Object);

	TBitBtn* BitBtn = (TBitBtn*)Object;
	if(BitBtn != NULL)
	{
		SetSpacing(BitBtn->GetSpacing());
	}
}

//-------------------------------------------------------------------
/**
	@brief Specifies layout of the button, i.e. where the glyphs will be
    place relative to the caption.
    
	Possible values include: blGlyphCenter, blGlyphLeft (default), blGlyphRight, 
    blGlyphTop, blGlyphBottom.
	
	@param Value Value of the new button layout.
*/
//-------------------------------------------------------------------
void TBitBtn::SetLayout(TButtonLayout Value)
{
	if(Layout != Value)
	{
		Layout = Value;
		UpdateLayout();
	}
}
	
//-------------------------------------------------------------------
/**
   @brief Specifies the number of pixels between the edge of the glyph and
   the caption of the button. 
*/
//-------------------------------------------------------------------
void TBitBtn::SetSpacing(int Value)
{
	if(Spacing != Value)
	{
		Spacing = Value;
		UpdateLayout();
	}
}

//-------------------------------------------------------------------
/**
   @brief Specifies the number of pixels from the edge of the image specified
   by Glyph property and the border of the button.
   
   The margin is the space between the border of the buton and the glyph. 
   Depending of the button layout, it could represent top, bottom, right of left
   margin.
*/
//-------------------------------------------------------------------
void TBitBtn::SetMargin(int Value)
{
	if(Margin != Value)
	{
		Margin = Value;
		UpdateLayout();
	}
}

//-------------------------------------------------------------------
/**
   @brief Load the image that will be used to render the glyphs of the button.
   
   There could be up to five glyphs that could be used to represents different
   state of the bitmapped button. The loaded image should contain equal in size,
   horizontal aligned glyphs. Their order is the following: bUp, bDown, 
   bMouseOver, bInactive, bDisabled. If any of the glyphs are missing, first
   glyph from the image will be used to simulate the specific state of the 
   control.
   
   @param Filename The path to the image that will be used to render the glyphs 
   of the button.
   @param NumGlyphs Number of glyphs that the loaded image is containing. The
   default value is 1.
*/
//-------------------------------------------------------------------
void TBitBtn::LoadPicture(const char* Filename, int NumGlyphs)
{
	TTexture* Image = new TTexture;
	if(!Image->LoadNoUpload(Filename))
	{
		delete Image;
		return;
	}

	SetPicture(Image->GetPicture(), NumGlyphs);
	delete Image;
}

//-------------------------------------------------------------------
//  LoadPicture()
//  03-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TBitBtn::LoadPicture(const TString& Filename, int NumGlyphs)
{
	LoadPicture(Filename.c_str(), NumGlyphs);
}

//-------------------------------------------------------------------
//  SetPicture()
//  14-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TBitBtn::SetPicture(TPicture* Picture, int NumGlyphs)
{
	if(!Picture)
	{
		t_printf("Picture is not a valid one. Can not attach it to the button.\n");
		return;
	}

	if(!Picture->GetData())
	{
		t_printf("Picture data is not valid. Can not attach this picture to the button.\n");
		return;
	}

	// You can provide up to five glyphs on a bitmap button 
	// with a single image. The application then displays one of 
	// these glyphs depending on the state of the button.
	
	// Store the picture info for later use
	unsigned char* ImageData = Picture->GetData(); 
	unsigned int ImageWidth = Picture->GetWidth();
	unsigned int ImageHeight = Picture->GetHeight();
	unsigned int BitDepth = Picture->GetBitdepth();
	unsigned int Chanels = BitDepth / 8;


	// The width and height of one glyph
	unsigned int GlyphWidth = ImageWidth / NumGlyphs;
	unsigned int GlyphHeight = ImageHeight;

	// For every glyph
	for(int n=0; n<NumGlyphs; n++)
	{
		// Alloc memory to store the glyph's data
		unsigned char* GlyphData = new unsigned char[GlyphWidth * GlyphHeight * Chanels];

		// Your picture should looks like in the scheme below. 
		// At least first glyph is required.
		// |----------------------------------------------------------------------------------|
		// |			  |				 |			        |                |                |
		// |  First glyph | Second glyph |    Third glyph   |   Fourth glyph |   Fifth glyph  |
		// |  (bUp)       |	   (bDown)   |    (bMouseOver)  |   (bInactive)  |   (bDisabled)  |
		// |			  |				 |			        |                |                |
		// |----------------------------------------------------------------------------------|

		// Use the picture's data to set the glyph's data
		for(unsigned int i=0; i<ImageHeight; i++)
		{
			for(unsigned int j=0; j<GlyphWidth * Chanels; j++)
			{
				GlyphData[i * GlyphWidth * Chanels + j] = 
					ImageData[i * ImageWidth * Chanels + n * GlyphWidth * Chanels + j];
			}
		}

		// Create the glyph
		TPicture* NewGlyph = new TPicture;
		NewGlyph->MakePicture(GlyphWidth, GlyphHeight, BitDepth, GlyphData);
		
		// Init the texture based on the glyph
		if(Glyph[n] != NULL) 
		{
			delete Glyph[n];
			Glyph[n] = NULL;
		}


		Glyph[n] = new TTexture;
		Glyph[n]->Load(NewGlyph);	

		// Set the current texture
		if(n == 0)
			CurrentGlyph = Glyph[0];
	
		delete NewGlyph;
		delete[] GlyphData;		
	}

	// Update the layout
	UpdateLayout();
}

//-------------------------------------------------------------------
//  OnPaint()
//  20-Sep-2002   rzv   created
//-------------------------------------------------------------------
void TBitBtn::OnPaint(void)
{
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas); 
	
	// Glyph
	if(CurrentGlyph != NULL)
	{
		Canvas->Brush->SetTexture(CurrentGlyph);
		Canvas->FillRect(GlyphX , GlyphY, 
			CurrentGlyph->GetPicture()->GetWidth(), 
			CurrentGlyph->GetPicture()->GetHeight());
	}

	// Set the pen color		
	Canvas->Pen->SetColor(GetCaptionColor());
	// Paint the caption
	Canvas->Text(CaptionX, CaptionY, GetCaption());	

	TCustomButton::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TBitBtn::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{     
	TCustomButton::OnMouseDown(Button, Shift, X, Y);
   	
    if(Glyph[1] != NULL)
        CurrentGlyph = Glyph[1];
		
    GlyphX += GetCaptionOffset();
    GlyphY += GetCaptionOffset();
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TBitBtn::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{    
	TCustomButton::OnMouseUp(Button, Shift, X, Y);
	    
    if(Glyph[0] != NULL)
        CurrentGlyph = Glyph[0];	        
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TBitBtn::OnMouseMove(const TShiftState& Shift, int X, int Y)
{	
	TCustomButton::OnMouseMove(Shift, X, Y);

	if(!GetCaptured())
	{
		if(Glyph[2] != NULL)
			CurrentGlyph = Glyph[2];
	}
}

//-------------------------------------------------------------------
//  OnCaptureChanged()
//  29-July-2002   rzv    created
//-------------------------------------------------------------------
void TBitBtn::OnCaptureChanged(void)
{    
	if(GetState() == bDown)
	{
		GlyphX -= GetCaptionOffset();
		GlyphY -= GetCaptionOffset();   
	}

	TCustomButton::OnCaptureChanged();
   	
    if(Glyph[0] != NULL)
        CurrentGlyph = Glyph[0];  
}

//-------------------------------------------------------------------
//  OnTextChanged()
//  22-May-2004   rzv    created
//-------------------------------------------------------------------
void TBitBtn::OnTextChanged(void)
{
	TCustomButton::OnTextChanged();

	UpdateLayout();
}

//-------------------------------------------------------------------
//  OnSize()
//  22-May-2004   rzv    created
//-------------------------------------------------------------------
void TBitBtn::OnSize(int AWidth, int AHeight)
{
	TCustomButton::OnSize(AWidth, AHeight);

	UpdateLayout();
}

//-------------------------------------------------------------------
//  UpdateLayout()
//  26-Apr-2004   rzv   created
//-------------------------------------------------------------------
void TBitBtn::UpdateLayout(void)
{	
	float TotalWidth;
	float TotalHeight;
	int TextureWidth = 0;
	int TextureHeight = 0;

	if(CurrentGlyph != NULL)
	{
		TextureWidth = CurrentGlyph->GetPicture()->GetWidth();
		TextureHeight = CurrentGlyph->GetPicture()->GetHeight();
	}

	switch(Layout)
	{
		case blGlyphCenter:
		{					
			CaptionX = (GetWidth() - CaptionWidth)/2;
			CaptionY = (GetHeight() - CaptionHeight)/2;

			if(CurrentGlyph != NULL)
			{
				GlyphX = (GetWidth() - TextureWidth)/2;
				GlyphY = (GetHeight() - TextureHeight)/2;
			}
		}
		break;
		case blGlyphLeft:
		{
			TotalWidth = CaptionWidth + TextureWidth + Spacing;
			
			GlyphX = (GetWidth() - TotalWidth)/2;
			GlyphY = (GetHeight() - TextureHeight)/2;
			
			CaptionX = GlyphX + TextureWidth + Spacing;
			CaptionY = (GetHeight() - CaptionHeight)/2;
		}
		break;
		case blGlyphRight:
		{
			TotalWidth = CaptionWidth + TextureWidth + Spacing;
			
			CaptionX = (GetWidth() - TotalWidth)/2;
			CaptionY = (GetHeight() - CaptionHeight)/2;

			GlyphX = CaptionX + CaptionWidth + Spacing;
			GlyphY = (GetHeight() - TextureHeight)/2;
		}
		break;
		case blGlyphTop:
		{
			TotalHeight = CaptionHeight + TextureHeight + Spacing;
			
			GlyphX = (GetWidth() - TextureWidth)/2;
			GlyphY = (GetHeight() - TotalHeight)/2;
			
			CaptionX = (GetWidth() - CaptionWidth)/2;
			CaptionY = GlyphY + TextureHeight + Spacing;
		}
		break;
		case blGlyphBottom:
		{
			TotalHeight = CaptionHeight + TextureHeight + Spacing;
			
			CaptionX = (GetWidth() - CaptionWidth)/2;
			CaptionY = (GetHeight() - TotalHeight)/2;

			GlyphX = (GetWidth() - TextureWidth)/2;
			GlyphY = CaptionY + CaptionHeight + Spacing;;
		}
		break;
	}
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TBitBtn::ParseSkin(TiXmlElement* XmlElement)
{
	TCustomButton::ParseSkin(XmlElement);

	const char *value = NULL;

	// Set spacing between glyph and text
	value = XmlElement->Attribute("GlyphSpacing");
	if(value != NULL)
	{
		sscanf(value, "%d", &Spacing);
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



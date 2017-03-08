#define N_IMPLEMENTS TGridCell
//-------------------------------------------------------------------
//  gridcell.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/gridrow.h"
#include "guide/gridcell.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/canvas.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TGridCell()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
TGridCell::TGridCell(TGridRow* ARow) 
{
	Row = ARow;
	Align = calNone;
	TextureRepeat = trNone;
	Texture = NULL;
	TextureU = 1.0f;
	TextureV = 1.0f;
	Left = 0;
	Top = 0;
	Width = 0;
	Height = 0;
}

//-------------------------------------------------------------------
//  ~TGridCell()
//  12-May-2004   rzv   created
//-------------------------------------------------------------------
TGridCell::~TGridCell()
{
}

//-------------------------------------------------------------------
//  SetAlign()
//  19-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridCell::SetAlign(TAlignCell Value)
{
	if(Value != Align)
	{
		Align = Value;
		Row->RealignCells();
	}
}

//-------------------------------------------------------------------
//  SetBounds()
//  21-July-2002   rzv   created
//-------------------------------------------------------------------
void TGridCell::SetBounds(int ALeft, int ATop, int AWidth, int AHeight)
{
	if((AWidth != Width) || (AHeight != Height)) 
	{		
		Width = AWidth;
		Height = AHeight;

		if(Texture != NULL)
		{
			switch(TextureRepeat)
			{
				case trNone:
					TextureU = 1.0f;
					TextureV = 1.0f;
					break;
				case trAll:
					TextureU = (float)Width/(float)Texture->GetWidth();
					TextureV = (float)Height/(float)Texture->GetHeight();
					break;
				case trHorizontal:
					TextureU = (float)Width/(float)Texture->GetWidth();
					TextureV = 1.0f;
					break;
				case trVertical:
					TextureU = 1.0f;
					TextureV = (float)Height/(float)Texture->GetHeight();
					break;
			}
		}
	}
	
	if((ALeft != Left) || (ATop != Top))
	{
		Left = ALeft;
		Top	= ATop;		
	}
}

//-------------------------------------------------------------------
//  SetLeft()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TGridCell::SetLeft(int Value) 
{ 
	SetBounds(Value, Top, Width, Height);
}

//-------------------------------------------------------------------
//  SetTop()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TGridCell::SetTop(int Value) 
{ 
	SetBounds(Left, Value, Width, Height);
}

//-------------------------------------------------------------------
//  SetWidth()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TGridCell::SetWidth(int Value) 
{ 
	SetBounds(Left, Top, Value, Height);
}

//-------------------------------------------------------------------
//  SetHeight()
//  06-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TGridCell::SetHeight(int Value) 
{ 
	SetBounds(Left, Top, Width, Value);
}

//-------------------------------------------------------------------
//  Paint()
//  17-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridCell::Paint(TCanvas* Canvas) 
{
	Canvas->FillTexturedRect(Texture, Canvas->GetControl()->GetColor(), 
		Row->GetLeft() + Left, Row->GetTop() + Top, Width, Height,
		TextureU, TextureV);

	// Debug only
	//Canvas->Pen->SetColor(clBlue);
	//Canvas->DrawRect(Row->GetLeft() + Left, Row->GetTop() + Top, Width, Height, 1);
}

//-------------------------------------------------------------------
//  Assign()
//  20-May-2004   rzv   created
//-------------------------------------------------------------------
void TGridCell::Assign(TObject* Object)
{
	TGridCell* Cell = (TGridCell*)Object;

	SetLeft(Cell->GetLeft());
	SetTop(Cell->GetTop());
	SetWidth(Cell->GetWidth());
	SetHeight(Cell->GetHeight());
	SetAlign(Cell->GetAlign());
	SetTexture(Cell->GetTexture());
	SetTextureRepeat(Cell->GetTextureRepeat());
}

//-------------------------------------------------------------------
void TGridCell::ApplySkin(TObject* Object)
{
	TGridCell* Cell = (TGridCell*)Object;

	SetLeft(Cell->GetLeft());
	SetTop(Cell->GetTop());
	SetWidth(Cell->GetWidth());
	SetHeight(Cell->GetHeight());
	SetAlign(Cell->GetAlign());
	SetTexture(Cell->GetTexture());
	SetTextureRepeat(Cell->GetTextureRepeat());
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TGridCell::ParseSkin(TiXmlElement* XmlElement)
{
	TSkin* Skin = TScreen::Singleton->GetSkin();
	
	const char *value = NULL;

	// Read the Width attribute
	value = XmlElement->Attribute("Width");
	if(value != NULL)
	{
		sscanf(value, "%d", &Width);
		value = NULL;
	}

	// Read the Rect attribute
	value = XmlElement->Attribute("Rect");
	if(value != NULL)
	{
		sscanf(value, "%d,%d,%d,%d", &Left, &Top, &Width, &Height);
		value = NULL;
	}

	// Read the Align attribute
	value = XmlElement->Attribute("Align");
	if(value != NULL)
	{
		if(!strcmp(value, "left"))
			Align = calLeft;
		else if(!strcmp(value, "right"))
			Align = calRight;
		else if(!strcmp(value, "client"))
			Align = calClient;
	
		value = NULL;
	}

	// Read the Texture attribute
	value = XmlElement->Attribute("Texture");
	if(value != NULL)
	{
		// Set the texture for this cell
		Texture = Skin->GetTexture(value);	
		//t_printf("TGridCell::Texture %s\n", value);
		value = NULL;
	}

	// Read the TextureRepeat attribute
	value = XmlElement->Attribute("TextureRepeat");
	if(value != NULL)
	{
		if(!strcmp(value, "horizontal"))
			TextureRepeat = trHorizontal;
		else if(!strcmp(value, "vertical"))
			TextureRepeat = trVertical;
		else if(!strcmp(value, "all"))
			TextureRepeat = trAll;
		else if(!strcmp(value, "none"))
			TextureRepeat = trNone;

		value = NULL;
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


#define N_IMPLEMENTS TShadow
//-------------------------------------------------------------------
//  shadow.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "guide/shadow.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/control.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TShadow()
//  09-Dec-2003   rzv   created
//-------------------------------------------------------------------
TShadow::TShadow(TSkin* Skin)
{  
	TextureLeft[0] = Skin->GetTexture(TString("shadow_left") + "0");
	TextureLeft[1] = Skin->GetTexture(TString("shadow_left") + "1");
	TextureLeft[2] = Skin->GetTexture(TString("shadow_left") + "2");

	TextureTop[0] = Skin->GetTexture(TString("shadow_top") + "0");
	TextureTop[1] = Skin->GetTexture(TString("shadow_top") + "1");
	TextureTop[2] = Skin->GetTexture(TString("shadow_top") + "2");

	TextureRight[0] = Skin->GetTexture(TString("shadow_right") + "0");
	TextureRight[1] = Skin->GetTexture(TString("shadow_right") + "1");
	TextureRight[2] = Skin->GetTexture(TString("shadow_right") + "2");

	TextureBottom[0] = Skin->GetTexture(TString("shadow_bottom") + "0");
	TextureBottom[1] = Skin->GetTexture(TString("shadow_bottom") + "1");
	TextureBottom[2] = Skin->GetTexture(TString("shadow_bottom") + "2");
}

//-------------------------------------------------------------------
//  ~TShadow()
//  09-Dec-2003   rzv   created
//-------------------------------------------------------------------
TShadow::~TShadow()
{
}

//-------------------------------------------------------------------
//  OnPaint()
//  09-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TShadow::Render(TControl* Control) 
{
	if(Control != NULL)
	{

	TControl* CtrlParent = (TControl*)Control->GetParent();
	if(CtrlParent != NULL)
		CtrlParent->Canvas->ClipDrawing();

	TRect Rect = Control->GetControlRect();

    // Bottom
    Control->Screen->Canvas->FillTexturedRect(TextureBottom[0], 0xAAFFFFFF, 
		Rect.left - 16, 
		Rect.top + Control->GetHeight(), 
		32, 16);
    Control->Screen->Canvas->FillTexturedRect(TextureBottom[1], 0xAAFFFFFF, 
		Rect.left + 16, 
		Rect.top + Control->GetHeight(), 
		Control->GetWidth() - 32, 16);
    Control->Screen->Canvas->FillTexturedRect(TextureBottom[2], 0xAAFFFFFF, 
		Rect.left + Control->GetWidth() - 16, 
		Rect.top + Control->GetHeight(), 
		32, 16);
   
    // Top
    Control->Screen->Canvas->FillTexturedRect(TextureTop[0], 0xAAFFFFFF, 
		Rect.left - 16, 
		Rect.top - 16, 
		32, 16);
    Control->Screen->Canvas->FillTexturedRect(TextureTop[1], 0xAAFFFFFF, 
		Rect.left + 16, 
		Rect.top - 16, 
		Control->GetWidth() - 32, 16);
    Control->Screen->Canvas->FillTexturedRect(TextureTop[2], 0xAAFFFFFF, 
		Rect.left + Control->GetWidth() - 16, 
		Rect.top - 16, 
		32, 16);
    
    // Left
    Control->Screen->Canvas->FillTexturedRect(TextureLeft[0], 0xAAFFFFFF, 
		Rect.left - 16, 
		Rect.top + Control->GetHeight() - 16, 
		16, 16);
    Control->Screen->Canvas->FillTexturedRect(TextureLeft[1], 0xAAFFFFFF, 
		Rect.left - 16, 
		Rect.top + 16, 
		16, Control->GetHeight() - 32);
    Control->Screen->Canvas->FillTexturedRect(TextureLeft[2], 0xAAFFFFFF, 
		Rect.left - 16, 
		Rect.top + 0, 
		16, 16);
    
    // Right
    Control->Screen->Canvas->FillTexturedRect(TextureRight[0], 0xAAFFFFFF, 
		Rect.left + Control->GetWidth(), 
		Rect.top + Control->GetHeight() - 16, 
		16, 16);
    Control->Screen->Canvas->FillTexturedRect(TextureRight[1], 0xAAFFFFFF, 
		Rect.left + Control->GetWidth(), 
		Rect.top + 16, 
		16, Control->GetHeight() - 32);
    Control->Screen->Canvas->FillTexturedRect(TextureRight[2], 0xAAFFFFFF, 
		Rect.left + Control->GetWidth(), 
		Rect.top + 0, 
		16, 16);
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



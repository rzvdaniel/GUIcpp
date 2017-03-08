#define N_IMPLEMENTS TCanvas
//-------------------------------------------------------------------
//  canvas.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/canvas.h"
#include "guide/osincludes.h"
#include "guide/control.h"
#include "guide/screen.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TCanvas()
//  16-July-2002   rzv   created
//-------------------------------------------------------------------
TCanvas::TCanvas(TControl* AControl) 
{	
	t_assert(AControl != NULL);
	Control = AControl;

	Pen   = new TPen;	
	Brush = new TBrush;	

	TextAntialias = 0;
}

//-------------------------------------------------------------------
//  ~TCanvas()
//  16-July-2002   rzv   created
//-------------------------------------------------------------------
TCanvas::~TCanvas() 
{	
	if(Brush)
		delete Brush;
	if(Pen)
		delete Pen;
}
//-------------------------------------------------------------------
/**
	Finds out whether an extension is supported by the currently
	active OpenGL driver. Note that a rendering context must be
	valid for this to be accurate.
	This function was adapted from the one provided in the red book
	(OpenGL Programming Guide, version 1.1 by Woo, Neider and Davis).
*/
//-------------------------------------------------------------------
bool TCanvas::QueryExtension(char* Extension) const 
{
	// What we need:
	// GL_EXT_texture_rectangle || GL_NV_texture_rectangle
 
	char* p = (char*)glGetString(GL_EXTENSIONS);
	t_printf("%s\n", p);
	size_t ExtensionLen = strlen(Extension);
	char*  end = p + strlen(p);
	
	while(p < end) 
	{
		size_t n = strcspn(p, " ");
		if((ExtensionLen == n) && (strncmp(Extension, p, n) == 0)) 
		{
			return true;
		}
		
		p += (n + 1);
	}
	
	return false;
}

//-------------------------------------------------------------------
//  GetTextWidth()
//  27-July-2003   rzv   created
//-------------------------------------------------------------------
float TCanvas::GetTextWidth(const TString& String)
{
	return GetTextWidth(String.c_str());
}

//-------------------------------------------------------------------
//  GetTextWidth()
//  27-July-2003   rzv   created
//-------------------------------------------------------------------
float TCanvas::GetTextWidth(const char* String)
{
	t_assert(Control->GetFont());

	return Control->GetFont()->GetTextWidth(String);
}

//-------------------------------------------------------------------
//  GetTextHeight()
//  27-July-2003   rzv   created
//-------------------------------------------------------------------
float TCanvas::GetTextHeight(const TString& String)
{
	return GetTextHeight(String.c_str());
}

//-------------------------------------------------------------------
//  GetTextHeight()
//  27-July-2003   rzv   created
//-------------------------------------------------------------------
float TCanvas::GetTextHeight(const char* String)
{
	t_assert(Control->GetFont());

	return Control->GetFont()->GetTextHeight();
}


//-------------------------------------------------------------------
//  ClipDrawing()
//  28-March-2003  rzv   created
//-------------------------------------------------------------------
void TCanvas::ClipDrawing(const TRect& Rect)
{
	glScissor(Rect.left, TScreen::Singleton->GetGfxServer()->Height - Rect.top - Rect.bottom, Rect.right, Rect.bottom);
	
	double eqn0[4] = { -1.0, 0.0, 0.0,  Rect.right };
	double eqn1[4] = {  1.0, 0.0, 0.0, -Rect.left };
	double eqn2[4] = {  0.0,-1.0, 0.0,  Rect.bottom };
	double eqn3[4] = {  0.0, 1.0, 0.0, -Rect.top };

	glClipPlane(GL_CLIP_PLANE0, eqn0);
	glClipPlane(GL_CLIP_PLANE1, eqn1);
	glClipPlane(GL_CLIP_PLANE2, eqn2);
	glClipPlane(GL_CLIP_PLANE3, eqn3);
}

//-------------------------------------------------------------------
//  ClipDrawing()
//  15-March-2004  rzv   created
//-------------------------------------------------------------------
void TCanvas::ClipDrawing(void)
{
	TRect Rect = Control->GetClipRect();
	
	glScissor(Rect.left, TScreen::Singleton->GetGfxServer()->Height - Rect.top - Control->GetHeight(), Rect.right, Rect.bottom);
	
	double eqn0[4] = { -1.0, 0.0, 0.0,  Rect.right };
	double eqn1[4] = {  1.0, 0.0, 0.0, -Rect.left };
	double eqn2[4] = {  0.0,-1.0, 0.0,  Rect.bottom };
	double eqn3[4] = {  0.0, 1.0, 0.0, -Rect.top };

	glClipPlane(GL_CLIP_PLANE0, eqn0);
	glClipPlane(GL_CLIP_PLANE1, eqn1);
	glClipPlane(GL_CLIP_PLANE2, eqn2);
	glClipPlane(GL_CLIP_PLANE3, eqn3);
}

//-------------------------------------------------------------------
//  DisableClipping()
//  09-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TCanvas::DisableClipping(void)
{
	glDisable(GL_SCISSOR_TEST);

    glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_CLIP_PLANE2);
	glDisable(GL_CLIP_PLANE3);
}

//-------------------------------------------------------------------
//  EnableClipping()
//  09-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TCanvas::EnableClipping(void)
{
	glEnable(GL_SCISSOR_TEST);

	glEnable(GL_CLIP_PLANE0);
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE2);
	glEnable(GL_CLIP_PLANE3); 
}

//-------------------------------------------------------------------
//  BeginUserScene()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TCanvas::BeginUserScene(void)
{	
	TRect ControlRect = Control->GetControlRect();

    glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_CLIP_PLANE2);
	glDisable(GL_CLIP_PLANE3);
    
	glViewport( 
		ControlRect.left, 
		Control->Screen->GetHeight() - ControlRect.top - Control->GetHeight(),
		Control->GetWidth(), 
		Control->GetHeight()
		);
}

//-------------------------------------------------------------------
//  EndUserScene()
//  08-Feb-2004   rzv   created
//-------------------------------------------------------------------
void TCanvas::EndUserScene(void)
{
    // "An optimum compromise that allows all primitives to be 
	// specified at integer positions, while still ensuring 
	// predictable rasterization, is to translate x and y by 0.375, 
	// as shown in the following code fragment. Such a translation 
	// keeps polygon and pixel image edges safely away from the 
	// centers of pixels, while moving line vertices's close enough 
	// to the pixel centers." - Red Book
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
    
	glEnable(GL_CLIP_PLANE0);
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE2);
	glEnable(GL_CLIP_PLANE3); 

	glViewport(0, 0, Control->Screen->GetWidth(), Control->Screen->GetHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Control->Screen->GetWidth(), Control->Screen->GetHeight(), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.375f, 0.375f, 0.0);
}

//-------------------------------------------------------------------
//  MoveTo()
//  19-July-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::MoveTo(int X, int Y)
{
	SetPenPos(TPoint(X, Y));
}

//-------------------------------------------------------------------
//  LineTo()
//  19-July-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::LineTo(int X, int Y)
{	 
	Control->PushClipRect();

	TRect Rect = Control->GetControlRect();
	TColor Color = Pen->GetColor();
	
	// Transparency?
	if(GetAlpha(Color) > 0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	// Disable texturing
	glDisable(GL_TEXTURE_2D);		

	// Set the drawing color
	glColor4ub(GetRed(Color), GetGreen(Color), GetBlue(Color), GetAlpha(Color));
	
	bool LineStipple = true;

	switch(Pen->GetStyle())
	{
		case psSolid:
			LineStipple = false;
			break;
		case psDash:
			glLineStipple(1, 0x0F0F);
			break;
		case psDot:
			glLineStipple(1, 0x1111);
			break;
		case psDashDot:
			glLineStipple(1, 0xFC30);
			break;
		case psDashDotDash:
			glLineStipple(1, 0xF33C);
			break;
		case psDashDotDot:
			glLineStipple(1, 0xF888);
			break;
	}

	if(LineStipple == true)
		glEnable(GL_LINE_STIPPLE);

	glLineWidth(Pen->GetWidth());

	glBegin(GL_LINES);
	glVertex2i(Rect.left + GetPenPos().x, 
			   Rect.top + GetPenPos().y);
	glVertex2i(Rect.left + X, 
			   Rect.top + Y);
	glEnd();

	if(LineStipple == true)
		glDisable(GL_LINE_STIPPLE);	
 
    MoveTo(X, Y);

	Control->PopClipRect();
}

//-------------------------------------------------------------------
//  Draw3DRect()
//  19-July-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::Draw3DRect(int X, int Y, int CX, int CY, int Width,
		TColor ClrTopLeft, TColor ClrBottomRight)
{
	Control->PushClipRect();

	for(int i=0; i<Width; i++)
	{
		MoveTo(X + CX - i, Y + i);
	
		Pen->SetColor(ClrTopLeft);
		LineTo(X + i, Y + i);			// top 
		LineTo(X + i, Y + CY - i);		// left
		
		Pen->SetColor(ClrBottomRight);
		LineTo(X + CX - i, Y + CY - i); // bottom 
		LineTo(X + CX - i, Y + i);      // right 
	}

	Control->PopClipRect();
}

//-------------------------------------------------------------------
//  Draw3DRect()
//  19-July-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::Draw3DRect(const TRect &Rect, int Width, TColor ClrTopLeft, 
		TColor ClrBottomRight)
{
	Draw3DRect(Rect.left, Rect.top, Rect.right, Rect.bottom, Width,
		ClrTopLeft, ClrBottomRight); 
}


//-------------------------------------------------------------------
//  DrawRect()
//  04-Aug-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::DrawRect(int X, int Y, int CX, int CY, int Width)
{
	Control->PushClipRect();

	for(int i=0; i<Width; i++)
	{
		MoveTo(X + CX - i, Y + i);
		LineTo(X + i, Y + i);			// top 
		LineTo(X + i, Y + CY - i);		// left	
		LineTo(X + CX - i, Y + CY - i); // bottom 
		LineTo(X + CX - i, Y + i);      // right 
	}

	Control->PopClipRect();
}

//-------------------------------------------------------------------
//  DrawRect()
//  04-Aug-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::DrawRect(const TRect &Rect, int Width)
{
	DrawRect(Rect.left, Rect.top, Rect.right, Rect.bottom, Width);	
}

//-------------------------------------------------------------------
//  FillRect()
//  20-July-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::FillRect(int X, int Y, int CX, int CY)
{
	Control->PushClipRect();

    TRect Rect = Control->GetControlRect();
	TColor Color = Brush->GetColor();
	
	// Transparency?
	if(GetAlpha(Color) > 0) 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	// Set the drawing color
	glColor4ub(GetRed(Color), GetGreen(Color), GetBlue(Color), GetAlpha(Color));
	
	// If our brush has any texture
	if(Brush->GetTexture() != NULL)
	{
		glEnable(GL_TEXTURE_2D);		
		glBindTexture(GL_TEXTURE_2D, Brush->GetTexture()->GetTexId());
		
		glBegin(GL_QUADS); 
		glTexCoord2f(Brush->GetTextureOffsetU(), Brush->GetTextureV());
		glVertex2i(Rect.left + X, Rect.top + Y); 
		glTexCoord2f(Brush->GetTextureU(), Brush->GetTextureV());
		glVertex2i(Rect.left + X + CX, Rect.top + Y); 
		glTexCoord2f(Brush->GetTextureU(), Brush->GetTextureOffsetV());
		glVertex2i(Rect.left + X + CX, Rect.top + Y + CY); 
		glTexCoord2f(Brush->GetTextureOffsetU(), Brush->GetTextureOffsetV());
		glVertex2i(Rect.left + X, Rect.top + Y + CY); 
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	else 
	{
		// We don't care about any texture or texture coordinates
		glBegin(GL_QUADS); 
		glVertex2i(Rect.left + X, Rect.top + Y); 
		glVertex2i(Rect.left + X + CX, Rect.top + Y); 
		glVertex2i(Rect.left + X + CX, Rect.top + Y + CY); 
		glVertex2i(Rect.left + X, Rect.top + Y + CY); 
		glEnd(); 
	}

	Control->PopClipRect();
}

//-------------------------------------------------------------------
//  FillRect()
//  20-July-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::FillRect(const TRect &Rect)
{
	FillRect(Rect.left, Rect.top, Rect.right, Rect.bottom);	
}

//-------------------------------------------------------------------
//  FillTexturedRect()
//  10-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TCanvas::FillTexturedRect(TTexture* Texture, TColor Color, 
                               int X, int Y, int CX, int CY, 
                               float U, float V, 
                               float UOffset, float VOffset)
{
	Control->PushClipRect();

    TRect Rect = Control->GetControlRect();
	
	// Transparency?
	if(GetAlpha(Color) > 0) 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	// Set the drawing color
	glColor4ub(GetRed(Color), GetGreen(Color), GetBlue(Color), GetAlpha(Color));
	
	// If any texture
	if(Texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);		
		glBindTexture(GL_TEXTURE_2D, Texture->GetTexId());
	
		glBegin(GL_QUADS); 
		glTexCoord2f(UOffset, V);
		glVertex2i(Rect.left + X, Rect.top + Y); 
		glTexCoord2f(U, V);
		glVertex2i(Rect.left + X + CX, Rect.top + Y); 
		glTexCoord2f(U, VOffset);
		glVertex2i(Rect.left + X + CX, Rect.top + Y + CY); 
		glTexCoord2f(UOffset, VOffset);
		glVertex2i(Rect.left + X, Rect.top + Y + CY); 
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
	}
	else 
	{
		// We don't care about any texture or texture coordinates
		glBegin(GL_QUADS); 
		glVertex2i(Rect.left + X, Rect.top + Y); 
		glVertex2i(Rect.left + X + CX, Rect.top + Y); 
		glVertex2i(Rect.left + X + CX, Rect.top + Y + CY); 
		glVertex2i(Rect.left + X, Rect.top + Y + CY); 
		glEnd(); 
	}

	Control->PopClipRect();
}

//-------------------------------------------------------------------
//  FillTexturedRect()
//  10-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TCanvas::FillTexturedRect(TTexture* Texture, TColor Color, 
                               const TRect &Rect, float U, float V, 
                               float UOffset, float VOffset)
{
    FillTexturedRect(Texture, Color, Rect.left, Rect.top, Rect.right, Rect.bottom,
             U, V, UOffset, VOffset);	
}

//-------------------------------------------------------------------
//  Text()
//  20-July-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::Text(float X, float Y, const char* String)
{
	t_assert(Control->GetFont());
	
	Control->PushClipRect();

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	TColor Color = Pen->GetColor();
	glColor3ub(GetRed(Color), GetGreen(Color), GetBlue(Color));	
	
	MoveTo(X, Y);
	TRect Rect = Control->GetControlRect();

	glRasterPos2f( X + Rect.left, Y + Rect.top + Control->GetFont()->GetSize());
	Control->GetFont()->Text(X + Rect.left, Y + Rect.top, String);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	
	Control->PopClipRect();
}

//-------------------------------------------------------------------
//  Text()
//  20-July-2002   rzv   created
//-------------------------------------------------------------------
void TCanvas::Text(float X, float Y, const TString& String)
{
	Text(X, Y, String.c_str());
}

//-------------------------------------------------------------------
//  Text3D()
//  09-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCanvas::Text3D(float X, float Y, TColor ColorUp, TColor ColorDown, 
				TPoint Offset, const char* String)
{
	t_assert(Control->GetFont());

	Control->PushClipRect();

    glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, GetTextAntialias());
		
	TRect Rect = Control->GetControlRect();
		
	MoveTo(X, Y);
	glColor4ub(GetRed(ColorDown), GetGreen(ColorDown), GetBlue(ColorDown), GetAlpha(ColorDown));	
	Control->GetFont()->Text(X + Rect.left + Offset.x, Y + Rect.top + Offset.y, String);
	
	MoveTo(X, Y);
	glColor4ub(GetRed(ColorUp), GetGreen(ColorUp), GetBlue(ColorUp), GetAlpha(ColorUp));	
	Control->GetFont()->Text(X + Rect.left, Y + Rect.top, String);
		
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	Control->PopClipRect();
}

//-------------------------------------------------------------------
//  Text3D()
//  09-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TCanvas::Text3D(float X, float Y, TColor ColorUp, TColor ColorDown, 
				TPoint Offset, const TString& String)
{
	Text3D(X, Y, ColorUp, ColorDown, Offset, String.c_str());
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//  Panel1.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#ifdef WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Md2.h"
#include "Form1.h"
#include "Panel1.h"
#include "guide/vcl.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TPanel1()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
TPanel1::TPanel1()
{
	Form1 = NULL;
	MouseX = 0;
	MouseY = 0;
	eye[0] = 0;
	eye[1] = 0;
	eye[2] = 50;
	rot[0] = 0;
	rot[1] = -45;
	rot[2] = 0;
}

//-------------------------------------------------------------------
//  ~TPanel1()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
TPanel1::~TPanel1()
{
}

//-------------------------------------------------------------------
//  Create()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::Create(TComponent* AOwner, const TRect& Rect)
{	
	TPanel::Create(AOwner, Rect);

	Form1 = (TForm1*)AOwner;
}

//-------------------------------------------------------------------
//  OnPaint()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnPaint(void) 
{
	// Skip the panel's background painting, so just call TWinControl
	// paint function instead of TPanel one (as we should...)
	TPanel::OnPaint();

	// Begin the user scene. It is very important to render
	// your OpenGL scene between Canvas's method BeginScene()
	// and EndScene(). The application needs this to restore
	// some OpenGL states required for 2D rendering, states 
	// that could be alterred by your code. This is a must.
	Canvas->BeginUserScene();

	// User scene
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0, (float)(GetWidth())/(float)(GetHeight()), 1.0f, 1000.0 ); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (-eye[0], -eye[1], -eye[2]);
	glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rot[2], 0.0f, 0.0f, 1.0f);
								
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);		
	glCullFace(GL_FRONT);
	glEnable(GL_TEXTURE_2D);

	TMd2* Model = Form1->GetModel();
	if(Model != NULL)
		Model->Render();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	
	// End the user scene
	Canvas->EndUserScene();

	if(Model != NULL)
	{
		Canvas->Pen->SetColor(clBlack);
		Canvas->Text(10, GetHeight() - 20, "Animation:");
		Canvas->Pen->SetColor(clGray);
		Canvas->Text(90, GetHeight() - 20, Model->GetAnimationName(Model->GetAnimation()));
	}
	else
	{
		Canvas->Pen->SetColor(clGray);
		Canvas->Text((GetWidth() - Canvas->GetTextWidth("No model loaded yet..."))/2, GetHeight()/2, "No model loaded yet...");
	}

	// If the panel is the active control on it's parent form,
	// render a red rect aroud it's borders to tell the user
	// that his working panel can receive keyboard input.
	if(GetActive() == true)
		Canvas->Pen->SetColor(clRed);
	else
		Canvas->Pen->SetColor(clLtGray);

	Canvas->DrawRect(0, 0, GetWidth(), GetHeight(), 1);
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	// Capture the mouse movement even if outside of control
	if(!GetCaptured())
		SetCapture();

	MouseX = X;
	MouseY = Y;

	TPanel::OnMouseDown(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	if(GetCaptured())
		ReleaseCapture();

	MouseX = 0;
	MouseY = 0;

	TPanel::OnMouseUp(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnMouseMove(const TShiftState& Shift, int X, int Y)
{
	if(GetCaptured())
	{
		// If the SHIFT key is pressed, zoom it
		if(Shift.count(ssShift))
		{
			// Zoom
			eye[2] -= ((MouseY - Y) * 180.0f) / 200.0f;
		}
		else
		{
			// Rotate
			rot[0] -= ((MouseY - Y) * 180.0f) / 200.0f;
			rot[1] -= ((MouseX - X) * 180.0f) / 200.0f;
			Clamp(rot);
		}
	}

	MouseX = X;
	MouseY = Y;

	TPanel::OnMouseMove(Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnKeyDown()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnKeyDown(unsigned short &Key, const TShiftState& Shift)
{
	if(Key == T_KEY_UP)
		eye[1] -= 3.0f;	 // Translate up
	else if(Key == T_KEY_DOWN)
		eye[1] += 3.0f;  // Translate down
	else if(Key == T_KEY_LEFT)
		eye[0] += 2.0f;  // Translate left
	else if(Key == T_KEY_RIGHT)
		eye[0] -= 2.0f;  // Translate right

	TPanel::OnKeyDown(Key, Shift);
}

//-------------------------------------------------------------------
//  OnKeyUp()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnKeyUp(unsigned short &Key, const TShiftState& Shift)
{
	// This does nothing, but is here for you to see it exists.
	TPanel::OnKeyUp(Key, Shift);
}

//-------------------------------------------------------------------
//  Clamp()
//  Clamp rotation angles
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::Clamp(float v[3])
{    
    for(int i = 0; i < 3; i ++)
	{
        if(v[i] > 360 || v[i] < -360)
            v[i] = 0;
	}
}


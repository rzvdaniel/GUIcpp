//-------------------------------------------------------------------
//  Panel1.cpp
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#include "guide/vcl.h"
#include "guide/debug.h"
#include "Panel1.h"

//-------------------------------------------------------------------
//  TPanel1()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
TPanel1::TPanel1()
{
	MouseX = 0;
	MouseY = 0;
	eye[0] = 0;
	eye[1] = 0;
	eye[2] = 20;
	rot[0] = 0;
	rot[1] = -45;
	rot[2] = 0;
}

//-------------------------------------------------------------------
//  ~TPanel1()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
TPanel1::~TPanel1()
{
}

//-------------------------------------------------------------------
//  Create()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::Create(TComponent* AOwner, const TRect& Rect)
{	
	TPanel::Create(AOwner, Rect);
	
	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH); 
	gluQuadricTexture(quadric, GL_TRUE);
}

//-------------------------------------------------------------------
//  OnPaint()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnPaint(void) 
{
	// Call the base class function, first. 
	TPanel::OnPaint();

	// Begin the user scene. It is very important to render
	// your OpenGL scene between Canvas's method BeginUserScene()
	// and EndUserScene(). The application needs this to restore
	// some OpenGL states required for 2D rendering, states 
	// that could be alterred by your code. This is a must.
	Canvas->BeginUserScene();

	// User scene
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0, (float)(GetWidth())/(float)(GetHeight()), 0.1f, 500.0 ); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (-eye[0], -eye[1], -eye[2]);
	glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rot[2], 0.0f, 0.0f, 1.0f);
							
	glEnable(GL_LIGHTING);	
	glEnable(GL_LIGHT0);	
	glEnable(GL_DEPTH_TEST);

	// Just a simple cylinder
	gluCylinder(quadric, 4.0f, 4.0f, 4.0f, 16, 2);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);			
	
	// End the user scene
	Canvas->EndUserScene();

	// If the panel is the active control on it's parent form,
	// render a red rect around it's borders to tell the user
	// that his working panel can receive keyboard input.
	if(GetActive() == true)
		Canvas->Pen->SetColor(clRed);
	else
		Canvas->Pen->SetColor(clLtGray);

	Canvas->DrawRect(2, 2, GetWidth() - 4, GetHeight() - 4, 1);
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
    TPanel::OnMouseDown(Button, Shift, X, Y);
	
    // Capture the mouse movement even if outside of control
	if(!GetCaptured())
		SetCapture();

	MouseX = X;
	MouseY = Y;	
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
    TPanel::OnMouseUp(Button, Shift, X, Y);
    
	if(GetCaptured())
		ReleaseCapture();

	MouseX = 0;
	MouseY = 0;
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnMouseMove(const TShiftState& Shift, int X, int Y)
{
    TPanel::OnMouseMove(Shift, X, Y);
    
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
}

//-------------------------------------------------------------------
//  OnKeyDown()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnKeyDown(unsigned short &Key, const TShiftState& Shift)
{
    TPanel::OnKeyDown(Key, Shift);
    
	if(Key == T_KEY_UP)
		eye[1] -= 3.0f;	 // Translate up
	else if(Key == T_KEY_DOWN)
		eye[1] += 3.0f;  // Translate down
	else if(Key == T_KEY_LEFT)
		eye[0] += 2.0f;  // Translate left
	else if(Key == T_KEY_RIGHT)
		eye[0] -= 2.0f;  // Translate right
}

//-------------------------------------------------------------------
//  OnKeyUp()
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::OnKeyUp(unsigned short &Key, const TShiftState& Shift)
{
	// This does nothing, but is here for you to see it exists.
	TPanel::OnKeyUp(Key, Shift);
}

//-------------------------------------------------------------------
//  Clamp()
//  Clamp rotation angles
//  14-Aug-2004   rzv    created
//-------------------------------------------------------------------
void TPanel1::Clamp(float v[3])
{    
    for(int i = 0; i < 3; i ++)
	{
        if(v[i] > 360 || v[i] < -360)
            v[i] = 0;
	}
}


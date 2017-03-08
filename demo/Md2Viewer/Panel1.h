#ifndef T_PANEL1_H
#define T_PANEL1_H
//-------------------------------------------------------------------
//  CLASS
//  TPanel1
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_PANEL_H
#include "guide/panel.h"
#endif

class TForm1;
class TPanel1 : public TPanel
{
	TForm1* Form1;
	int MouseX;
	int MouseY;
	float eye[3];
	float rot[3];

public:  
    TPanel1();
    virtual ~TPanel1();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

protected:
	// Events	
	void OnPaint(void);
	void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	void OnKeyDown(unsigned short &Key, const TShiftState& Shift);
	void OnKeyUp(unsigned short &Key, const TShiftState& Shift);

private:
	void Clamp(float v[3]);
};

#endif 
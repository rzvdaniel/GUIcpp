#ifndef T_CAPTIONBAR_H
#define T_CAPTIONBAR_H
//-------------------------------------------------------------------
//  CLASS
//  TCaptionBar
//
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TCaptionBar
#include "guide/ndefdllclass.h"

#ifndef T_WINCONTROL_H
#include "guide/wincontrol.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TCaptionBar : public TWinControl
{
	int MouseX;
	int MouseY;

public:
	TCaptionBar();
	virtual ~TCaptionBar();
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

protected:
	// Events	
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);
	virtual void OnParentActivate(void);
	virtual void OnParentDeactivate(void);
};

//-------------------------------------------------------------------
#endif

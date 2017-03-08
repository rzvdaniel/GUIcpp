#ifndef T_RADIOBTN_H
#define T_RADIOBTN_H
//-------------------------------------------------------------------
//  CLASS
//  TRadioBtn
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TRadioBtn
#include "guide/ndefdllclass.h"

#ifndef T_CHECKBTN_H
#include "guide/checkbtn.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TRadioBtn : public TCheckBtn
{
public:
	TRadioBtn();
	virtual ~TRadioBtn();
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	virtual void ParseSkin(TiXmlElement* XmlElement);
	virtual void SetCheckState(TCheckState Value);

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnEnable(void);
	virtual void OnDisable(void);
};

//-------------------------------------------------------------------
#endif 


#ifndef T_CHECKBTN_H
#define T_CHECKBTN_H
//-------------------------------------------------------------------
//  CLASS
//  TCheckBtn
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TCheckBtn
#include "guide/ndefdllclass.h"

#ifndef T_WINCONTROL_H
#include "guide/wincontrol.h"
#endif

#ifndef T_LABEL_H
#include "guide/label.h"
#endif

class TCheckBtn;
class TCheckLabel : public TLabel
{
	TCheckBtn* CheckBtn;

public:
	TCheckLabel();
	virtual ~TCheckLabel() {}

	virtual void SetCheckBtn(TCheckBtn* ACheckBtn) { CheckBtn = ACheckBtn; }
	TCheckBtn* GetCheckBtn(void) const { return CheckBtn; }

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
};

//-------------------------------------------------------------------
enum TCheckState { cbUp = 0, cbDown };

class N_PUBLIC TCheckBtn : public TWinControl
{
	TCheckLabel* Label;
	TCheckState CheckState;

public:
	TCheckBtn();
	virtual ~TCheckBtn();
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);
	
	virtual void SetCheckState(TCheckState Value);
	TCheckState GetCheckState(void) const { return CheckState; }

	void SetParent(TControl* AParent); 

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnTextChanged(void);	
	virtual void OnEnable(void);
	virtual void OnDisable(void);
};

//-------------------------------------------------------------------
#endif 


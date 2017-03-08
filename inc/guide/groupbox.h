#ifndef T_GROUPBOX_H
#define T_GROUPBOX_H
//-------------------------------------------------------------------
//  CLASS
//  TGroupBox
//
//  (C) 2003 Ricas -- R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TGroupBox
#include "guide/ndefdllclass.h"

#ifndef T_WINCONTROL_H
#include "guide/wincontrol.h"
#endif

enum TCaptionAlignment { caLeftJustify, caRightJustify, caCenter };
//-------------------------------------------------------------------

class N_PUBLIC TGroupBox : public TWinControl 
{
    /// Controls the placement of the caption within the group box
	TCaptionAlignment CaptionAlignment;
	/// Space between text and surrounding lines
	int CaptionSpacing;
	/// Position of text relative to the border of control
	int CaptionMargin;

protected:
	int CaptionPos;

public:
	TGroupBox();
	virtual ~TGroupBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	void SetCaptionAlignment(TCaptionAlignment Value);
	TCaptionAlignment GetCaptionAlignment(void) const { return CaptionAlignment; }

	void SetCaptionMargin(int Value) { CaptionMargin = Value; }
	int GetCaptionMargin(void) const { return CaptionMargin; }

protected:
	// Events	
	virtual void OnPaint(void);
	virtual void OnTextChanged(void);
};

//-------------------------------------------------------------------
#endif

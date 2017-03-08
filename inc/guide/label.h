#ifndef T_LABEL_H
#define T_LABEL_H
//-------------------------------------------------------------------
//  CLASS
//  TLabel
//
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TLabel
#include "guide/ndefdllclass.h"

#ifndef T_CONTROL_H
#include "guide/control.h"
#endif


enum TTextAlignment { taLeftJustify, taRightJustify, taCenter };

//-------------------------------------------------------------------
class N_PUBLIC TLabel : public TControl 
{		
    /// Controls the placement of the text within the label
    TTextAlignment TextAlignment;
	/// Label can resize automatically?
	bool AutoSize;

protected:
	float TextPosX;
	float TextMargin;

public:
	TLabel();
	virtual ~TLabel();	
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	void SetAutoSize(bool Value);
	bool GetAutoSize(void) const { return AutoSize; }

	void SetTextAlignment(TTextAlignment Value);
	TTextAlignment GetTextAlignment(void) const { return TextAlignment; }
	
	void SetTextMargin(float Value) { TextMargin = Value; }
	float GetTextMargin(void) const { return TextMargin; }

protected:
	// Events	
	virtual void OnPaint(void);	
	virtual void OnTextChanged(void);
	virtual void OnSize(int AWidth, int AHeight);

private:
	void UpdateTextPosition(void);
};

//-------------------------------------------------------------------
#endif 


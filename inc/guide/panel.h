#ifndef T_PANEL_H
#define T_PANEL_H
//-------------------------------------------------------------------
//  CLASS
//  TPanel
//
//  (C) 2002 Ricas -- R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TPanel
#include "guide/ndefdllclass.h"

#ifndef T_WINCONTROL_H
#include "guide/wincontrol.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TPanel : public TWinControl 
{		
public:
	TPanel();
	virtual ~TPanel();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

protected:
	// Events	
	virtual void OnPaint(void);
};

//-------------------------------------------------------------------
#endif

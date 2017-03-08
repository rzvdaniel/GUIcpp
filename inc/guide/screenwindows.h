#ifndef T_SCREENWINDOWS_H
#define T_SCREENWINDOWS_H
//-------------------------------------------------------------------
//  CLASS
//  TScreenWindows
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TScreenWindows
#include "guide/ndefdllclass.h"

#ifndef T_SCREENINDEPENDENT_H
#include "guide/screenindependent.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TScreenWindows : public TScreenIndependent
{
public:
	TScreenWindows();
	virtual ~TScreenWindows();	
	virtual void Create(const TRect& Rect, int Bpp, bool Full, const char* SkinFile);
	
	void Close(void);
	void Run(void);
	void Idle(void);

	virtual void SetMousePosition(int X, int Y);
};

//-------------------------------------------------------------------
#endif


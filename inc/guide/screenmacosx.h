#ifndef T_SCREENMACOSX_H
#define T_SCREENMACOSX_H
//-------------------------------------------------------------------
//  CLASS
//  TScreenMacosx
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TScreenMacosx
#include "guide/ndefdllclass.h"

#ifndef T_SCREENINDEPENDENT_H
#include "guide/screenindependent.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TScreenMacosx : public TScreenIndependent
{
public:
	TScreenMacosx();
	virtual ~TScreenMacosx();	
	virtual void Create(const TRect& Rect, int Bpp, bool Full);
};

//-------------------------------------------------------------------
#endif


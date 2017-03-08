#ifndef T_SCREENLINUX_H
#define T_SCREENLINUX_H
//-------------------------------------------------------------------
//  CLASS
//  TScreenLinux
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TScreenLinux
#include "guide/ndefdllclass.h"

#ifndef T_SCREENINDEPENDENT_H
#include "guide/screenindependent.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TScreenLinux : public TScreenIndependent
{
public:
	TScreenLinux();
	virtual ~TScreenLinux();	
	virtual void Create(const TRect& Rect, int Bpp, bool Full);
};

//-------------------------------------------------------------------
#endif


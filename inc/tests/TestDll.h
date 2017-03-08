#ifndef T_TESTDLL_H
#define T_TESTDLL_H
//-------------------------------------------------------------------
//  CLASS
//  TTestDll
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#ifndef T_DLL_H
#include "guide/dll.h"
#endif

//-------------------------------------------------------------------

class TTestDll : public TDll
{
public:
	void (*InitTest)(void);
	void (*ExitTest)(void);

public:
	TTestDll();
	virtual ~TTestDll();

	void Open(const char *name);
	void Close(void);
};
                                                                     
//-------------------------------------------------------------------
#endif


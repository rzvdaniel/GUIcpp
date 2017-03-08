#ifndef T_DLL0_H
#define T_DLL0_H
//-------------------------------------------------------------------
//  CLASS
//  TTestDll
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORMAQUA_H
#include "guideaqua/formaqua.h"
#endif

extern "C" __declspec(dllexport) void InitTest(void);
extern "C" __declspec(dllexport) void ExitTest(void);

//-------------------------------------------------------------------

class __declspec(dllexport) TDll0 : public TFormAqua
{

public:
	TDll0();
	virtual ~TDll0();
};

extern "C" __declspec(dllexport) TDll0* Dll0;

                                                                   
//-------------------------------------------------------------------
#endif


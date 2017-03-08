//-------------------------------------------------------------------
//  Dll0.cpp
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#include "dll/Dll0.h"
#include "guide/screen.h"
#include "guide/debug.h"

#ifdef __WIN32__
#include <windows.h>
#endif

TDll0* Dll0 = NULL;

//-------------------------------------------------------------------
//  InitTest()
//  05-May-2004  rzv   created
//-------------------------------------------------------------------
void InitTest(void)
{
	Dll0 = new TDll0;
	Dll0->Create(NULL, TRect(200, 150, 400, 300), true);
}

//-------------------------------------------------------------------
//  ExitTest()
//  05-May-2004  rzv   created
//-------------------------------------------------------------------
void ExitTest(void)
{
	if(Dll0 != NULL)
		delete Dll0;
}

#ifdef __WIN32__
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
#endif

//-------------------------------------------------------------------
//  TDll0()
//  05-May-2004  rzv   created
//-------------------------------------------------------------------
TDll0::TDll0()
{
}

//-------------------------------------------------------------------
//  ~TDll0()
//  05-May-2004  rzv   created
//-------------------------------------------------------------------
TDll0::~TDll0()
{
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------
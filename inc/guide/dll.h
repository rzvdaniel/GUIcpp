#ifndef T_DLL_H
#define T_DLL_H
//-------------------------------------------------------------------
/**
	@class TDll
	@brief @brief A portable dll openening/closing function for Windows, 
	Linux, and Mac OS X.

	(C) 2002 RadonLabs GmbH
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TDll
#include "guide/ndefdllclass.h"

#include <string>

//-------------------------------------------------------------------

typedef stl::string TString;

//-------------------------------------------------------------------

class N_PUBLIC TDll 
{
protected:
	void* Image;

public:
	TDll();
	virtual ~TDll();
	
	void* Symbol(const char *sym);
	void Open(const char *name);
	void Close(void);
};
                                                                     
//-------------------------------------------------------------------
#endif


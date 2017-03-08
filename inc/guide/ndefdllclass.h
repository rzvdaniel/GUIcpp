//-------------------------------------------------------------------
//	OVERVIEW
//  DLL export/import related stuff.
//
//  (C) 1999 A.Weissflog
//-------------------------------------------------------------------
#ifndef N_SYSTEM_H
#include "guide/nsystem.h"
#endif

#undef N_DLLCLASS
#ifdef __VC__
#   if defined(N_IMPLEMENTS) && defined(N_DEFINES) && (N_IMPLEMENTS==N_DEFINES)
#       define N_DLLCLASS
#       define N_PUBLIC __declspec(dllexport)
#   else
#       define N_DLLCLASS
#       define N_PUBLIC __declspec(dllimport)
#   endif
#else
#   define N_DLLCLASS
#   define N_PUBLIC
#endif

//-------------------------------------------------------------------
  

#ifndef T_DEBUG_H
#define T_DEBUG_H

//-------------------------------------------------------------------
//  This code was originally created by Radonlabs for their graphic
//  engine Nebula. All the credits goes to Radonlabs www.radonlabs.de
//-------------------------------------------------------------------

#include <stdlib.h>

#ifdef __MMGR__
//#include "guide/mmgr.h"
#endif

#include "guide/ndefdllclass.h"

//-------------------------------------------------------------------

N_EXPORT void t_printf(const char *,...);
N_EXPORT void t_sleep(double);
N_EXPORT void t_barf(const char *, const char *, int);

#ifdef __NO_ASSERT__
#define t_assert(exp)
#else
#define t_assert(exp) { if (!(exp)) t_barf(#exp,__FILE__,__LINE__); }
#endif

#define t_error(x) do { t_printf("ERROR %s/%d: %s\n", __FILE__, __LINE__, x); abort(); } while(0)
#define t_warn(x) do { t_printf("WARN %s/%d: %s\n", __FILE__, __LINE__, x); } while(0)

//-------------------------------------------------------------------
#endif


//-------------------------------------------------------------------
//  This code was originally created by Radonlabs for their graphic
//  engine Nebula. All the credits goes to Radonlabs www.radonlabs.de
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//  debug.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include "guide/debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __WIN32__
#include <windows.h>
#endif

#ifdef __LINUX__
#include <time.h>
#include <dlfcn.h>
#endif

//FILE *logfile = fopen("guide.log","w"); 
//FILE *logfile = stderr;
FILE *logfile = stdout;

//--------------------------------------------------------------------
//  t_barf()
//  13-Dec-99   floh    created
//--------------------------------------------------------------------
N_EXPORT void t_barf(const char *exp, const char *file, int line)
{
    t_printf("*** NEBULA ASSERTION ***\nexpression: %s\nfile: %s\nline: %d\n",
             exp, file, line);
    t_sleep(1.0f);
    abort();
}

//--------------------------------------------------------------------
//  t_printf()
//  27-Nov-98   floh    created
//--------------------------------------------------------------------
N_EXPORT void t_printf(const char *s, ...)
{
    va_list arglist;
    va_start(arglist,s);
    vfprintf(logfile,s,arglist);
    va_end(arglist);
}

//--------------------------------------------------------------------
//  t_sleep()
//  21-Dec-98   floh    created
//--------------------------------------------------------------------
N_EXPORT void t_sleep(double sec)
{
#   ifdef __WIN32__
    int milli_sec = (int) (sec * 1000.0);
    Sleep(milli_sec);
#   else
    struct timespec t;
    #define N_NANOSEC_INT 1000000000
    #define N_NANOSEC_FLT 1000000000.0
    long long int nano_sec = (long long int) (sec * N_NANOSEC_FLT);
    t.tv_sec  = nano_sec / N_NANOSEC_INT;
    t.tv_nsec = nano_sec % N_NANOSEC_INT;
    nanosleep(&t,NULL);
#   endif
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

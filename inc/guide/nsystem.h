#ifndef N_SYSTEM_H
#define N_SYSTEM_H
//--------------------------------------------------------------------
//  OVERVIEW
//  Platform specific macros and defines.
//
//  (C) 1999 A.Weissflog
//--------------------------------------------------------------------
#ifndef T_DEFINES_H
#include "guide/defines.h"
#endif 

#ifdef __WIN32__
#   undef __WIN32__
#endif

#ifdef WIN32
#   define __WIN32__ (1)
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// this speeds up windows.h processing dramatically...
#define NOGDICAPMASKS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCTLMGR
#define NONLS
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSERVICE
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX

//--------------------------------------------------------------------
//  compiler identification:
//  __VC__      -> Visual C
//  __GNUC__    -> gcc
//--------------------------------------------------------------------
#ifdef _MSC_VER
#define __VC__ (1)
#endif

#ifdef __VC__
#if (_MSC_VER < 1100)      // MSVC 4.x doesn't know bool 
#   define bool ushort
#   define true (1)
#   define false (0)
#endif
#endif

//--------------------------------------------------------------------
//  disable some VC warnings
//--------------------------------------------------------------------
#ifdef __VC__
#pragma warning( disable : 4251 )       // class XX needs DLL interface to be used...
#pragma warning( disable : 4355 )       // initialization list uses 'this' 
#pragma warning( disable : 4275 )       // base class has not dll interface...
#pragma warning( disable : 4786 )       // identifier was truncated to '255' chars...

#if (_MSC_VER >= 1400)       // VC8+
#pragma warning(disable : 4996)    // Either disable all deprecation warnings,
// Or just turn off warnings about the newly deprecated CRT functions.
// #ifndef _CRT_SECURE_NO_DEPRECATE
// #define _CRT_SECURE_NO_DEPRECATE
// #endif
// #ifndef _CRT_NONSTDC_NO_DEPRECATE
// #define _CRT_NONSTDC_NO_DEPRECATE
// #endif
#endif   // VC8+

#endif

//--------------------------------------------------------------------
//  __NCPU__
//--------------------------------------------------------------------
#if __GNUC__
#   if i386
#       define __NCPU__ "x86"
#       define __N_LITTLEENDIAN__ 
#   elif alpha
#       define __NCPU__ "alpha"
#       define __N_LITTLEENDIAN__ 
#   elif m68k
#       define __NCPU__ "m68k"
#       define __N_BIGENDIAN__ 
#   elif mips
#       define __NCPU__ "mips"
#       define __N_LITTLEENDIAN__ 
#   elif ppc
#       define __NCPU__ "ppc"
#       define __N_BIGENDIAN__ 
#   elif sparc
#       define __NCPU__ "sparc"
#       define __N_LITTLEENDIAN__ 
#   elif __WIN32__
#       define __NCPU__ "i386"
#       define __N_LITTLEENDIAN__ 
#   else
#       define __NCPU__ "other"
#       define __N_LITTLEENDIAN__ 
#   endif
#elif __VC__
#   if _M_ALPHA
#       define __NCPU__ "alpha"
#       define __N_LITTLEENDIAN__ 
#   elif _M_IX86
#       define __NCPU__ "x86"
#       define __N_LITTLEENDIAN__ 
#   elif _M_MPPC
#       define __NCPU__ "ppc"
#       define __N_BIGENDIAN__ 
#   elif _M_MRX000
#       define __NCPU__ "mips"
#       define __N_LITTLEENDIAN__ 
#   else
#       define __NCPU__ "other"
#       define __N_LITTLEENDIAN__ 
#   endif
#else
#   define __NCPU__ "other"
#   define __N_LITTLEENDIAN__ 
#endif

//--------------------------------------------------------------------
//  __NSYSTEM__
//--------------------------------------------------------------------
#if __LINUX__
#   if __GLIBC__
#       define __NSYSTEM__ "linux"
#   else
#       define __NSYSTEM__ "oldlinux"
#   endif
#elif __WIN32__
#   define __NSYSTEM__ "win32"
#else
#   define __NSYSTEM__ "other"
#endif

//--------------------------------------------------------------------
//  __NCOMPILER__
//--------------------------------------------------------------------
#if __GNUC__
#   define __NCOMPILER__ "gcc"
#elif __VC__
#   define __NCOMPILER__ "vc"
#else
#   define __NCOMPILER__ "other"
#endif

//--------------------------------------------------------------------
//  __NVERSION__
//--------------------------------------------------------------------
#define __NVERSION__ __NSYSTEM__"-"\
                     __NCOMPILER__"-"\
                     __NCPU__"-"\
                     __DATE__"-"\
                     __TIME__

//--------------------------------------------------------------------
//  N_EXPORT, N_IMPORT, N_INLINECLASS
//--------------------------------------------------------------------
#ifdef __VC__
#   ifndef N_STATIC
#       define N_EXPORT __declspec(dllexport)
#       define N_IMPORT __declspec(dllimport)
#       define N_INLINECLASS
#   else
#       define N_EXPORT
#       define N_IMPORT
#       define N_INLINECLASS
#   endif
#else
#   define N_EXPORT
#   define N_IMPORT
#   define N_INLINECLASS
#endif

//--------------------------------------------------------------------
#endif


#ifndef T_OSINCLUDES_H
//-------------------------------------------------------------------
//  OS specific includes
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------

#ifdef __WIN32__
#include <windows.h>
#endif

#ifdef __MACOSX__
// Define this to force some constants to be initialized from
// the Apple glext.h header.  Apple defines the ARB versions
// of the texture env stuff from OpenGL 1.3 while Nebula uses
// the EXT form from OpenGL 1.2.
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <Carbon/carbon.h>
#include <AGL/agl.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifdef __LINUX__
#include <GL/glx.h>
#include <X11/Xatom.h>
#include <X11/Xmu/StdCmap.h>
#include <X11/keysym.h>
#include <X11/extensions/xf86vmode.h>
#endif

//-------------------------------------------------------------------
#endif

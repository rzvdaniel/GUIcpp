#define N_IMPLEMENTS TDll
//-------------------------------------------------------------------
/**
	This code was originally created by Radonlabs for their graphic
	engine Nebula. All the credits goes to Radonlabs www.radonlabs.de

	(C) 2002 RadonLabs GmbH
*/
//-------------------------------------------------------------------

#include "guide/dll.h"
#include "guide/debug.h"

#ifdef __WIN32__
#include <windows.h>
#include <direct.h>
#endif

#ifdef __LINUX__
#include <time.h>
#include <sys/time.h>
#include <dlfcn.h>
#include <dirent.h>
#include <sys/stat.h>
#endif

#ifdef __MACOSX__
#include <Carbon/carbon.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/stat.h>
#endif

//-------------------------------------------------------------------
//  TDll()
//  22-Sep-2003   rzv   created
//-------------------------------------------------------------------
TDll::TDll()
{
	Image = NULL;
}

//-------------------------------------------------------------------
//  ~TDll()
//  22-Sep-2003   rzv   created
//-------------------------------------------------------------------
TDll::~TDll()
{
	Image = NULL;
}

//-------------------------------------------------------------------
/**
  @brief A portable dll openening function for Windows, Linux, and Mac OS X.

  @param name A char pointer to a string with the dll name, for linux without 
  leading 'lib' and without trailing 'so', for windows systems the full dll name 
  is required.
*/
//-------------------------------------------------------------------
#if defined(__LINUX__)
static void* DllOpenWrapper(const char *name, bool prefix)
{
    char dll_name[256];
    if (prefix) {
        strcpy(dll_name,"lib");
        strcat(dll_name,name);
    } else {
        strcpy(dll_name,name);
    }
    strcat(dll_name,".so");
    void *dll = dlopen(dll_name,RTLD_NOW|RTLD_GLOBAL);
    // Caller will handle printing error
    return dll;
}

void TDll::Open(const char *name)
{
    this->Image = DllOpenWrapper(name, true);
    if (!this->Image) {
        char *err1 = strdup(dlerror());
        this->Image = DllOpenWrapper(name, false);
		if (!this->Image) {
	    const char *err2 = dlerror();
            t_printf("Could not load dll for '%s'\n", name);
            t_printf("Error was:\n");
            t_printf("%s\n", err1);
            t_printf("%s\n", err2);
	    delete err1;
        }
    }
}
#elif defined(__WIN32__)
void TDll::Open(const char *name)
{
    HINSTANCE dll;
    dll = LoadLibrary((LPCSTR) name);
    if (!dll) {
        // Find out why we failed
        LPVOID lpMsgBuf;
        FormatMessage( 
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM | 
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0,
            NULL 
            );
        
        // Display the string.
        t_printf("Could not load dll '%s'\nError was:\n%s\n", name, lpMsgBuf);

        // Free the buffer.
        LocalFree( lpMsgBuf );
    }
    this->Image =  (void *) dll;
}
#elif defined(__MACOSX__)
void TDll::Open(const char *name)
{
    const int kBundleAnyType  = 0;
    const int kBundleNoSubdir = 0;

    CFBundleRef mainBundle = CFBundleGetMainBundle();

    // put the name of the bundle we want in a CFString
    TString bundleName( name );
    bundleName += ".bundle";
    CFStringRef cfBundleName = CFStringCreateWithCString( NULL,
                                                          bundleName.c_str(),
                                                          kCFStringEncodingASCII );

    CFURLRef bundleURL = CFBundleCopyResourceURL( mainBundle,
                                                  cfBundleName, 
                                                  kBundleAnyType, 
                                                  kBundleNoSubdir );

    if ( bundleURL )
    {
        CFBundleRef myBundle = CFBundleCreate( kCFAllocatorDefault, bundleURL );
        Boolean loaded = CFBundleLoadExecutable( myBundle );
        if ( loaded )
            this->Image = myBundle;
    }
}
#else
void TDll::Open(const char *name)
{
    t_error("TDll::Open() not implemented!");
}
#endif

//-------------------------------------------------------------------
/**
	@brief A portable dll closing function for Windows, Linux and 
	Mac OSX systems.
*/
//-------------------------------------------------------------------
#ifdef __LINUX__
void TDll::Close(void)
{
    dlclose(this->Image);
	this->Image = NULL;
}
#elif defined(__WIN32__)
void TDll::Close(void)
{
    FreeLibrary((HMODULE)this->Image);
	this->Image = NULL;
}
#elif defined(__MACOSX__)
void TDll::Close(void)
{
    CFBundleUnloadExecutable((CFBundleRef)this->Image);
	this->Image = NULL;
}
#else
void TDll::Close(void)
{
    t_error("TDll::Close() not implemented!");
}
#endif

//-------------------------------------------------------------------
/**
  @brief Look up a symbol within a DLL.
  @param sym Symbol to look for.
*/
//-------------------------------------------------------------------
#ifdef __LINUX__
void* TDll::Symbol(const char *sym)
{
    void *h = dlsym(this->Image,sym);
    if (!h)
    {
        t_printf("%s\n", dlerror());
        t_error("TDll::Symbol() failed!\n");    
    }
    return h;
}
#elif defined(__WIN32__)
void* TDll::Symbol(const char *sym)
{
    FARPROC h = GetProcAddress((HMODULE)this->Image, (LPCSTR)sym);
    if (!h) t_error("TDll::Symbol() failed!\n");
    return (void *) h;
}
#elif defined(__MACOSX__)
void* TDll::Symbol(const char *sym)
{
    CFStringRef cfSym = CFStringCreateWithCString( NULL, sym,
                                                   kCFStringEncodingASCII );
    void *h = (void*)CFBundleGetFunctionPointerForName( (CFBundleRef)this->Image,
                                                        cfSym );
    if (!h)
    {
        t_error( "TDll::Symbol() failed!\n" );
    }
    return h;
}
#else
void* TDll::Symbol(const char *sym)
{
    t_error("TDll::Symbol() not implemented!");
}
#endif

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

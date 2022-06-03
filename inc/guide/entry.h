#ifndef T_ENTRY_H
#define T_ENTRY_H
//-------------------------------------------------------------------
//  CLASS
//  TEntry
//
//  Original code by Radonlabs - www.radonlabs.de
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TEntry
#include "guide/ndefdllclass.h"

#ifndef T_STRINGCI_H
#include "string.h"
#endif

#ifdef __WIN32__
    #include <io.h>
    #include <direct.h>
#endif

#if defined(__LINUX__) || defined(__MACOSX__)
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <dirent.h>
	#include <errno.h>
#endif 

//--------------------------------------------------------------------
//  Wrap some Win32 silly named directory functions
//--------------------------------------------------------------------
#ifdef __WIN32__
#   define getcwd      _getcwd
#   define chdir       _chdir
#   define rmdir       _rmdir
#   define mkdir(x,y)  _mkdir(x)
#endif

#include <set>

enum TEntryAttributes { eaNormal, eaReadOnly, eaHidden, eaSystem, eaSubdir, eaArchive };

typedef stl::set< TEntryAttributes, stl::less<TEntryAttributes> > TEntryAttrib;

//-------------------------------------------------------------------
class N_PUBLIC TEntry 
{
	TString Name;
	TEntryAttrib Attrib;
	long TimeCreate;
	long TimeAccess;
	long TimeWrite;
	unsigned long Size;

public:
	TEntry(void);
	virtual ~TEntry(void) {}

	void SetAttrib(TEntryAttrib Value) { Attrib = Value; }
	TEntryAttrib GetAttrib(void) const { return Attrib; }
	
	void SetName(TString AName) { Name.assign(AName); }
	void SetName(const char* AName) { Name.assign(AName); }
	TString GetName(void) const { return Name; }

	void SetTimeCreate(long Value) { TimeCreate = Value; }
	long GetTimeCreate(void) const { return TimeCreate; }
	
	void SetTimeAccess(long Value) { TimeAccess = Value; }
	long GetTimeAccess(void) const { return TimeAccess; }

	void SetTimeWrite(long Value) { TimeWrite = Value; }
	long GetTimeWrite(void) const { return TimeWrite; }

	void SetSize(unsigned long Value) { Size = Value; }
	unsigned long GetSize(void) const { return Size; }
};
                                                                   
//-------------------------------------------------------------------
#endif


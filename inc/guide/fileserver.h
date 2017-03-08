#ifndef T_FILESERVER_H
#define T_FILESERVER_H
//--------------------------------------------------------------------
/**
    @class TFileServer

    @brief New fileserver, provides functions for creating file and
    directory objects and assigns

    (C) 2002 RadonLabs GmbH
*/ 
#undef N_DEFINES
#define N_DEFINES TFileServer
#include "guide/ndefdllclass.h"

#ifndef T_TYPEDEF_H
#include "guide/typedef.h"
#endif

#ifndef T_ENTRY_H
#include "guide/entry.h"
#endif

//--------------------------------------------------------------------
class N_PUBLIC TFileServer
{
	TString Cwd;
	
public:
    TFileServer();
    virtual ~TFileServer();

#	ifdef __WIN32__
    virtual int ChangeDrive(char Value);
    virtual char GetDrive(void);
#	elif __LINUX__
	virtual bool ChangeDrive(const char* Value);
    virtual const char* GetDrive(void);
#	endif

    virtual bool SetCwd(const char* Dir);
    virtual const char* GetCwd(void);

    virtual int GetNumFiles(void);
    virtual int GetNumDirectories(void);
    virtual int GetNumEntries(void);
	virtual void GetEntry(TEntry& Entry, int Index);

	/// Tells if an entry is directory or not
	virtual int IsDir(const char* Path);
	
	bool CheckExtension(const char* Filename, const char* Extension);

private:
#	ifdef __WIN32__	
	int GetNextEntry(TEntry& Entry, int Handle);
	int GetFirstEntry(TEntry& Entry);
	TEntry MakeEntry(_finddata_t FindData);
#	elif __LINUX__	
	TEntry MakeEntry(dirent* DirEntry);
#	endif
};

//--------------------------------------------------------------------
#endif

#define N_IMPLEMENTS TFileServer
//-------------------------------------------------------------------
//  fileserver.cpp
//  (C) 2002 RadonLabs GmbH 
//-------------------------------------------------------------------
#if defined(__MACOSX__)
#include <Carbon/carbon.h>
#endif 
#include <stdio.h>

#include "guide/string.h"
#include "guide/fileserver.h"
#include "guide/debug.h"

//--------------------------------------------------------------------
/**
  @fn char *n_strncpy2(char *dest, const char *src, size_t size)
  @brief A strncopy function which sets a 0 at the end of the copied string

  @param dest A char pointer where the string will be copied to.
  @param src  A char pointer to a 0 terminated character string
  @param size The length of the source string without trailing 0

  Works like @c strncpy(), but makes sure that the copied string
  is terminated correcly (that is, in ALL cases, a terminating
  0 is appended without violating the 'size' boundary. 

  - 19-Feb-99   floh    created
*/
//------------------------------------------------------------------------------
char *n_strncpy2(char *dest, const char *src, size_t size)
{
    strncpy(dest,src,size);
    dest[size-1] = 0;
    return dest;
} 

//--------------------------------------------------------------------
//  TFileServer()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
TFileServer::TFileServer()
{
}

//--------------------------------------------------------------------
//  ~TFileServer()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
TFileServer::~TFileServer()
{
}

//--------------------------------------------------------------------
//  ChangeDrive()
//  23-Dec-2003   rzv   created
//--------------------------------------------------------------------	
#ifdef __WIN32__
int TFileServer::ChangeDrive(char Value)
{	
	// Set the new drive as current.
	return _chdrive(Value);
}

//--------------------------------------------------------------------
//  GetDrive()
//  23-Dec-2003   rzv   created
//--------------------------------------------------------------------
char TFileServer::GetDrive(void)
{
	return _getdrive();
}
#endif

//--------------------------------------------------------------------
//  ChangeDrive()
//  Linux version
//  23-Dec-2003   rzv   created
//--------------------------------------------------------------------
#ifdef __LINUX__
bool TFileServer::ChangeDrive(const char* Value)
{
	// Set the current working directory.
	return SetCwd(Value);
}

//--------------------------------------------------------------------
//  GetDrive()
//  Linux version
//  23-Dec-2003   rzv   created
//--------------------------------------------------------------------
const char* TFileServer::GetDrive(void)
{
	return GetCwd();
}
#endif

//--------------------------------------------------------------------
//  SetCwd()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
bool TFileServer::SetCwd(const char* Dir)
{
    // Change to working directory
    int result = chdir(Dir);

    return (result == 0);
}

//--------------------------------------------------------------------
//  GetCwd()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
const char* TFileServer::GetCwd(void)
{
	char buf[T_MAXPATH];
		
	char* cwd;
    cwd = getcwd(buf, sizeof(buf));
	
	if(cwd == NULL)
	{
		t_printf("Current working directory failed\n");
		return NULL;
	}
    
	Cwd.assign(buf);
		 
	return Cwd.c_str();
}

//--------------------------------------------------------------------
//  GetNumEntries()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
int TFileServer::GetNumEntries(void)
{
	int NumEntries = 0;

#	ifdef __WIN32__	

	struct _finddata_t FindData;
    int Handle = _findfirst("*.*",&FindData);
    while (_findnext(Handle, &FindData) == 0) 
			NumEntries++;
	_findclose(Handle);
	
#	elif __LINUX__

	// Open current working directory
	DIR *dir = opendir( GetCwd() );
	
	if( !dir )
		t_printf("Error opening %s: %s\n", GetCwd(), strerror(errno));
	else
	{
		struct dirent *de;
		while( (de = readdir(dir)) != NULL )
		{
			// Skip "." and "..".
			//if( !strcmp(".",de->d_name) || !strcmp("..",de->d_name) )
			//	continue;
			
			NumEntries++;
		}
		
		if( closedir(dir) )
			t_printf("Error opening %s: %s\n", GetCwd(), strerror(errno));
	}
		
#	endif
	
	return NumEntries;
}

//--------------------------------------------------------------------
//  GetNumFiles()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
int TFileServer::GetNumFiles(void)
{
	int NumFiles = 0;

#	ifdef __WIN32__	

	struct _finddata_t FindData;

    int Handle = _findfirst("*.*",&FindData);
    while (_findnext(Handle, &FindData) == 0) 
    {
		if(!(FindData.attrib & _A_SUBDIR))
			NumFiles++;
    }
	_findclose(Handle);
	
#	elif __LINUX__

	// Open current working directory
	DIR *dir = opendir( GetCwd() );
	
	if( !dir )
		t_printf("Error opening %s: %s\n", GetCwd(), strerror(errno));
	else
	{
		struct dirent *de;
		while( (de = readdir(dir)) != NULL )
		{
			// Skip "." and "..".
			if( !strcmp(".",de->d_name) || !strcmp("..",de->d_name) )
				continue;
						
			if(IsDir(de->d_name) == 0)
				NumFiles++;
		}
		
		if( closedir(dir) )
			t_printf("Error opening %s: %s\n", GetCwd(), strerror(errno));
	}
	
#	endif

	return NumFiles;
}

//--------------------------------------------------------------------
//  GetNumDirectories()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
int TFileServer::GetNumDirectories(void)
{
	int NumDirectories = 0;

#	ifdef __WIN32__	

	struct _finddata_t FindData;
    int Handle = _findfirst("*.*",&FindData);
    while (_findnext(Handle, &FindData) == 0) 
    {
		if(FindData.attrib & _A_SUBDIR)
			NumDirectories++;
    }
	_findclose(Handle);
	
#	elif __LINUX__

	// Open current working directory
	DIR *dir = opendir( GetCwd() );
	
	if( !dir )
		t_printf("Error opening %s: %s\n", GetCwd(), strerror(errno));
	else
	{
		struct dirent *de;
		while( (de = readdir(dir)) != NULL )
		{
			// Skip "." and "..".
			if( !strcmp(".",de->d_name) || !strcmp("..",de->d_name) )
				continue;
						
			if(IsDir(de->d_name) == 1)
				NumDirectories++;
		}
		
		if( closedir(dir) )
			t_printf("Error opening %s: %s\n", GetCwd(), strerror(errno));
	}
	
#	endif

	return NumDirectories;
}

//--------------------------------------------------------------------
//  GetNextEntry()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
#ifdef __WIN32__	
int TFileServer::GetNextEntry(TEntry& Entry, int Handle)
{
	struct _finddata_t FindData;
	int NewHandle = _findnext(Handle, &FindData);
	Entry = MakeEntry(FindData);
	return NewHandle;
}

//--------------------------------------------------------------------
//  GetFirstEntry()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
int TFileServer::GetFirstEntry(TEntry& Entry)
{
	struct _finddata_t FindData;
	int NewHandle = _findfirst("*.*", &FindData);
	Entry = MakeEntry(FindData);
	_findclose(NewHandle);
	return NewHandle;
}
#endif

//--------------------------------------------------------------------
//  GetEntry()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
void TFileServer::GetEntry(TEntry& Entry, int Index)
{
	int NewHandle = 0;

#	ifdef __WIN32__	
	if(Index == 0) 
		 NewHandle = GetFirstEntry(Entry);
	else
	{
		struct _finddata_t FindData;
		NewHandle = _findfirst("*.*", &FindData);
		int i=1;
		while(_findnext(NewHandle, &FindData) == 0) 
		{
			if(i == Index)
			{
				Entry = MakeEntry(FindData);
				break;
			}
			i++;
		}
		_findclose(NewHandle);
	}
#	elif __LINUX__

	// Open current working directory
	DIR *dir = opendir( GetCwd() );
	
	if( !dir )
		t_printf("Error opening %s: %s\n", GetCwd(), strerror(errno));
	else
	{
		int i=1;
		struct dirent* DirectoryEntry;
		while( (DirectoryEntry = readdir(dir)) != NULL )
		{
			// Skip "." and "..".
			//if( !strcmp(".", DirectoryEntry->d_name) || !strcmp("..", DirectoryEntry->d_name) )
			//	continue;
						
			if(i == Index)
			{
				Entry = MakeEntry(DirectoryEntry);
				break;
			}
			i++;
		}
		
		if( closedir(dir) )
			t_printf("Error opening %s: %s\n", GetCwd(), strerror(errno));
	}
	

#	endif
}

//--------------------------------------------------------------------
/**
	@param Path The path we want to find if it is directory or not.
	@return Value <code>1</code> if the specified path is directory, 
	value <code>0</code> if not.
*/
//--------------------------------------------------------------------
int TFileServer::IsDir(const char* Path)
{
#	ifdef __WIN32__

	// Not implemented, yet.
	return -1;

#	elif __LINUX__

	struct stat st_buf;

	if( stat( Path, &st_buf ) )
		return -1;

	return S_ISDIR( st_buf.st_mode );

#	endif

	return -1;
}

//--------------------------------------------------------------------
//  MakeEntry()
//  21-Dec-2003   rzv   created
//--------------------------------------------------------------------
#ifdef __WIN32__
TEntry TFileServer::MakeEntry(_finddata_t FindData)
{
	TEntryAttrib Attrib;
	if(FindData.attrib & _A_NORMAL)
		Attrib.insert(eaNormal);
	if(FindData.attrib & _A_RDONLY)
		Attrib.insert(eaReadOnly);
	if(FindData.attrib & _A_HIDDEN)
		Attrib.insert(eaHidden);
	if(FindData.attrib & _A_SYSTEM)
		Attrib.insert(eaSystem);
	if(FindData.attrib & _A_SUBDIR)
		Attrib.insert(eaSubdir);
	if(FindData.attrib & _A_ARCH)
		Attrib.insert(eaArchive);

	TEntry Entry;
	Entry.SetAttrib(Attrib);
	Entry.SetName(FindData.name);
	Entry.SetSize(FindData.size);
	Entry.SetTimeCreate(FindData.time_create);
	Entry.SetTimeAccess(FindData.time_access);
	Entry.SetTimeWrite(FindData.time_write);

	return Entry;
}
#elif __LINUX__
TEntry TFileServer::MakeEntry(dirent* DirEntry)
{
	TEntry Entry;
	
	if(DirEntry)
	{
		struct stat StatInfo;
		lstat(DirEntry->d_name, &StatInfo);
	
		TEntryAttrib Attrib;
	
		// If we have a directory
		if(S_ISDIR(StatInfo.st_mode))
			Attrib.insert(eaSubdir);
		else
			Attrib.insert(eaNormal);
	
		Entry.SetAttrib(Attrib);
		Entry.SetName(DirEntry->d_name);
		Entry.SetSize(StatInfo.st_size);
		Entry.SetTimeCreate(StatInfo.st_mtime);
		Entry.SetTimeAccess(StatInfo.st_atime);
		Entry.SetTimeWrite(StatInfo.st_ctime);
	}
	
	return Entry;
}
#endif

//--------------------------------------------------------------------
/**
	@brief Test if a filename has a given extension.
*/
bool TFileServer::CheckExtension(const char* Filename, const char* Extension)
{
	// if not a good filename/extension, exit early
	if (Filename == NULL || Extension == NULL || !strlen(Filename) || !strlen(Extension))  
		return false;

	TStringCi StrFilename(Filename);
	int i = StrFilename.find_last_of('.');
	
	TStringCi StrExtension = StrFilename.substr(i+1);
	
	if(!StrExtension.compare(Extension))
		return true;
	
	// Old version
	/*
	// pointer to Filename so we don't destroy Filename
	char *AFilename = (char*)Filename;  

	// start at the end
	AFilename += strlen(Filename);  
	
	bool PeriodFound = false;
	for(int i = strlen(Filename); i >= 0; i--) 
	{
		// try to find a period 
		if(*AFilename == '.') 
		{  
			PeriodFound = true;
			break;
		}
		AFilename--;
	}

	// if no period, no extension
	if (!PeriodFound)  
		return false;

	// extension and ext match?
#	ifdef __WIN32__
	if (!stricmp(AFilename+1, Extension))  
		return true;
#	elif __LINUX__
	if (!strcmp(AFilename, Extension))  
		return true;
#	endif
	*/

	return false;
}

//--------------------------------------------------------------------
//  EOF
//--------------------------------------------------------------------



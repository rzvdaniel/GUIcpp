#ifndef T_DIRECTORYLISTBOX_H
#define T_DIRECTORYLISTBOX_H
//-------------------------------------------------------------------
//  CLASS
//  TDirectoryListBox
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TDirectoryListBox
#include "guide/ndefdllclass.h"

#ifndef T_LABEL_H
#include "guide/label.h"
#endif

#ifndef T_FILELISTBOX_H
#include "guide/filelistbox.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TDirectoryListBox : public TListBox
{
#	ifdef __WIN32__
	char Drive;
#	endif

	TLabel* DirLabel;
	TString Directory;
	TFileListBox* FileList;

public:
	TDirectoryListBox();
	virtual ~TDirectoryListBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	void SetDirectory(TString Value);
	void SetDirectory(const char* Value);
	TString GetDirectory(void) const { return Directory; }

#	ifdef __WIN32__
	void SetDrive(char Value);
	char GetDrive(void) const { return Drive; }
#	elif __LINUX__
	void SetDrive(const char* Value);
	const char* GetDrive(void) const;
#	endif

	void SetFileList(TFileListBox* AFileList);
	TFileListBox* GetFileList(void) const { return FileList; }

protected:
	//Events
	virtual void OnDoubleClick(void);
	virtual void OnDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State);
};

//-------------------------------------------------------------------
#endif 


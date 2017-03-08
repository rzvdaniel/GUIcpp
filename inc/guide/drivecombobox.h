#ifndef T_DRIVECOMBOBOX_H
#define T_DRIVECOMBOBOX_H
//-------------------------------------------------------------------
//  CLASS
//  TDriveComboBox
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TDriveComboBox
#include "guide/ndefdllclass.h"

#ifndef T_COMBOBOX_H
#include "guide/combobox.h"
#endif

#ifndef T_DIRECTORYLISTBOX_H
#include "guide/directorylistbox.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TDriveComboListBox : public TComboListBox
{
public:
	TDriveComboListBox() {}
	virtual ~TDriveComboListBox() {}
};

//-------------------------------------------------------------------

class N_PUBLIC TDriveComboBox : public TComboBox
{
#	ifdef __WIN32__
	char Drive;
#	elif __LINUX__
	TString Drive;
#	endif

	TDirectoryListBox* DirList;

public:
	TDriveComboBox();
	virtual ~TDriveComboBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	void Clear(void);

	TDirectoryListBox* GetDirectoryListBox(void) const { return DirList; }
	void SetDirectoryListBox(TDirectoryListBox* ADirList) { DirList = ADirList; }

#	ifdef __WIN32__
	void SetDrive(char Value);
	char GetDrive(void) const { return Drive; }
#	elif __LINUX__
	void SetDrive(const char* Value);
	const char* GetDrive(void) const;
#	endif

protected:
	// Events
	virtual void OnTextChanged(void);
};

//-------------------------------------------------------------------
#endif 


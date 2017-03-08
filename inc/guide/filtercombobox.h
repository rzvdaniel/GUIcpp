#ifndef T_FILTERCOMBOBOX_H
#define T_FILTERCOMBOBOX_H
//-------------------------------------------------------------------
//  CLASS
//  TFilterComboBox
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TFilterComboBox
#include "guide/ndefdllclass.h"

#ifndef T_COMBOBOX_H
#include "guide/combobox.h"
#endif

#ifndef T_FILELISTBOX_H
#include "guide/filelistbox.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TFilterComboListBox : public TComboListBox
{
public:
	TFilterComboListBox() {}
	virtual ~TFilterComboListBox() {}
};

//-------------------------------------------------------------------
class N_PUBLIC TFilterComboBox : public TComboBox
{
	TFileListBox* FileList;
	TString Filter;
	TString Mask;

public:
	TFilterComboBox();
	virtual ~TFilterComboBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	TFileListBox* GetFileListBox(void) const { return FileList; }
	void SetFileListBox(TFileListBox* AFileList) { FileList = AFileList; }

	void SetFilter(const TString& AFilter);
	const TString& GetMask(void) { return Mask; }

protected:
	// Events
	virtual void OnTextChanged(void);
};

//-------------------------------------------------------------------
#endif 


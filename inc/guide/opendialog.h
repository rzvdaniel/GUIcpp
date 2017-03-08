#ifndef T_OPENDIALOG_H
#define T_OPENDIALOG_H
//-------------------------------------------------------------------
//  CLASS
//  TOpenDialog
//
//  (C) 2003 Ricas -- R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TOpenDialog
#include "guide/ndefdllclass.h"

#ifndef T_FORM_H
#include "guide/form.h"
#endif

#ifndef T_DRIVECOMBOBOX_H
#include "guide/drivecombobox.h"
#endif

#ifndef T_FILTERCOMBOBOX_H
#include "guide/filtercombobox.h"
#endif

#ifndef T_EDIT_H
#include "guide/edit.h"
#endif

//-------------------------------------------------------------------

class N_PUBLIC TOpenDialog : public TForm
{
	TDirectoryListBox* DirectoryListBox;
	TFileListBox* FileListBox;
	TDriveComboBox* DriveComboBox;
	TFilterComboBox* FilterComboBox;
	TEdit* EditBox;
	TButton* Ok;
	TButton* Cancel;

protected:
	TString Title;
	TString FileName;
	TString Filter;
	TStrings* Files;
	int FilterIndex;

public:
	TOpenDialog();
	virtual ~TOpenDialog();
	virtual void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
	
	TModalResult Execute(void);

	TButton* GetButtonOk(void) const { return Ok; }
	TButton* GetButtonCancel(void) const { return Cancel; }

	void SetTitle(TString ATitle);
	TString GetTitle(void) const { return Title; }

	TString GetFileName(void);

	void SetFilter(const TString& AFilter);
	TString GetFilter(void) const { return Filter; }

	void SetFilterIndex(int Value);
	int GetFilterIndex(void) const { return FilterIndex; }

	void SetInitialDir(TString AInitialDir);
	TString GetInitialDir(void) const;

protected:
	// Events
	virtual void OnFileListBoxSelectionChange(void);
};

//-------------------------------------------------------------------
#endif

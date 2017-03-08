#ifndef T_TEST6_H
#define T_TEST6_H
//-------------------------------------------------------------------
//  CLASS
//  TTest6
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

class TButton;
class TDirectoryListBox;
class TFileListBox;
class TDriveComboBox;
class TFilterComboBox;
class TTest6 : public TForm
{

	TDriveComboBox* DriveComboBox1;
	TFilterComboBox* FilterComboBox1;
	TFileListBox* FileListBox1;
	TDirectoryListBox* DirectoryListBox1;


public:  
    TTest6();
    virtual ~TTest6();
	void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

protected:
	// Events	
};

#endif 

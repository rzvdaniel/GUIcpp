#define N_IMPLEMENTS TDriveComboBox
//-------------------------------------------------------------------
//  drivecombobox.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/drivecombobox.h"
#include "guide/screen.h"
#include "guide/debug.h"


//-------------------------------------------------------------------
//  TDriveComboBox()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
TDriveComboBox::TDriveComboBox()
{
	DirList = NULL;
}

//-------------------------------------------------------------------
//  ~TDriveComboBox()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
TDriveComboBox::~TDriveComboBox()
{	
}

//-------------------------------------------------------------------
//  Create()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TDriveComboBox::Create(TComponent* AOwner, const TRect& Rect)
{		
	TComboBox::Create(AOwner, Rect);
	
	TFileServer* FileServer = Screen->GetFileServer();
		
#	ifdef __WIN32__

    // Save current drive.
    Drive = FileServer->GetDrive();

	// If we can switch to the drive, if exists.
    for(int i = 2; i <= 26; i++ )
	{
        if(!FileServer->ChangeDrive(i))
		{
			TString DriveName;
			DriveName = (char)(i + 'A' - 1);
			DriveName.append(":");

			// Insert the drive into the list box
			TListBoxItem* Item = new TListBoxItem;
			Item->SetString(DriveName);
			ListBox->Items->Append(Item);
		}
	}
	
	// Restore original drive.
	FileServer->ChangeDrive(Drive);

	// Set drive combobox text with the current drive.
	TString DriveName;
	DriveName = (char)(Drive + 'A' - 1);
	DriveName.append(":");
	SetText(DriveName);

#	elif __LINUX__

	SetText(FileServer->GetDrive());
	
#	endif
}

//-------------------------------------------------------------------
//  SetDrive()
//  23-Dec-2003   rzv   created
//-------------------------------------------------------------------
#ifdef __WIN32__
void TDriveComboBox::SetDrive(char Value) 
{ 
	if(Drive != Value)
	{
		// New drive value
		Drive = Value; 

		// Set the new drive as current.
		Screen->GetFileServer()->ChangeDrive(Value);

		// Notify the directory list that we've changed the drive
		if(DirList != NULL)
			DirList->SetDrive(Drive);
	}
}
#endif

//-------------------------------------------------------------------
//  SetDrive()
//  25-July-2005   rzv   created
//-------------------------------------------------------------------
#ifdef __LINUX__
void TDriveComboBox::SetDrive(const char* Value)
{
	// Set the new drive as current.
	Screen->GetFileServer()->ChangeDrive(Value);
	
	// Notify the directory list that we've changed the drive
	if(DirList != NULL)
		DirList->SetDrive(Value);
}

//-------------------------------------------------------------------
//  GetDrive()
//  25-July-2005   rzv   created
//-------------------------------------------------------------------
const char* TDriveComboBox::GetDrive(void) const
{
	return Screen->GetFileServer()->GetDrive();
}
#endif

//-------------------------------------------------------------------
//  OnTextChanged()
//  23-Dec-2003   rzv    created
//-------------------------------------------------------------------
void TDriveComboBox::OnTextChanged(void)
{
	TComboBox::OnTextChanged();

	TString DirectoryName = GetText();
	
#	ifdef __WIN32__
	SetDrive((char)DirectoryName[0] - 'A' + 1);
#	elif __LINUX__
	SetDrive(DirectoryName.c_str());
#	endif

}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------



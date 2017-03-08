#ifndef T_FILELISTBOX_H
#define T_FILELISTBOX_H
//-------------------------------------------------------------------
//  CLASS
//  TFileListBox
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TFileListBox
#include "guide/ndefdllclass.h"

#ifndef T_LISTBOX_H
#include "guide/listbox.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TFileListBox : public TListBox
{
	char Drive;
	TString Directory;
	TString FileName;
	TString Mask;
	bool ShowGlyphs;

public:
	TFileListBox();
	virtual ~TFileListBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);

	void SetDirectory(TString Value);
	void SetDirectory(const char* Value);
	TString GetDirectory(void) const { return Directory; }
	TString GetFileName(void);
	
	void SetDrive(char Value) { Drive = Value; }
	char GetDrive(void) const { return Drive; }

	void SetMask(TString Value);
	void SetMask(const char* Value);
	TString GetMask(void) const { return Mask; }

	void SetShowGlyphs(bool Value) { ShowGlyphs = Value; }
	bool GetShowGlyphs() { return ShowGlyphs; }

protected:
	void Update(void);

protected:
	//Events
	virtual void OnDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State);

};

//-------------------------------------------------------------------
#endif 


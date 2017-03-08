#ifndef T_FORM2_H
#define T_FORM2_H
//-------------------------------------------------------------------
//  CLASS
//  TForm2
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "formaqua.h"
#endif

class TOpenDialog;
class TTexture;
class TButton;
class TEdit;
class TForm1;
class TForm2 : public TForm
{
	/// Ok button
	TButton* Ok;
	/// Cancel button
	TButton* Cancel;
	/// LoadModel button
	TButton* LoadModel;
	/// LoadSkin button
	TButton* LoadSkin;
	/// Model filename
	TEdit* EditModel;
	/// Model skin filename
	TEdit* EditSkin;
	/// Open dialog
	TOpenDialog* OpenDialog;

	// Form1 pointer
	TForm1* Form1;

	/// Quake md2 model
	TMd2* Model;

public:  
    TForm2();
    virtual ~TForm2();
	virtual void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

	void SetMainForm(TForm1* Form) { Form1 = Form; }

protected:
	// Events	
	void OnOkClick(void);
	void OnLoadModelClick(void);
	void OnLoadSkinClick(void);
};

#endif 
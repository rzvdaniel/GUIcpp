#ifndef T_FORM1_H
#define T_FORM1_H
//-------------------------------------------------------------------
//  CLASS
//  TForm1
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_FORM_H
#include "guide/form.h"
#endif

#ifndef T_MD2_H
#include "Md2.h"
#endif

#ifndef T_FORM2_H
#include "Form2.h"
#endif

#ifndef T_ABOUT_H
#include "About.h"
#endif

#ifndef T_HELP_H
#include "Help.h"
#endif

class TPanel1;
class TOpenDialog;
class TTexture;
class TButton;
class TMainMenu;
class TPopupMenu;
class TMenuItem;
class TForm1 : public TForm
{
	/// Our 3D rendering area
	TPanel1* Panel1;
	/// Simple button
	TButton* Ok;
	/// Texture for background
	TTexture* Texture;
	/// Open dialog
	TOpenDialog* OpenDialog;
	/// About dialog
	TFormAbout* AboutForm;
	/// Help contents dialog
	TFormHelp* HelpForm;
	/// Load model dialog
	TForm2* Form2;

	/// Main menu
	TMainMenu* MainMenu;
	TPopupMenu* FileMenu;
	TPopupMenu* OptionsMenu;
	TPopupMenu* HelpMenu;
	/// Popup menu
	TPopupMenu* PopupMenu;
	TMenuItem* Stop;

	/// Quake md2 model
	TMd2* Model;
	/// Model name
	TString ModelName;

public:  
    TForm1();
    virtual ~TForm1();
	virtual void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);

	TMd2* GetModel(void) const { return Model; }
	void SetModel(TMd2* AModel) { Model = AModel; }

	void SetStopPopupItemCaption(const char* ACaption);
	TString GetStopPopupItemCaption(void) const;

protected:
	// Events	
	void OnOkClick(void);

	void OnFileLoadModel(void);
	void OnFileLoadSkin(void);
	void OnFileExit(void);

	void OnOptionsWireframe(void);
	void OnOptionsSolid(void);

	void OnHelpContents(void);
	void OnHelpAbout(void);
		
	void OnNextAnimation(void);
	void OnPrevAnimation(void);
	void OnAllAnimations(void);
	void OnToggleAnimations(void);
};

#endif 
#ifndef T_SCREEN_H
#define T_SCREEN_H
//-------------------------------------------------------------------
/**
	@class TScreen
	@brief Application's main class.
	
	It's  responsibilities are to:
	- create the graphic and file server;
	- create a skin object, accessible to all of the controls;
	- keep track of main and modal forms, captured controls;
	- manage visible popup menus;
	- handle mouse and keyboard input;
	- render visible forms and mouse cursor;
	
	Run() method enters the main loop of the program and 
	exit when the user  decides to leave the  application.

	@author Razvan Predescu (2002)
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TScreen
#include "guide/ndefdllclass.h"

#ifndef T_FORM_H
#include "guide/form.h"
#endif

#ifndef T_FONT_H
#include "guide/font.h"
#endif

#ifndef T_FILESERVER_H
#include "guide/fileserver.h"
#endif

#ifndef T_GFXSERVER_H
#include "guide/gfxserver.h"
#endif

//-------------------------------------------------------------------

typedef stl::list<TForm*> TFormsList;
typedef stl::list<TForm*> TModalFormsList;

//-------------------------------------------------------------------
class TCanvas;
class TSkin;
class N_PUBLIC TScreen : public TWinControl
{
	friend class TControl;

	/// Captured control
	TControl* CapturedControl;
	/// Control that the mouse events are passed to
	TControl* ControlUnderCursor;
	/// Visible menu
	TMenu* VisibleMenu;
	/// Mouse position
	TPoint MousePosition;
	/// Shift state
	TShiftState ShiftState;
	/// File server
	TFileServer* FileServer;
	/// Graphics server
	TGfxServer* GfxServer;
	/// Forms list
	TModalFormsList* FormsList;
	/// Modal forms list
	TModalFormsList* ModalFormsList;

public:
	static TScreen* Singleton;
	
public:
	TScreen();
	virtual ~TScreen();	
	virtual bool Create(const TRect& Rect);
	virtual void Close(void);
	virtual void Run(void);
	virtual void Idle(void);

	TSkin* GetSkin(void) const { return Skin; }
	TForm* GetMainForm(void);

	void SetCapturedControl(TControl* Control) { CapturedControl = Control; }
	TControl* GetCapturedControl(void) const { return CapturedControl; }

	void SetVisibleMenu(TMenu* AVisibleMenu);
	TMenu* GetVisibleMenu(void) const;

	void InsertForm(TForm* AForm);
	void RemoveForm(TForm* AForm);

	void InsertModalForm(TForm* AModalForm);
	void RemoveModalForm(TForm* AModalForm);

	TPoint GetMousePosition(void) const { return MousePosition; }
	virtual void SetMousePosition(int X, int Y);

	TShiftState GetShiftState(void) { return ShiftState; }
	TFileServer* GetFileServer(void) const { return FileServer; }
	TGfxServer* GetGfxServer(void) const { return GfxServer; }
	
	void SetClearColor(float R, float G, float B, float A);
	void GetClearColor(float& R, float& G, float& B, float& A);
	
	/// Process an incoming input message (mouse, keyboard,)
	void HandleInputMessage(TMessage* Message);	

	/// Set the control the mouse events are passed to
	TControl* GetControlUnderCursor(void) { return ControlUnderCursor; }

protected:	
	/// Load the skin file
	bool LoadSkin(const char* Filename);

protected:
	/// Events	
	virtual void OnPaint(void);	

private:
	void HandleMouseMessage(TWMMouse* Message);
	void HandleKeyboardMessage(TWMKey* Message);
	
	/// Set the control the mouse events are passed to
	void SetControlUnderCursor(TControl* Control) { ControlUnderCursor = Control; }
};

//-------------------------------------------------------------------
#endif


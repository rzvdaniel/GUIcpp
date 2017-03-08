#ifndef T_FORM_H
#define T_FORM_H
//-------------------------------------------------------------------
//  CLASS
//  TForm 
//
//  (C) 2002 Ricas -- R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TForm
#include "guide/ndefdllclass.h"

#ifndef T_BUTTON_H
#include "guide/button.h"
#endif

#ifndef T_CAPTIONBAR_H
#include "guide/captionbar.h"
#endif

//-------------------------------------------------------------------

class N_PUBLIC TForm : public TWinControl 
{	
	bool Main;
	int MinWidth;
	int MinHeight;
	TModalResult ModalResult;
	
protected:
	TCaptionBar* CaptionBar;	

public:
	TForm();
	virtual ~TForm();
	virtual void Create(TComponent* AOwner, const TRect& Rect, bool HasCaption);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

	void SetMain(bool Value);
	bool GetMain(void) const { return Main; }

	void SetCaption(const char* ACaption);
	void SetCaption(TString ACaption);

	TCaptionBar* GetCaptionBar(void) const { return CaptionBar; }

	void SetModalResult(TModalResult Value);
	TModalResult GetModalResult(void) const { return ModalResult; }
	TModalResult ShowModal(void);

	void SetMinWidth(int Value) { MinWidth = Value; }
	int GetMinWidth(void) const { return MinWidth; }

	void SetMinHeight(int Value) { MinHeight = Value; }
	int GetMinHeight(void) const { return MinHeight; }
	
	void Close(void);
	virtual void PaintBorders(void);

protected:
	// Events	
	virtual void OnPaint(void);	
	virtual void OnClose(void);
	virtual void OnShow(void);
	virtual void OnHide(void);
	virtual void OnSize(int AWidth, int AHeight);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);

public:
	// Event handlers
	void CMClose(void);
};

//-------------------------------------------------------------------
#endif

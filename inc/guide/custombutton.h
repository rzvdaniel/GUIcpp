#ifndef T_CUSTOMBUTTON_H
#define T_CUSTOMBUTTON_H
//-------------------------------------------------------------------
/**
	@class TCustomButton
	@brief Base class for standard buttons
	Encapsulates behavior common to all button controls
*/
#undef N_DEFINES
#define N_DEFINES TCustomButton
#include "guide/ndefdllclass.h"

#ifndef T_WINCONTROL_H
#include "guide/wincontrol.h"
#endif

enum TButtonState { bUp = 0, bDown };
enum TModalResult { mrNone=0, mrOk, mrCancel, mrAbort, mrRetry,
					mrIgnore, mrYes, mrNo, mrAll };

//-------------------------------------------------------------------
class N_PUBLIC TCustomButton : public TWinControl
{
	/// How much the caption moves when the button is pressed
	float CaptionOffset;
	/// Determines if the button is pressed or rised
	TButtonState State;		
	/// Determines whether the choosing of this button ends the modal state of a form
	TModalResult ModalResult;

public:
	TCustomButton();
	virtual ~TCustomButton();
	virtual void Create(TComponent* AOwner, TRect Rect);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);
	
	TButtonState GetState(void) const { return State; }
	
	void SetModalResult(TModalResult Value);
	TModalResult GetModalResult(void) const { return ModalResult; }

	void SetCaptionOffset(float Value);
	float GetCaptionOffset(void) const { return CaptionOffset; }

protected:
	// Events	
	virtual void OnClick(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	virtual void OnCaptureChanged(void);
	virtual void OnActivate(void);
	virtual void OnDeactivate(void);
	virtual void OnEnable(void);
	virtual void OnDisable(void);
	virtual void OnParentActivate(void);
	virtual void OnParentDeactivate(void);
};

//-------------------------------------------------------------------
#endif 


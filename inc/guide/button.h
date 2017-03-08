#ifndef T_BUTTON_H
#define T_BUTTON_H
//-------------------------------------------------------------------
/**
	@class TButton
	@brief Standard button

    If someone needs to create a new kind of button, use TCustomButton 
	instead.
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TButton
#include "guide/ndefdllclass.h"

#ifndef T_CUSTOMBUTTOM_H
#include "guide/custombutton.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TButton : public TCustomButton
{	
public:
	TButton();
	virtual ~TButton();
	virtual void Create(TComponent* AOwner, TRect Rect);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

protected:
	// Events
	virtual void OnPaint(void);	
	virtual void OnTextChanged(void);
	virtual void OnSize(int AWidth, int AHeight);
};

//-------------------------------------------------------------------
#endif 


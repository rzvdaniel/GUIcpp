#ifndef T_LISTBOX_H
#define T_LISTBOX_H
//-------------------------------------------------------------------
//  CLASS
//  TListBox
//
//  (C) 2004 Ricas -- R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TListBox
#include "guide/ndefdllclass.h"

#ifndef T_CUSTOMLISTBOX_H
#include "guide/customlistbox.h"
#endif

//-------------------------------------------------------------------
class N_PUBLIC TListBox : public TCustomListBox
{
public:
	TListBox();
	virtual ~TListBox();
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void ParseSkin(TiXmlElement* XmlElement);

	void SetScrollStyle(TScrollStyle Value);

protected:
	// Events	
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	virtual void OnActivate(void);
	virtual void OnDeactivate(void);
	virtual void OnDrawItem(int Index, const TRect& Rect, const TListBoxItemState& State);

protected:	
	virtual void OnHorzScroll(TScrollCode ScrollCode, int &ScrollPos);	
	virtual void OnVertScroll(TScrollCode ScrollCode, int &ScrollPos);
};

//-------------------------------------------------------------------
#endif

#ifndef T_SCROLLBAR_H
#define T_SCROLLBAR_H
//-------------------------------------------------------------------
//  CLASS
//  TScrollBar
//
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TScrollBar
#include "guide/ndefdllclass.h"

#ifndef T_CUSTOMBUTTON_H
#include "guide/custombutton.h"
#endif

#ifndef T_TEXTURE_H
#include "guide/texture.h"
#endif

//-------------------------------------------------------------------

enum TScrollButtonKind { sbMin, sbMax };
enum TScrollBarKind { sbHorizontal, sbVertical };
enum TScrollCode { scLineUp, scLineDown, scPageUp, scPageDown, 
	scPosition, scTrack, scTop, scBottom, scEndScroll };

typedef CBFunctor2<TScrollCode, int&> TScrollEvent;

//-------------------------------------------------------------------

class N_PUBLIC TScrollButton : public TCustomButton
{
	TScrollButtonKind Kind;

public:
	TScrollButton();
	virtual ~TScrollButton() {}
	virtual void Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind);
		
    TScrollButtonKind GetKind(void) const { return Kind; }
    
protected:	
	// Events
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
};

//-------------------------------------------------------------------
class N_PUBLIC TScrollButtonMinHorz : public TScrollButton
{
public:
	TScrollButtonMinHorz() {}
	virtual ~TScrollButtonMinHorz() {}
	virtual void Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind);
};

//-------------------------------------------------------------------
class N_PUBLIC TScrollButtonMaxHorz : public TScrollButton
{
public:
	TScrollButtonMaxHorz() {}
	virtual ~TScrollButtonMaxHorz() {}
	virtual void Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind);
};

//-------------------------------------------------------------------
class N_PUBLIC TScrollButtonMinVert : public TScrollButton
{
public:
	TScrollButtonMinVert() {}
	virtual ~TScrollButtonMinVert() {}
	virtual void Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind);
};

//-------------------------------------------------------------------
class N_PUBLIC TScrollButtonMaxVert : public TScrollButton
{
public:
	TScrollButtonMaxVert() {}
	virtual ~TScrollButtonMaxVert() {}
	virtual void Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind);
};

//-------------------------------------------------------------------
class N_PUBLIC TScrollThumb : public TWinControl
{
	int MouseX;
	int MouseY;
	int MinSize;
	int Size;

public:
	TScrollThumb();
	virtual ~TScrollThumb() {}
	virtual void Create(TComponent* AOwner, TRect Rect);
	virtual void ParseSkin(TiXmlElement* XmlElement);
	
	void SetPosition(int Value);
	int GetPosition(void) const;

	void SetMinSize(int Value);
	int GetMinSize(void) const { return MinSize; }

	void SetSize(int Value);
	int GetSize(void) const { return Size; }

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);
};

//-------------------------------------------------------------------
class N_PUBLIC TScrollThumbHorz : public TScrollThumb
{
public:
	TScrollThumbHorz() {}
	virtual ~TScrollThumbHorz() {}
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void Create(TComponent* AOwner, TRect Rect);
};

//-------------------------------------------------------------------
class N_PUBLIC TScrollThumbVert : public TScrollThumb
{
public:
	TScrollThumbVert() {}
	virtual ~TScrollThumbVert() {}
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);
	virtual void Create(TComponent* AOwner, TRect Rect);
};

//-------------------------------------------------------------------
class N_PUBLIC TScrollBar : public TWinControl
{	
	bool Tracking;

private:
	int Min;
	int Max;
	int Position;
	int LargeChange;
	int SmallChange;
	TScrollBarKind Kind;

protected:
	TScrollButton* MinButton;
	TScrollButton* MaxButton;
	TScrollThumb* Thumb;

public:
	TScrollEvent FOnScroll;

public:
	TScrollBar();
	virtual ~TScrollBar();
	virtual void Create(TComponent* AOwner, TRect Rect, TScrollBarKind BarKind);
	virtual void Assign(TObject* Object);
	virtual void ApplySkin(TObject* Object);

	TScrollButton* GetMinButton(void) const { return MinButton; }
	TScrollButton* GetMaxButton(void) const { return MaxButton; }
	TScrollThumb* GetThumb(void) const { return Thumb; }

	void SetMin(int Value);
	int GetMin(void) const { return Min; }

	void SetMax(int Value);
	int GetMax(void) const { return Max; }

	void SetPosition(int Value);
	int GetPosition(void) const { return Position; }
	
	int GetNumPositions(void) const { return Max - Min; }

	void SetKind(TScrollBarKind Value);
	TScrollBarKind GetKind(void) const { return Kind; }

	void SetLargeChange(int Value) { LargeChange = Value; }
	int GetLargeChange(void) const { return LargeChange; }

	void SetSmallChange(int Value) { SmallChange = Value; }
	int GetSmallChange(void) const { return SmallChange; }

	void SetTracking(bool Value) { Tracking = Value; }
	bool GetTracking(void) const { return Tracking; }

    int GetMaxThumbSize(void) const;
	void Reset(void);

public:
	// Event handlers
	virtual void CMScroll(TScrollCode ScrollCode, int ScrollPos);
    
protected:
	// Events	
	virtual void OnPaint(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnSize(int AWidth, int AHeight);
	virtual void OnScroll(TScrollCode ScrollCode, int &ScrollPos);	
	virtual void OnActivate(void);
};

//-------------------------------------------------------------------
#endif 


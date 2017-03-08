#define N_IMPLEMENTS TScrollBar
//-------------------------------------------------------------------
//  scrollbar.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/scrollbar.h"
#include "guide/skin.h"
#include "guide/scrollwinctrl.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TScrollButton class methods
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//  TScrollButton()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
TScrollButton::TScrollButton()
{
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TScrollButton::Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind)
{
	TCustomButton::Create(AOwner, Rect);
	
	Kind = BtnKind;	
}

//-------------------------------------------------------------------
//  OnPaint()
//  20-Aug-2004   rzv   created
//-------------------------------------------------------------------
void TScrollButton::OnPaint(void)
{	 
    if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
    
    TCustomButton::OnPaint();		
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  26-May-2003   rzv   created
//-------------------------------------------------------------------
void TScrollButton::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TScrollCode ScrollCode;
	if(Kind == sbMin)
		ScrollCode = scLineUp;
	else 
		ScrollCode = scLineDown;
		
	// Notify the parent scrollbar that we're scrolling it
	TScrollBar* ScrollBar = (TScrollBar*)GetParent();
	ScrollBar->CMScroll(ScrollCode, 0);

	TCustomButton::OnMouseDown(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  Create()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollButtonMinHorz::Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind)
{
	TScrollButton::Create(AOwner, Rect, BtnKind);
		
	ApplySkin(Skin->ScrollButtonMinHorz);
}

//-------------------------------------------------------------------
//  Create()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollButtonMaxHorz::Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind)
{
	TScrollButton::Create(AOwner, Rect, BtnKind);
		
	ApplySkin(Skin->ScrollButtonMaxHorz);
}

//-------------------------------------------------------------------
//  Create()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollButtonMinVert::Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind)
{
	TScrollButton::Create(AOwner, Rect, BtnKind);
		
	ApplySkin(Skin->ScrollButtonMinVert);
}

//-------------------------------------------------------------------
//  Create()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollButtonMaxVert::Create(TComponent* AOwner, const TRect& Rect, TScrollButtonKind BtnKind)
{
	TScrollButton::Create(AOwner, Rect, BtnKind);
		
	ApplySkin(Skin->ScrollButtonMaxVert);
}

//-------------------------------------------------------------------
//  TScrollThumb class methods
//-------------------------------------------------------------------



//-------------------------------------------------------------------
//  TScrollThumb()
//  28-May-2003   rzv   created
//-------------------------------------------------------------------
TScrollThumb::TScrollThumb()
{	
	MinSize = 0;
	Size = 0;
}

//-------------------------------------------------------------------
//  Create()
//  15-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::Create(TComponent* AOwner, TRect Rect)
{	
	TWinControl::Create(AOwner, TRect(0, 0, 16, 16));  
}

//-------------------------------------------------------------------
//  Create()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollThumbHorz::Create(TComponent* AOwner, TRect Rect)
{	
	TScrollThumb::Create(AOwner, TRect(0, 0, 16, 16));
    
    ApplySkin(Skin->ScrollThumbHorz);

	SetCurrentGrid(GetGrid("Horizontal"));
}

//-------------------------------------------------------------------
//  Create()
//  27-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollThumbVert::Create(TComponent* AOwner, TRect Rect)
{	
	TScrollThumb::Create(AOwner, TRect(0, 0, 16, 16));
    
    ApplySkin(Skin->ScrollThumbVert);

	SetCurrentGrid(GetGrid("Vertical")); 
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TScrollThumbHorz::Assign(TObject* Object)
{
	TScrollThumb::Assign(Object);
}

//-------------------------------------------------------------------
void TScrollThumbHorz::ApplySkin(TObject* Object)
{
	TScrollThumb::ApplySkin(Object);

	TScrollThumbHorz* AControl = (TScrollThumbHorz*)Object;
	if(AControl != NULL)
	{
		SetMinSize(AControl->GetMinSize());
	}
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TScrollThumbVert::Assign(TObject* Object)
{
	TScrollThumb::Assign(Object);
}

//-------------------------------------------------------------------
void TScrollThumbVert::ApplySkin(TObject* Object)
{
	TScrollThumb::ApplySkin(Object);

	TScrollThumbVert* AControl = (TScrollThumbVert*)Object;
	if(AControl != NULL)
	{
		SetMinSize(AControl->GetMinSize());
	}
}

//-------------------------------------------------------------------
//  SetMinSize()
//  25-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::SetMinSize(int Value)
{
	if(MinSize != Value)
		MinSize = Value;
}

//-------------------------------------------------------------------
//  SetSize()
//  25-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::SetSize(int Value)
{
    TScrollBar* ScrollBar = (TScrollBar*)GetParent();
    TScrollButton* MaxBtn = ScrollBar->GetMaxButton();
    TScrollButton* MinBtn = ScrollBar->GetMinButton();
    
    if(Size != Value)
    {
        Size = Value;
        
        // We have a minimum size, because we don't want
        // different graphic parts of the thumb (rows,
        // cells) to overlap when we paint the control
        if(Size < MinSize)
            Size = MinSize;
	    
        // We also have a maximum size because the thumb
        // can not overlap the bounds of the parent scrollbar
        
        int Sz = Size;
	    if(ScrollBar->GetKind() == sbHorizontal)
	    {
	        if(Sz > ScrollBar->GetWidth() - MinBtn->GetWidth() - MaxBtn->GetWidth())
                Sz = ScrollBar->GetWidth() - MinBtn->GetWidth() - MaxBtn->GetWidth();
            
            SetWidth(Sz);	
            SetHeight(ScrollBar->GetHeight());
        }
	    else
	    {
	        if(Sz > ScrollBar->GetHeight() - MinBtn->GetHeight() - MaxBtn->GetHeight())
                Sz = ScrollBar->GetHeight() - MinBtn->GetHeight() - MaxBtn->GetHeight();
            
		    SetHeight(Sz);
		    SetWidth(ScrollBar->GetWidth());
	    }
     }
}

//-------------------------------------------------------------------
//  SetPosition()
//  Set the position of the thumb relative to the scrollbar min btn
//  17-Dec-2003   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::SetPosition(int Value)
{
	TScrollBar* ScrollBar = (TScrollBar*)GetParent();
	
	int Pos = Value;
	
	if(Pos < 0)
	    Pos = 0;
	else if(Pos > ScrollBar->GetMaxThumbSize() - Size)
	    Pos = ScrollBar->GetMaxThumbSize() - Size;
	    
	if(ScrollBar->GetKind() == sbHorizontal)
	{   	   
        SetTop(0);
		SetLeft(Pos + ScrollBar->GetMinButton()->GetWidth());	
	}
	else
	{   
        SetLeft(0);
		SetTop(Pos + ScrollBar->GetMinButton()->GetHeight());	
	}
}

//-------------------------------------------------------------------
//  GetPosition()
//  Returns the position of the thumb relative to the scrollbar min btn
//  18-Dec-2003   rzv   created
//-------------------------------------------------------------------
int TScrollThumb::GetPosition(void) const 
{
	TScrollBar* ScrollBar = (TScrollBar*)GetParent();
	
	if(ScrollBar->GetKind() == sbHorizontal)
		return GetLeft() - ScrollBar->GetMinButton()->GetWidth();  
	else
		return GetTop() - ScrollBar->GetMinButton()->GetHeight();  

	return 0; 
}

//-------------------------------------------------------------------
//  OnPaint()
//  15-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::OnPaint(void) 
{	
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	TWinControl::OnPaint();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  28-May-2003   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	ControlToScreen(X, Y);

	MouseX = X; 
	MouseY = Y;

	TControl::OnMouseDown(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseUp()
//  28-May-2003   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	ControlToScreen(X, Y);

	MouseX = X; 
	MouseY = Y;

	TControl::OnMouseUp(Button, Shift, X, Y);
}

//-------------------------------------------------------------------
//  OnMouseMove()
//  28-May-2003   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::OnMouseMove(const TShiftState& Shift, int X, int Y)
{
	TControl::OnMouseMove(Shift, X, Y);

	if(GetCaptured())
	{
		// Convert the control coordinates X, Y to screen coordinates
		ControlToScreen(X, Y);

		int DX = MouseX - X; 
		int DY = MouseY - Y;
		
		// Store the old position of the thumb for later use
		int OldPosition = GetPosition();
		
		TScrollBar* ScrollBar = (TScrollBar*)GetParent();

		// Set the new position
		if(ScrollBar->GetKind() == sbHorizontal)
			SetPosition(GetPosition() - DX);
		else
			SetPosition(GetPosition() - DY);
		
		// If we have a new thumb position and if we have scrollbar positions
		if(OldPosition != GetPosition() && ScrollBar->GetNumPositions() != 0)
	    {
			// Calculate the offset we'll use to find the right position
			// we'll pass to the scroll bar
	        int Offset = (ScrollBar->GetMaxThumbSize() - Size) / ScrollBar->GetNumPositions();
            
			if(Offset != 0)
            {
				// Get the position where we'll scroll the scrollbar
				// This should be into the [Min , Max] range
                div_t Pos = div(GetPosition(), Offset);
				
				// Scroll the scrollbar
                ScrollBar->CMScroll(scTrack, Pos.quot);
            }
        }
			
		MouseX = X; 
		MouseY = Y;
	}
}

//-------------------------------------------------------------------
//  ParseSkin()
//  24-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollThumb::ParseSkin(TiXmlElement* XmlElement)
{	
	TWinControl::ParseSkin(XmlElement);
	
	const char *value = NULL;

	// Set the minimum size the thumb can have
	value = XmlElement->Attribute("MinSize");
	if(value != NULL)
		sscanf(value, "%d", &MinSize);
}

//-------------------------------------------------------------------
//  TScrollBar class methods
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//  TScrollBar()
//  15-May-2003   rzv   created
//-------------------------------------------------------------------
TScrollBar::TScrollBar()
{	
	Min = 0;
	Max = 0;
	Position = 0;
	SmallChange = 1;	
	LargeChange = 1;
	Kind = sbVertical;
	Tracking = true;
	MinButton = NULL;
	MaxButton = NULL;
	Thumb = NULL;
}

//-------------------------------------------------------------------
//  ~TScrollBar()
//  15-May-2003   rzv   created
//-------------------------------------------------------------------
TScrollBar::~TScrollBar()
{	
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TScrollBar::Create(TComponent* AOwner, TRect Rect, TScrollBarKind BarKind)
{	
	TWinControl::Create(AOwner, TRect(0, 0, 16, 16));
	
	ApplySkin(Skin->ScrollBar);
	
	int W;
	int H;
    
    if(BarKind == sbHorizontal)
    {
	    // Create the min button
		W = Skin->ScrollButtonMinHorz->GetWidth();
		H = Skin->ScrollButtonMinHorz->GetHeight();
		W = (W != 0 ? W : GetWidth());
		H = (H != 0 ? H : GetHeight());
	    MinButton = new TScrollButtonMinHorz;
	    MinButton->Create(this, TRect(0, 0, W, H), sbMin);

	    // Create the max button
		W = Skin->ScrollButtonMaxHorz->GetWidth();
		H = Skin->ScrollButtonMaxHorz->GetHeight();
		W = (W != 0 ? W : GetWidth());
		H = (H != 0 ? H : GetHeight());
	    MaxButton = new TScrollButtonMaxHorz;
	    MaxButton->Create(this, TRect(0, 0, W, H), sbMax);

		// Create the thumb
		Thumb = new TScrollThumbHorz;
		Thumb->Create(this, TRect(0, 0, 0, 0));
    }
    else
    {
	    // Create the min button
		W = Skin->ScrollButtonMinVert->GetWidth();
		H = Skin->ScrollButtonMinVert->GetHeight();
		W = (W != 0 ? W : 16);
		H = (H != 0 ? H : 16);
	    MinButton = new TScrollButtonMinVert;
	    MinButton->Create(this, TRect(0, 0,  W, H), sbMin);
	
	    // Create the max button
		W = Skin->ScrollButtonMaxVert->GetWidth();
		H = Skin->ScrollButtonMaxVert->GetHeight();
		W = (W != 0 ? W : 16);
		H = (H != 0 ? H : 16);
	    MaxButton = new TScrollButtonMaxVert;
	    MaxButton->Create(this, TRect(0, 0,  W, H), sbMax);

		// Create the thumb
		Thumb = new TScrollThumbVert;
		Thumb->Create(this, TRect(0, 0, 0, 0));
    }
    
	// Set kind of scrollbar
	SetKind(BarKind);
	
	// Don't show the scrollbar, yet.
	SetVisible(false);
    
	if(Kind == sbHorizontal) 
		SetCurrentGrid(GetGrid("Horizontal"));
    else
		SetCurrentGrid(GetGrid("Vertical"));
}

//-------------------------------------------------------------------
//  Assign()
//  15-Oct-2004   rzv   created
//-------------------------------------------------------------------
void TScrollBar::Assign(TObject* Object)
{
	TWinControl::Assign(Object);
}

//-------------------------------------------------------------------
void TScrollBar::ApplySkin(TObject* Object)
{
	TWinControl::ApplySkin(Object);
}

//-------------------------------------------------------------------
//  SetKind()
//  10-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollBar::SetKind(TScrollBarKind Value)
{
	if(Kind != Value)
		Kind = Value;

	if(Kind == sbVertical) 
	{
		SetAlign(alRight);

		MinButton->SetAlign(alTop);
		MaxButton->SetAlign(alBottom);
 	}
	else
	{	
		SetAlign(alBottom);

		MinButton->SetAlign(alLeft);
		MaxButton->SetAlign(alRight);
 	}  
 	
    Thumb->SetPosition(0);
 	Thumb->SetSize(GetMaxThumbSize());
}

//-------------------------------------------------------------------
//  SetMin()
//  09-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollBar::SetMin(int Value) 
{ 
	if(Min != Value)
		Min = Value; 
}

//-------------------------------------------------------------------
//  SetMax()
//  09-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollBar::SetMax(int Value) 
{ 
	if(Max != Value)
		Max = Value; 
}

//-------------------------------------------------------------------
//  SetPosition()
//  10-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollBar::SetPosition(int Value)
{
	CMScroll(scPosition, Value);
}

//-------------------------------------------------------------------
//  Reset()
//  29-Sep-2004   rzv   created
//-------------------------------------------------------------------
void TScrollBar::Reset(void)
{
	Min = 0;
	Max = 0;
	Position = 0;

	Thumb->SetPosition(0);
 	Thumb->SetSize(GetMaxThumbSize());
}

//-------------------------------------------------------------------
//  GetMaxThumbSize()
//  17-Sep-2004   rzv   created
//-------------------------------------------------------------------
int TScrollBar::GetMaxThumbSize(void) const
{
    int Value = 0;
    
    if(Kind == sbHorizontal)
        Value = GetWidth() - MinButton->GetWidth() - MaxButton->GetWidth();
    else
	    Value = GetHeight() - MinButton->GetHeight() - MaxButton->GetHeight();
    
    return Value;
}

//-------------------------------------------------------------------
//  CMScroll()
//  26-May-2003   rzv   created
//-------------------------------------------------------------------
void TScrollBar::CMScroll(TScrollCode ScrollCode, int ScrollPos)
{
	OnScroll(ScrollCode, ScrollPos);

    // Give a chance to the user to modify himself the position of 
	// the thumb tab the way he wants
	if(FOnScroll)
		FOnScroll(ScrollCode, ScrollPos);
	
	// Set the position
	Position = ScrollPos;
	
	// Update the thumb position, if we're not tracking it
	if(ScrollCode != scTrack)
	{
        if((Max - Min) != 0)
        {
            int Offset = (GetMaxThumbSize() - Thumb->GetSize()) / (Max - Min);
            
            // Adjust the position of thumb on the scrollbar
            Thumb->SetPosition(Position * Offset);
        }
     }
}

//-------------------------------------------------------------------
/**
	OnScroll event occurs when the user scrolls the scroll bar.
*/
//-------------------------------------------------------------------
void TScrollBar::OnScroll(TScrollCode ScrollCode, int &ScrollPos)
{
	int NewPos = Position;

	switch(ScrollCode)
	{
		case scLineUp:
			NewPos -= SmallChange;
			break;
		case scLineDown:
			NewPos += SmallChange;
			break;
		case scPageUp:
			NewPos -= LargeChange;
			break;
		case scPageDown:
			NewPos += LargeChange;
			break;
		case scPosition:
		case scTrack:
			NewPos = ScrollPos;
			break;
		case scTop:
			NewPos = Min;
			break;
		case scBottom:
			NewPos = Max;
			break;
	}

	if(NewPos < Min)
		NewPos = Min;
	if(NewPos > Max)
		NewPos = Max;
	
	ScrollPos = NewPos;
}

//-------------------------------------------------------------------
//  OnPaint()
//  15-May-2003   rzv   created
//-------------------------------------------------------------------
void TScrollBar::OnPaint(void) 
{	
	if(GetCurrentGrid() != NULL)
		GetCurrentGrid()->Paint(Canvas);
	
	TWinControl::OnPaint();
}

//-------------------------------------------------------------------
//  OnSize()
//  04-June-2003   rzv   created
//-------------------------------------------------------------------
void TScrollBar::OnSize(int AWidth, int AHeight)
{
	TWinControl::OnSize(AWidth, AHeight);	
}

//-------------------------------------------------------------------
//  OnActivate()
//  18-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TScrollBar::OnActivate(void)
{
	TWinControl* CtrlParent = (TWinControl*)GetParent();
	
	if(CtrlParent != NULL)
		CtrlParent->SetActiveControl(NULL);

	TWinControl::OnActivate();
}

//-------------------------------------------------------------------
//  OnMouseDown()
//  09-June-2003   rzv   created
//-------------------------------------------------------------------
void TScrollBar::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	TWinControl::OnMouseDown(Button, Shift, X, Y);

	if(Kind == sbVertical)
	{
		if(Y < Thumb->GetPosition() + MinButton->GetHeight())
			CMScroll(scPageUp, 0);
		else
			CMScroll(scPageDown, 0);
	}
	else
	{
		if(X < Thumb->GetPosition() + MinButton->GetWidth())
			CMScroll(scPageUp, 0);
		else
			CMScroll(scPageDown, 0);
	}
}


//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

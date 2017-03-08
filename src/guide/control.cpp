#define N_IMPLEMENTS TControl
//-------------------------------------------------------------------
//  control.cpp
//  (C) 2002 R.Predescu
//-------------------------------------------------------------------
#include <time.h>
#include <algorithm>
#include "guide/control.h"
#include "guide/screen.h"
#include "guide/skin.h"
#include "guide/menu.h"
#include "guide/menupopup.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TControl()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
TControl::TControl()
{
	Visible = true;		
	Enabled = true;
	Captured = false;
	Clicking = false;
	DoubleClicking = false;
	ParentFont = true;
	CastShadows = false;
	Left = 0;
	Top	= 0;
	Width = 0;
	Height = 0;
	CaptionX = 0;
	CaptionY = 0;	
	CaptionWidth = 0;
	CaptionHeight = 0;	
	LastTime = 0;
	LastPosition = TPoint(0, 0);
	BorderWidth = 0;
	BorderColor = clGray;
	Parent = NULL;
	Controls = NULL;
	Font = NULL;
	Canvas = NULL;
	MouseCursor = NULL;	
	Screen = NULL;
	Skin = NULL;
	CurrentGrid = NULL;
	PopupMenu = NULL;
	Align = alNone;
	Color = clWhite;
	ColorCaption = clBlack;
	ColorCaptionEnabled = clBlack;
	ColorCaptionDisabled = clBlack;
	ColorSelection = clLtGray;
	Margins = TRect(0, 0, 0, 0);
	MarginsText = TRect(0, 0, 0, 0);
}

//-------------------------------------------------------------------
//  ~TControl()
//  17-Jun-2002   rzv   created
//-------------------------------------------------------------------
TControl::~TControl() 
{
	if(Canvas != NULL)	
		delete Canvas;

	TControl* CtrlParent = (TControl*)GetParent();
	if(CtrlParent != NULL)
		CtrlParent->RemoveControl(this);

	DestroyControls();
	DestroyGrids();
}

//-------------------------------------------------------------------
/**
	This function is called automatically by derived classes.

	@param AOwner The owner of the control.
	@param Rect Bounding rectangle of the control.
*/
//-------------------------------------------------------------------
void TControl::Create(TComponent* AOwner, const TRect& Rect)
{
	Screen = TScreen::Singleton;
	Skin = Screen->GetSkin();

	TComponent* ComponentOwner = NULL;
	if(AOwner != NULL)
		ComponentOwner = (TComponent*)AOwner;
	else
		ComponentOwner = Screen;

	TComponent::Create(ComponentOwner);

	TControl* ControlOwner = NULL;
	if(AOwner != NULL)
		ControlOwner = (TControl*)AOwner;
	else
		ControlOwner = Screen;

	ControlOwner->InsertControl(this);

	if(!ControlOwner->GetFont())
		SetFont(Skin->GetDefaultFont());
	else
		SetFont(ControlOwner->GetFont());
	
	Anchors.insert(akTop);
	Anchors.insert(akLeft);

	Canvas = new TCanvas(this);

	SetBounds(Rect.left, Rect.top, Rect.right, Rect.bottom);
}

//-------------------------------------------------------------------
/**
	@brief Get properties of the passed object and assign 
	them to our one.
*/
//-------------------------------------------------------------------
void TControl::Assign(TObject* Object)
{
	TControl* AControl = (TControl*)Object;
	if(!AControl)
		return;

	SetBounds(AControl->GetBounds());
}

//-------------------------------------------------------------------
/**
	@brief Applies skin properties to the control. Default control
	properties will be over written if the skin contains valid values
	for these properties.

	@param Object Skin object containing the properties to be assigned
	to the control
*/
//-------------------------------------------------------------------
void TControl::ApplySkin(TObject* Object)
{
	TControl* AControl = (TControl*)Object;
	if(!AControl)
		return;

	if(Width == 0)
	{
		if(AControl->GetWidth() != 0)
			SetWidth(AControl->GetWidth());
	}

	if(Height == 0)
	{
		if(AControl->GetHeight() != 0)
			SetHeight(AControl->GetHeight());
	}

	SetColor(AControl->GetColor());
	SetCaptionColor(AControl->GetCaptionColor());
	SetCaptionColorEnabled(AControl->GetCaptionColorEnabled());
	SetCaptionColorDisabled(AControl->GetCaptionColorDisabled());
	SetSelectionColor(AControl->GetSelectionColor());
	SetGrids(AControl->GetGrids());
	SetMouseCursor(AControl->GetMouseCursor());
	SetBorderColor(AControl->GetBorderColor());
	SetBorderWidth(AControl->GetBorderWidth());
	SetCastShadows(AControl->GetCastShadows());
	SetMargins(AControl->GetMargins());
	SetTextMargins(AControl->GetTextMargins());
}

//-------------------------------------------------------------------
//  InsertControl()                                 
//  30-July-2002   rzv   created                    
//-------------------------------------------------------------------
void TControl::InsertControl(TControl* Control)     
{                                                    	
	if(Control != NULL) 
	{
		if(Controls == NULL)							
			Controls = new TControlsList;  
		
		Control->Parent = this;
		Controls->push_back(Control);
	}
}													
													
//-------------------------------------------------------------------
//  RemoveControl()                                 
//  30-July-2002   rzv   created                    
//-------------------------------------------------------------------
void TControl::RemoveControl(TControl* Control)      
{
	if(Controls != NULL)
	{
		if(Control != NULL) 
		{
			Controls->remove(Control);
			Control->Parent = NULL;
		}

		if(Controls->empty()) 
		{                          
			delete Controls;             
			Controls = NULL;
		}
	}
}

//-------------------------------------------------------------------
//  DestroyControls()
//  30-Jun-2002   rzv   created
//-------------------------------------------------------------------
void TControl::DestroyControls(void)
{
	TControl* Control = NULL;
	while(Controls != NULL) 
	{
		Control = Controls->back(); 	
		RemoveControl(Control);

		TComponent* CtrlOwner = (TComponent*)Control->GetOwner();
		if(CtrlOwner != NULL)
			CtrlOwner->RemoveComponent((TComponent*)Control);

		delete Control;
	} 
}

//-------------------------------------------------------------------
/**
	A recursive search within all children is performed. 

	@param AName	Name of the control to be retrieved.
	@return			Pointer to the control with the specified name, 
					if any, or <code>NULL</code> if no control was found.
*/
//-------------------------------------------------------------------
TControl* TControl::GetControl(TString AName)
{
	if(Controls != NULL)
	{
		TControlsList::iterator iter;
		for(iter = Controls->begin(); iter != Controls->end(); iter++)
		{
			TControl* Control = (TControl*)(*iter);
			TControl* Ctrl = Control->GetControl(AName);
			if(Ctrl != NULL)
				return Ctrl;
		}
	}

	if(!AName.compare(GetName())) 
		return this;

	return NULL;
}

//-------------------------------------------------------------------
/**
	Only search for direct children.

	@param AName	Name of the control to be retrieved.
	@return			Pointer to the control with the specified name, 
					if any, or <code>NULL</code> if no control was found.
*/
//-------------------------------------------------------------------
TControl* TControl::GetChild(TString AName) const
{
	if(Controls != NULL)
	{
		TControlsList::iterator iter;
		for(iter = Controls->begin(); iter != Controls->end(); iter++)
		{
			TControl* Control = (TControl*)(*iter);
			
			if(!AName.compare(Control->GetName())) 
				return Control;
		}
	}
			
	return NULL;
}

//-------------------------------------------------------------------
/**
	Usually the parent of the control is the same as its owner, but it 
	also happens to be different. For example, forms are very often 
	owners of the controls they're containing, but not necessary their 
	parent.

    @param AParent The new parent of the control.
	@note This will not change the owner of the control. The owner
	of a control is specified at control's creation time.
*/
//-------------------------------------------------------------------
void TControl::SetParent(TControl* AParent) 
{
	t_assert(AParent != this);

	if(Parent != NULL)
		Parent->RemoveControl(this);
				
	if(AParent != NULL)
		AParent->InsertControl(this);

	// First, update control rect (used by ClipRect)
	UpdateControlRect();
		
	// Second, update clip rect
	UpdateClipRect();
}

//-------------------------------------------------------------------
/**
	Attach a list of grids to the control.

    Grids are used to set the look of the controls. Usually controls
	have different grids for different states. For example, a button
	can have one grid for its normal look, one for its pressed state,
	for mouse over or for disabled state.

    @param AGrids List of grids we want to attach to the control.
*/
//-------------------------------------------------------------------
void TControl::SetGrids(TGridsList AGrids) 
{ 
	TGridsList::iterator iter;
	for(iter = AGrids.begin(); iter != AGrids.end(); iter++)
	{
		TGrid* Grid = (TGrid*)(*iter).second;
		TGrid* NewGrid = new TGrid;
		NewGrid->Assign(Grid);
		Grids[NewGrid->GetName()] = NewGrid;
	}
       
    UpdateGrids();
}

//-------------------------------------------------------------------
/**
	Retrieve the specified grid the control is containing.

    @param AName Name of the grid we want to obtain.
	@return The specified grid, if any, or NULL if no grid was found.
*/
//-------------------------------------------------------------------
TGrid* TControl::GetGrid(const char* AName)
{            
     TGridsList::iterator iter = Grids.find(TString(AName));
     if(iter != Grids.end())
		 return iter->second;
              
     return NULL;
}

//-------------------------------------------------------------------
//  DestroyGrids()
//  20-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::DestroyGrids(void)
{
	TGridsList::iterator iter; 
	for(iter = Grids.begin(); iter != Grids.end(); iter++)   
		 delete (*iter).second;
     
	Grids.clear();
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TControl::SetMargins(const TRect& Value)
{
	if(Margins != Value)
		Margins = Value;
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TControl::SetMargins(int Left, int Top, int Right, int Bottom)
{
	SetMargins(TRect(Left, Top, Right, Bottom));
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
const TRect& TControl::GetMargins(void)
{
	return Margins;
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TControl::SetTextMargins(const TRect& Value)
{
	if(MarginsText != Value)
		MarginsText = Value;
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TControl::SetTextMargins(int Left, int Top, int Right, int Bottom)
{
	SetTextMargins(TRect(Left, Top, Right, Bottom));
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
const TRect& TControl::GetTextMargins(void)
{
	return MarginsText;
}

//-------------------------------------------------------------------
//  UpdateGrids()
//  19-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::UpdateGrids(void)
{
	TGridsList::iterator iter; 
	for(iter = Grids.begin(); iter != Grids.end(); iter++)
	{
		TGrid* Grid = (TGrid*)(*iter).second;
		Grid->SetWidth(Width);
		Grid->SetHeight(Height);
	}
}

//-------------------------------------------------------------------
/**
    @param AFont New font the control is using to render its text.
*/
//-------------------------------------------------------------------
void TControl::SetFont(TFont* AFont)
{
	if(AFont != NULL)
	{
		Font = AFont;
		CMFontChanged();
	}
}

//-------------------------------------------------------------------
/**
	@param Name Name of the font.
    @param Size Size of the font.
	@return The specified font or NULL if no font was found.
*/
//-------------------------------------------------------------------
TFont* TControl::GetFont(const char* Name, int Size)
{
	return Skin->GetFont(Name, Size);	
}

//-------------------------------------------------------------------
/**
	Tells the control to use or not its parent font when displaying 
	its own caption or text.

    @param Value <code>true</code>, if the control should use its parent
	font, <code>false</code> if the control should not use its parent font.
*/
//-------------------------------------------------------------------
void TControl::SetParentFont(bool Value)		
{ 
	if(ParentFont != Value)
		ParentFont = Value;
}

//-------------------------------------------------------------------
/**
	@param Name Name of the mouse cursor we want to obtain.
	@return The specified mouse cursor.
*/
//-------------------------------------------------------------------
void TControl::SetMouseCursor(TString Name)
{
	MouseCursor = GetMouseCursor(Name.c_str());
}

//-------------------------------------------------------------------
/**
    @param Name Name of the mouse cursor we want to obtain.
    @return The specified mouse cursor.
*/
//-------------------------------------------------------------------
TMouseCursor* TControl::GetMouseCursor(const char* Name)
{
	return Skin->GetMouseCursor(Name);	
}

//-------------------------------------------------------------------
/**
	Usual pop up menu appears when the user press the right mouse
	button.

    @param The pop up menu associated with the control.
*/
//-------------------------------------------------------------------
void TControl::SetPopupMenu(TMenu* APopupMenu) 
{ 
    PopupMenu = APopupMenu; 
}

//-------------------------------------------------------------------
/**
	If the control doesn't contains any pop up menu, nothing happens.

    @return The pop up menu associated with the control or NULL if the 
	control doesn't contains any pop up menu.
*/
//-------------------------------------------------------------------
TMenu* TControl::GetPopupMenu(void) const 
{ 
    return PopupMenu; 
}

//-------------------------------------------------------------------
/**   
	Use Caption to specify the text string that labels the control.
	
    @param ACaption Usually, the label of the control.
	@see <code>SetText</code>
*/
//-------------------------------------------------------------------
void TControl::SetCaption(const char* ACaption) 
{ 
	Caption.assign(ACaption); 
	CMTextChanged();
}

//-------------------------------------------------------------------
/**
    Use Caption to specify the text string that labels the control.
	
    @param ACaption Usually, the label of the control.
	@see <code>SetText</code>
*/
//-------------------------------------------------------------------
void TControl::SetCaption(TString ACaption) 
{ 
	SetCaption(ACaption.c_str());
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TControl::SetBorderWidth(int AWidth)
{
	BorderWidth = AWidth;
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TControl::SetBorderColor(TColor AColor)
{
	BorderColor = AColor;
}

//-------------------------------------------------------------------
/**
    For edit controls and memos, the Text appears within the control. 
	For combo boxes, the Text is the content of the edit control portion 
	of the combo box.

    @param AText The text associated with the control.
	@see <code>SetCaption</code>
*/
//-------------------------------------------------------------------
void TControl::SetText(TString AText) 
{ 
	Text.assign(AText); 
	CMTextChanged();
}

//-------------------------------------------------------------------
/**
    Use SetEnabled to change the availability of the control to the user. 
	If the control is disabled, it ignores mouse, keyboard, and timer 
	events.

    @param Value <code>true</code>, to enable the control, <code>false</code> 
	to disable the control.
	@see <code>SetVisible</code>
*/
//-------------------------------------------------------------------
void TControl::SetEnabled(bool Value)		
{ 
	if(Enabled != Value)
	{
		Enabled = Value; 

		if(Enabled == true)
			CMEnable();
		else
			CMDisable();
	}
}

//-------------------------------------------------------------------
/**
    Use anchors to ensure that a control maintains its current position 
	relative to an edge of its parent, even if the parent is resized.

    @param Anchor The anchor we want to update for the control.
    @param Value <code>true</code>, if we want to add an anchor, 
	<code>false</code> if we want to remove an anchor.
	@see <code>SetAlign</code>
*/
//-------------------------------------------------------------------
void TControl::SetAnchor(TAnchorKind Anchor, bool Value)
{
	if(Value == true)
		Anchors.insert(Anchor);
	else
		Anchors.erase(Anchor);
}

//-------------------------------------------------------------------
/**
	Returns <code>true</code> if the control has the specified anchor.

    @param Anchor The anchor we want to see if the control is containing.
	@return <code>true</code>, if the control contains the specified anchor, 
	<code>false</code> if the control doesn't contain that anchor.
	@see <code>GetAlign</code>
*/
//-------------------------------------------------------------------
bool TControl::GetAnchor(TAnchorKind Anchor) const
{
	if(Anchors.count(Anchor))
		return true;

	return false;
}

//-------------------------------------------------------------------
/**
	@see <code>SendToBack</code>
*/
//-------------------------------------------------------------------
void TControl::BringToFront(void)
{	
	SetZOrder(true);

	if(Parent != NULL)
		Parent->BringToFront();
}

//-------------------------------------------------------------------
/**
	Puts a windowed control behind all other windowed controls, or puts 
	a non-windowed control behind all other non-windowed controls.

	@see <code>BringToFront</code>
*/
//-------------------------------------------------------------------
void TControl::SendToBack(void)
{
	SetZOrder(false);
}

//-------------------------------------------------------------------
/**
	@param TopMost <code>true</code>, to make the control the topmost 
	control; <code>false</code>, to make the control the bottommost.
	@see <code>SendToBack BringToFront</code>
*/
//-------------------------------------------------------------------
void TControl::SetZOrder(bool TopMost)
{
	if(Parent != NULL) 
	{
		if(Parent->Controls != NULL) 
		{	
			Parent->Controls->remove(this);

			if(TopMost) 
				Parent->Controls->push_back(this);	
			else
				Parent->Controls->push_front(this);
		}
	}
}

//-------------------------------------------------------------------
/**
	Specifies the X and Y coordinates of the top left corner of a control, 
	relative to its parent or containing control in pixels. 

	@see <code>SetLeft</code>
	@see <code>SetTop</code>
*/
//-------------------------------------------------------------------
void TControl::SetPosition(TPoint Value) 
{ 
	SetBounds(Value.x, Value.y, Width, Height);
}

//-------------------------------------------------------------------
/**
	Specifies the X coordinate of the top left corner of a control, 
	relative to its parent or containing control in pixels. 

	@see <code>SetTop</code>
*/
//-------------------------------------------------------------------
void TControl::SetLeft(int Value) 
{ 
	SetBounds(Value, Top, Width, Height);
}

//-------------------------------------------------------------------
/**
	Specifies the Y coordinate of the top left corner of a control, 
	relative to its parent or containing control in pixels. 

	@see <code>SetLeft</code>
*/
//-------------------------------------------------------------------
void TControl::SetTop(int Value) 
{ 
	SetBounds(Left, Value, Width, Height);
}

//-------------------------------------------------------------------
/**
	@see <code>SetHeight</code>
*/
//-------------------------------------------------------------------
void TControl::SetWidth(int Value) 
{ 
	SetBounds(Left, Top, Value, Height);
}

//-------------------------------------------------------------------
/**
	@see <code>SetWidth</code>
*/
//-------------------------------------------------------------------
void TControl::SetHeight(int Value) 
{ 
	SetBounds(Left, Top, Width, Value);
}

//-------------------------------------------------------------------
/**
	This function will allow the control to receive all mouse 
	messages until another control captures the mouse by a subsequent 
	call to SetCapture().

    @note Be careful when when playing with SetCapture(): some controls 
	captures mouse events internally. 

	@see <code>ReleaseCapture</code>
*/
//-------------------------------------------------------------------
void TControl::SetCapture(void)
{
	Screen->SetCapturedControl(this);
	Captured = true;
}

//-------------------------------------------------------------------
/**
    @param Value Boolean value: true for visible, false for invisible.
	@see <code>SetCapture</code>
*/
//-------------------------------------------------------------------
void TControl::ReleaseCapture(void)
{	
	Screen->SetCapturedControl(NULL);
	Captured = false;
	CMCaptureChanged();
}

//-------------------------------------------------------------------
/**
    @param Value Boolean value: true for visible, false for invisible.
	@see <code>SetEnabled Hide Show</code>
*/
//-------------------------------------------------------------------
void TControl::SetVisible(bool Value) 
{ 	 
	if(Visible != Value)
	{
		Visible = Value;
	
		if(Visible == true)
			CMShow();
		else
			CMHide();
	}
}

//-------------------------------------------------------------------
/**
	The effect is the same as calling SetVisible(true).

	@see <code>Hide SetVisible</code>
*/
//-------------------------------------------------------------------
void TControl::Show(void)
{
	SetVisible(true);
}

//-------------------------------------------------------------------
/**
	The effect is the same as calling SetVisible(false).

	@see <code>Show SetVisible</code>
*/
//-------------------------------------------------------------------
void TControl::Hide(void)
{
	SetVisible(false);
}

//-------------------------------------------------------------------
/**
	@brief Sets the bounds of the control all at once. This will call
	OnSize() and OnMove() functions if size or position of the control
	will change.

	@param Rect A TRect structure containing size and position 
	information. Left and top are position information, right 
	and bottom are size information(width and height).
	
*/
//-------------------------------------------------------------------
void TControl::SetBounds(const TRect &Rect)
{
	SetBounds(Rect.left, Rect.top, Rect.right, Rect.bottom);
}

//-------------------------------------------------------------------
/**
	@brief Sets the bounds of the control all at once. This will call
	OnSize() and OnMove() functions if size or position of the control
	will change.

	@param ALeft Left property of the control.
	@param ARight Right property of the control.
	@param AWidth Width property of the control.
	@param AHeight Height property of the control.
*/
//-------------------------------------------------------------------
void TControl::SetBounds(int ALeft, int ATop, int AWidth, int AHeight)
{
	if((AWidth != Width) || (AHeight != Height)) 
	{
		// Inform all the child that their parent's size was changed
		if(Controls != NULL)
		{
			TControlsList::iterator iter;
			for(iter = Controls->begin(); 
				iter != Controls->end(); 
				iter++)
			{
				TControl* Control = (TControl*)(*iter);
				Control->CMParentResize(AWidth, AHeight);
			}
		}
		
		// Set the new size
		Width = AWidth;
		Height = AHeight;
		
		CMSize(AWidth, AHeight);
	}
	
	if((ALeft != Left) || (ATop != Top))
	{
		Left = ALeft;
		Top	= ATop;
		
		CMMove(ALeft, ATop);
	}
}

//-------------------------------------------------------------------
/**
	@param ALeft Left property of the control to be returned.
	@param ARight Right property of the control to be returned.
	@param AWidth Width property of the control to be returned.
	@param AHeight Height property of the control to be returned.
*/
//-------------------------------------------------------------------
void TControl::GetBounds(int& ALeft, int& ATop, int& AWidth, int& AHeight) const
{
	ALeft = Left;
	ATop = Top;
	AWidth = Width;
	AHeight = Height;
}

//-------------------------------------------------------------------
/**
	@return Left, Top, Width and Height properties as a TRect structure.
*/
//-------------------------------------------------------------------
TRect TControl::GetBounds(void) const
{
	return TRect(Left, Top, Width, Height); 
}


//-------------------------------------------------------------------
/**
	@param Rect Boundaries of the control.
*/
//-------------------------------------------------------------------
void TControl::SetBoundsRect(const TRect &Rect)
{
	SetBounds(Rect.left, 
			  Rect.top, 
			  Rect.right - Rect.left, 
			  Rect.bottom - Rect.top);
}

//-------------------------------------------------------------------
/**
	@return Bounds of the control as a TRect structure.
*/
//-------------------------------------------------------------------
TRect TControl::GetBoundsRect(void) const
{
	return TRect(Left, Top, Left + Width, Top + Height);
}

//-------------------------------------------------------------------
//  UpdateControlRect()
//  05-Apr-2003   rzv   created
//-------------------------------------------------------------------
void TControl::UpdateControlRect(void)
{
	TControl* CtrlParent = (TControl*)GetParent();

	if(CtrlParent == NULL)
	{
		// We don't have a parent, so simply build the control's rect
		ControlRect = TRect(Left, Top, Left + Width, Top + Height);
	}
	else 
	{
		ControlRect = CtrlParent->GetControlRect();
		ControlRect.left += Left;
		ControlRect.top += Top;
		ControlRect.right = ControlRect.left + Width;
		ControlRect.bottom = ControlRect.top + Height;
	}
}

//-------------------------------------------------------------------
//  UpdateClipRect()
//  28-March-2003   rzv   created
//-------------------------------------------------------------------
void TControl::UpdateClipRect(void)
{
	ClipRect = ControlRect;
	
	// Clipping rect is the  intersection of the control rect
	// with its parent clip rect
	if(Parent != NULL) 
		ClipRect.IntersectRect(ClipRect, Parent->GetClipRect());

	// Recursively update the clipping rect for all the childs
	if(Controls != NULL)
	{
		TControlsList::iterator iter;
		for(iter = Controls->begin(); iter != Controls->end(); iter++)
		{
			TControl* Control = (TControl*)(*iter);
			Control->UpdateClipRect();
		}
	}
}

//-------------------------------------------------------------------
//  PushClipRect()
//  13-Mar-2004   rzv   created
//-------------------------------------------------------------------
void TControl::PushClipRect(void)
{
	ClipRectStack.push(ClipRect);
	
	Canvas->EnableClipping();
	Canvas->ClipDrawing();
	
}

//-------------------------------------------------------------------
//  PopClipRect()
//  13-Mar-2004   rzv   created
//-------------------------------------------------------------------
void TControl::PopClipRect(void)
{	
	ClipRectStack.pop();

	if(ClipRectStack.size() != 0)
		ClipRect = ClipRectStack.top(); 

	Canvas->DisableClipping();

	Canvas->ClipDrawing();
}

//-------------------------------------------------------------------
/**
	@param Point Position we want to convert.
	@return Converted position, returned as a TPoint value.
*/
//-------------------------------------------------------------------
TPoint TControl::ScreenToControl(TPoint Point)
{
	return TPoint(Point.x - ControlRect.left, 
				  Point.y - ControlRect.top);
}

//-------------------------------------------------------------------
/**
	@param X Horizontal position.
	@param Y Vertical position.
*/
//-------------------------------------------------------------------
void TControl::ScreenToControl(int& X, int& Y)
{
	X -= ControlRect.left, 
	Y -= ControlRect.top;
}

//-------------------------------------------------------------------
/**
	@param Point Position we want to convert.
	@return Converted position, returned as a TPoint value.
*/
//-------------------------------------------------------------------
TPoint TControl::ControlToScreen(TPoint Point)
{
	return TPoint(Point.x + ControlRect.left, 
				  Point.y + ControlRect.top);
}

//-------------------------------------------------------------------
/**
	@param X Horizontal position.
	@param Y Vertical position.
*/
//-------------------------------------------------------------------
void TControl::ControlToScreen(int& X, int& Y)
{
	 X += ControlRect.left, 
	 Y += ControlRect.top;
}

//-------------------------------------------------------------------
/**
	It only searches for a child control.

	@param Point Position to find the control behind.
	@return The control at the specified position or NULL if no control
			was found.
*/
//-------------------------------------------------------------------
TControl* TControl::ControlFromPoint(const TPoint& Point)
{
	if(Controls != NULL)
	{
		// Reverse iterator for move from the end to the beginning of Controls
		TControlsList::reverse_iterator iter;
		for(iter = Controls->rbegin(); iter != Controls->rend(); iter++)
		{
			TControl* Control = (TControl*)(*iter);
			if(Control->GetVisible() && Control->GetBoundsRect().PtInRect(Point)) 
				return Control;
		}
	}
			
	return NULL;
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the last control from the aligned controls list 
	specified by the passed alignment value.

	@param Value Identify the list of aligned controls we are interested 
	to retrieve the last control from.
	@return Last aligned control or NULL if none is found.
*/
//-------------------------------------------------------------------
TControl* TControl::GetLastAlignedControl(TAlign Value)
{
	if(AlignedControls[Value].size() != 0)
		return AlignedControls[Value].back();

	return NULL;
}

//-------------------------------------------------------------------
/**
	@brief Retrieve the rectangle that is not yet filled with aligned 
	child controls. Controls that have no alignment are not taken
	into consideration.

	@return Left, Top, Right, Bottom coordinates of the empty rectangle.
*/
//-------------------------------------------------------------------
TRect TControl::GetEmptyAlignedRect(void)
{
	TRect EmptyRect(Margins.left, Margins.top, Width - Margins.left - Margins.right, Height - Margins.top - Margins.bottom);

	TControl* CtrlTop = GetLastAlignedControl(alTop);
	TControl* CtrlBottom = GetLastAlignedControl(alBottom);
	TControl* CtrlLeft = GetLastAlignedControl(alLeft);
	TControl* CtrlRight = GetLastAlignedControl(alRight);

	if(CtrlTop != NULL)
		EmptyRect.top = CtrlTop->Top + CtrlTop->Height;
	if(CtrlBottom != NULL)
		EmptyRect.bottom = CtrlBottom->Top;
	if(CtrlLeft != NULL)
		EmptyRect.left = CtrlLeft->Left + CtrlLeft->Width;
	if(CtrlRight != NULL)
		EmptyRect.right = CtrlRight->Left;

	return EmptyRect;
}

//-------------------------------------------------------------------
/**
	@param Value Alignment of the control.
*/
//-------------------------------------------------------------------
void TControl::SetAlign(TAlign Value)
{
	if(Value != Align)
	{
		RemoveAlignedControl(Align);

		AlignControl(Value);

		InsertAlignedControl(Value);

		Align = Value;
	}
}

//-------------------------------------------------------------------
//  AlignControl()
//  06-Aug-2002   rzv   created
//-------------------------------------------------------------------
void TControl::AlignControl(TAlign Value)
{
	switch(Value)
	{
		case alNone:
			AlignNone();
			break;
		case alLeft:
			AlignLeft();
			break;
		case alRight:
			AlignRight();
			break;
		case alTop:
			AlignTop();
			break;
		case alBottom:
			AlignBottom();
			break;
	}
}

//-------------------------------------------------------------------
//  AlignNone()
//  06-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::AlignNone(void)
{	
}

//-------------------------------------------------------------------
//  AlignLeft()
//  05-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::AlignLeft(void)
{
	TRect Rect = Parent->GetEmptyAlignedRect();
	SetBounds(Rect.left, Rect.top, Width, Rect.bottom - Rect.top);		
}

//-------------------------------------------------------------------
//  AlignRight()
//  05-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::AlignRight(void)
{	
	TRect Rect = Parent->GetEmptyAlignedRect();
	TRect ParentMargins = Parent->GetMargins();
	SetBounds(ParentMargins.left + Rect.right - Width, Rect.top, Width, Rect.bottom - Rect.top);		
}

//-------------------------------------------------------------------
//  AlignTop()
//  05-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::AlignTop(void)
{
	TRect Rect = Parent->GetEmptyAlignedRect();
	SetBounds(Rect.left, Rect.top, Rect.right, Height);		
}

//-------------------------------------------------------------------
//  AlignBottom()
//  05-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::AlignBottom(void)
{
	TRect Rect = Parent->GetEmptyAlignedRect();
	TRect ParentMargins = Parent->GetMargins();
	SetBounds(Rect.left, Rect.bottom - Height + ParentMargins.top, Rect.right, Height);		
}

//-------------------------------------------------------------------
//  AlignClient()
//  06-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::AlignClient(void)
{
	// Nothing yet.
}

//-------------------------------------------------------------------
//  RealignLeftList()
//  06-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::RealignLeftList(void)
{	
	TRect Rect = GetEmptyAlignedRect();
	TControlsList* ControlsList = &AlignedControls[alLeft];	
	int XOffset = 0;

	TControlsList::iterator iter;
	for(iter = ControlsList->begin(); iter != ControlsList->end(); iter++)
	{
		TControl* Control = (TControl*)(*iter);
		Control->SetBounds(XOffset + Margins.left, Rect.top + Margins.top, Control->Width, Rect.bottom - Rect.top - Margins.bottom);
		
		XOffset += Control->Width;
	}
}

//-------------------------------------------------------------------
//  RealignRightList()
//  06-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::RealignRightList(void)
{
	TRect Rect = GetEmptyAlignedRect();
	TControlsList* ControlsList = &AlignedControls[alRight];	
	int XOffset = GetWidth();

	TControlsList::iterator iter;
	for(iter = ControlsList->begin(); iter != ControlsList->end(); iter++)
	{
		TControl* Control = (TControl*)(*iter);
		Control->SetBounds(XOffset - Control->Width - Margins.right, Rect.top + Margins.top, Control->Width, Rect.bottom - Rect.top - Margins.bottom);
		
		XOffset -= Control->Width;
	}
}

//-------------------------------------------------------------------
//  RealignTopList()
//  06-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::RealignTopList(void)
{
	TControlsList* ControlsList = &AlignedControls[alTop];
	int YOffset = 0;

	TControlsList::iterator iter;
	for(iter = ControlsList->begin(); iter != ControlsList->end(); iter++)
	{
		TControl* Control = (TControl*)(*iter);
		Control->SetBounds(0 + Margins.left, YOffset + Margins.top, GetWidth() - Margins.right, Control->Height);
		
		YOffset += Control->Height;
	}	
}

//-------------------------------------------------------------------
//  RealignBottomList()
//  06-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::RealignBottomList(void)
{
	TControlsList* ControlsList = &AlignedControls[alBottom];
	int YOffset = GetHeight();

	TControlsList::iterator iter;
	for(iter = ControlsList->begin(); iter != ControlsList->end(); iter++)
	{
		TControl* Control = (TControl*)(*iter);
		Control->SetBounds(0 + Margins.left, YOffset - Control->Height - Margins.bottom, GetWidth() - Margins.right, Control->Height);
		
		YOffset -= Control->Height;
	}	
}

//-------------------------------------------------------------------
//  RealignClientList()
//  07-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::RealignClientList(void)
{
	TControlsList* ControlsList = &AlignedControls[alClient];

/*
	int YOffset = GetHeight();

	TControlsList::iterator iter;
	for(iter = ControlsList->begin(); iter != ControlsList->end(); iter++)
	{
		TControl* Control = (TControl*)(*iter);
		Control->SetBounds(0, YOffset - Control->Height, GetWidth(), Control->Height);
		
		YOffset -= Control->Height;
	}
*/
}

//-------------------------------------------------------------------
//  InsertAlignedControl()
//  01-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::InsertAlignedControl(TAlign Value)
{	
	if(Value != alNone)
	{
		// Try to find if the control isn't already present into the list
		TControlsList::iterator Where = stl::find(Parent->AlignedControls[Value].begin(), Parent->AlignedControls[Value].end(), this);

		// The control doesn't exist into the list, so it's time to add it
		if(Where == Parent->AlignedControls[Value].end())
		{
			Parent->AlignedControls[Value].push_back(this);

			if(Value == alTop || Value == alBottom)
			{
				Parent->RealignLeftList();
				Parent->RealignRightList();
			}
		}	
	}
}

//-------------------------------------------------------------------
//  RemoveAlignedControl()
//  01-May-2004   rzv   created
//-------------------------------------------------------------------
void TControl::RemoveAlignedControl(TAlign Value)
{
	if(Value != alNone)
	{
		// Try to find the control into the specified list
		TControlsList::iterator Where = stl::find(Parent->AlignedControls[Value].begin(), Parent->AlignedControls[Value].end(), this);

		// We find the control
		if(Where != Parent->AlignedControls[Value].end())
		{			
			// Remove it from the list
			Parent->AlignedControls[Value].remove(this);

			if(Value == alTop || Value == alBottom)
			{
				if(Value == alTop)
					Parent->RealignTopList();
				else
					Parent->RealignBottomList();

				Parent->RealignLeftList();
				Parent->RealignRightList();
			}

			if(Value == alLeft)
				Parent->RealignLeftList();

			if(Value == alRight)
				Parent->RealignRightList();
		
		}
	}
}

//-------------------------------------------------------------------
/**
	@brief If Click is called, any code attached to the OnClick event is 
	executed. This is useful when we want to simulate a mouse click.
*/
//-------------------------------------------------------------------
void TControl::Click(void)
{
	CMMouseClick();	
}

//-------------------------------------------------------------------
/**
	@brief This function will paint borders according with the specified 
	border width and color.
*/
//-------------------------------------------------------------------
void TControl::PaintBorders(void)
{
	if(BorderWidth)
	{
		Canvas->Pen->SetColor(BorderColor);
		Canvas->DrawRect(0, 0, GetWidth()-BorderWidth, GetHeight()-BorderWidth, BorderWidth);
	}
}

//-------------------------------------------------------------------
//  CMPaint()
//  04-July-2002   rzv    created
//-------------------------------------------------------------------
void TControl::CMPaint(void)
{
	if(Visible == true)
	{
		if(FOnPaint)
			FOnPaint();
		else
			OnPaint();
	}
}

//-------------------------------------------------------------------
//  CMMouseClick()
//  11-Sep-2003   rzv    created
//-------------------------------------------------------------------
void TControl::CMMouseClick(void)
{	
	OnClick();
	
	if(FOnClick)
		FOnClick();
}

//-------------------------------------------------------------------
//  CMMouseDoubleClick()
//  21-Dec-2003   rzv    created
//-------------------------------------------------------------------
void TControl::CMMouseDoubleClick(void)
{	
	OnDoubleClick();	
}

//-------------------------------------------------------------------
//  CMMouseDown()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TControl::CMMouseDown(TMouseButton Button, int X, int Y)
{
	if(GetEnabled() == false)
		return;

	TPoint Point = ScreenToControl(TPoint(X, Y));
	TControl* ChildCtrl = ControlFromPoint(Point);
	if(ChildCtrl != NULL)
	{
		ChildCtrl->CMMouseDown(Button, X, Y);
		return;
	}

	Screen->SetControlUnderCursor(this);

	OnMouseDown(Button, Screen->GetShiftState(), Point.x, Point.y);	

	if(FOnMouseDown)
		FOnMouseDown(Button, Screen->GetShiftState(), X, Y);

}

//-------------------------------------------------------------------
//  CMMouseUp()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TControl::CMMouseUp(TMouseButton Button, int X, int Y)
{
	if(GetEnabled() == false)
		return;

	TPoint Point = ScreenToControl(TPoint(X, Y));
	TControl* ChildCtrl = ControlFromPoint(Point);
	if(ChildCtrl != NULL)
	{
		ChildCtrl->CMMouseUp(Button, X, Y);
		return;
	}

	Screen->SetControlUnderCursor(this);

	OnMouseUp(Button, Screen->GetShiftState(), Point.x, Point.y);
	
	if(FOnMouseUp)
		FOnMouseUp(Button, Screen->GetShiftState(), X, Y);
}

//-------------------------------------------------------------------
//  CMMouseMove()
//  10-July-2002   rzv    created
//-------------------------------------------------------------------
void TControl::CMMouseMove(int X, int Y)
{
	if(GetEnabled() == false)
		return;

	TPoint Point = ScreenToControl(TPoint(X, Y));
	TControl* ChildCtrl = ControlFromPoint(Point);
	if(ChildCtrl != NULL)
	{
		ChildCtrl->CMMouseMove(X, Y);
		return;
	}

	Screen->SetControlUnderCursor(this);

	OnMouseMove(Screen->GetShiftState(), Point.x, Point.y);
	
	if(FOnMouseMove)
		FOnMouseMove(Screen->GetShiftState(), X, Y);
}

//-------------------------------------------------------------------
//  CMSize()
//  11-Aug-2002   rzv    created
//-------------------------------------------------------------------
void TControl::CMSize(int AWidth, int AHeight)
{
	OnSize(AWidth, AHeight);
}


//-------------------------------------------------------------------
//  CMMove()
//  19-Sep-2002   rzv    created
//-------------------------------------------------------------------
void TControl::CMMove(int X, int Y)
{
	OnMove(X, Y);
}

//-------------------------------------------------------------------
//  CMShow()
//  25-March-2004   rzv    created
//-------------------------------------------------------------------
void TControl::CMShow(void)
{
	OnShow();
}

//-------------------------------------------------------------------
//  CMHide()
//  25-March-2004   rzv    created
//-------------------------------------------------------------------
void TControl::CMHide(void)
{
	OnHide();
}

//-------------------------------------------------------------------
//  CMCaptureChanged()
//  29-July-2002   rzv    created
//-------------------------------------------------------------------
void TControl::CMCaptureChanged(void)
{
	OnCaptureChanged();
}

//-------------------------------------------------------------------
//  CMTextChanged()
//  05-March-2003   rzv    created
//-------------------------------------------------------------------
void TControl::CMTextChanged(void)
{
	if(FOnTextChanged)
		FOnTextChanged();

	OnTextChanged();
}

//-------------------------------------------------------------------
//  CMFontChanged()
//  19-Sep-2003   rzv    created
//-------------------------------------------------------------------
void TControl::CMFontChanged(void)
{
	OnFontChanged();
}

//-------------------------------------------------------------------
//  CMParentFontChanged()
//  19-Sep-2003   rzv    created
//-------------------------------------------------------------------
void TControl::CMParentFontChanged(void)
{
	if(ParentFont == true)
	{
		if(Parent != NULL) 
			SetFont(Parent->GetFont());

		OnParentFontChanged();
	}
}

//-------------------------------------------------------------------
//  CMEnable()
//  27-Oct-2003   rzv   created
//-------------------------------------------------------------------
void TControl::CMEnable(void)
{
	OnEnable();
}

//-------------------------------------------------------------------
//  CMDisable()
//  27-Oct-2003   rzv   created
//-------------------------------------------------------------------
void TControl::CMDisable(void)
{
	OnDisable();
}

//-------------------------------------------------------------------
//  CMParentResize()
//  03-Apr-2004   rzv    created
//-------------------------------------------------------------------
void TControl::CMParentResize(int AWidth, int AHeight)
{
	OnParentResize(AWidth, AHeight);
}

//-------------------------------------------------------------------
//  CMParentActivate()
//  29-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TControl::CMParentActivate(void)
{
	OnParentActivate();
}

//-------------------------------------------------------------------
//  CMParentDeactivate()
//  29-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TControl::CMParentDeactivate(void)
{	
	OnParentDeactivate();
}

//-------------------------------------------------------------------
/**
	The OnPaint event occurs when the control is painted.
*/
//-------------------------------------------------------------------
void TControl::OnPaint(void)
{
}

//-------------------------------------------------------------------
/**
	The OnClick event occurs when the user clicks the control.
*/
//-------------------------------------------------------------------
void TControl::OnClick(void)
{
}

//-------------------------------------------------------------------
/**
	The OnDoubleClick event occurs when the user double clicks the control.
*/
//-------------------------------------------------------------------
void TControl::OnDoubleClick(void)
{
}

//-------------------------------------------------------------------
/**
	The OnMouseDown event occurs when the user presses a mouse button 
	with the mouse pointer over the control.

	@param Button	Mouse button that is pressed.
	@param Shift	If any of the special keys are pressed (Shift, Ctrl, Alt, ...).
	@param X		X position of the mouse cursor.
	@param Y		Y position of the mouse cursor.
	@see <code>OnMouseUp OnMouseMove OnClick</code>
*/
//-------------------------------------------------------------------
void TControl::OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	if(Parent != NULL)
		Parent->BringToFront();

	// If we do not have a popup menu item
	if(!dynamic_cast<TPopupMenuItem*>(this))
	{
		// If the screen has a visible popup menu, hide it
		TMenu* VisibleMenu = Screen->GetVisibleMenu();
		if(VisibleMenu != NULL)
		{
			VisibleMenu->Hide();
			Screen->SetVisibleMenu(NULL);
		}
	}

	//-------------------------------------------------------------------
	// Generate a double click code
	//-------------------------------------------------------------------
	
	// Get the new time
	long Time = clock();
	
	float TimeDiff;
#	ifdef __WIN32__
	TimeDiff = (Time - LastTime);
#	elif __LINUX__
	TimeDiff = (Time - LastTime) / 1000;
#	endif

	// If the difference is small enough, generate a double click
	if(TimeDiff < 500.0f && DoubleClicking == true && LastPosition.x == X && LastPosition.y == Y)
	{
		CMMouseDoubleClick();
		DoubleClicking = false;
	}
	else
		DoubleClicking = true;

	// Reset the last time
	LastTime = Time;
	LastPosition = TPoint(X, Y);
	
	//-------------------------------------------------------------------
	// End generating a double click code
	//-------------------------------------------------------------------
	
	// We're clicking.
	Clicking = true;

	// Capture the control if it is not already captured. Even if mouse 
	// cursor is outside the control, it will be the only control that
	// will receive mouse messages until the user will release mouse button.
	if(!GetCaptured())
		SetCapture();
}

//-------------------------------------------------------------------
/**
	The OnMouseUp event occurs when the user releases a mouse button 
	when the mouse pointer is over the control.

	@param Button	Mouse button that is released.
	@param Shift	If any of the special keys are pressed (Shift, Ctrl, Alt, ...).
	@param X		X position of the mouse cursor.
	@param Y		Y position of the mouse cursor.
	@see <code>OnMouseDown OnMouseMove OnClick</code>
*/
//-------------------------------------------------------------------
void TControl::OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y)
{
	// If the control has a popup menu, show it!
	if(Button == mbRight && PopupMenu != NULL)
	{
		PopupMenu->SetLeft(X);
		PopupMenu->SetTop(Y);
		PopupMenu->Show();
	}

    // If we're clicking...
	if(Clicking == true)
		CMMouseClick();

	// We're not clicking anymore.
	Clicking = false;

	if(GetCaptured())
		ReleaseCapture();
}

//-------------------------------------------------------------------
/**
	The OnMouseMove event occurs when the user moves the mouse pointer 
	while the mouse pointer is over the control.

	@param Shift	If any of the special keys are pressed (Shift, Ctrl, Alt, ...).
	@param X		X position of the mouse cursor.
	@param Y		Y position of the mouse cursor.
	@see <code>OnMouseDown OnMouseUp OnClick</code>
*/
//-------------------------------------------------------------------
void TControl::OnMouseMove(const TShiftState& Shift, int X, int Y)
{
}

//-------------------------------------------------------------------
/**
	The OnCaptureChanged event occurs when the control looses the 
	mouse capture.
*/
//-------------------------------------------------------------------
void TControl::OnCaptureChanged(void)
{
	if(Clicking == true)
		Clicking = false;
}

//-------------------------------------------------------------------
/**
	The OnTextChanged event occurs when the caption or the text of the
	control changes. For example, if the user needs to know the exact
	width of the control caption (in pixels) every time the caption 
	changes, this is a good place to calculate it. By default, different 
	controls manages this event in a different manner.
*/
//-------------------------------------------------------------------
void TControl::OnTextChanged(void)
{
	CaptionWidth = Canvas->GetTextWidth(Caption);
}

//-------------------------------------------------------------------
/**
	The OnFontChanged event occurs when the control changes its font.
*/
//-------------------------------------------------------------------
void TControl::OnFontChanged(void)
{	
	if(Font != NULL)
		CaptionHeight = Font->GetHeight();

	if(Controls != NULL)
	{
		TControlsList::iterator iter;
		for(iter = Controls->begin(); 
		    iter != Controls->end(); 
		    iter++)
		{
			TControl* Control = (TControl*)(*iter);	
			Control->CMParentFontChanged();		
		}
	}
}

//-------------------------------------------------------------------
/**
	The OnParentFontChanged event occurs when the parent of the control 
	changes its font.
*/
//-------------------------------------------------------------------
void TControl::OnParentFontChanged(void)
{
	SetFont(Parent->GetFont());
}

//-------------------------------------------------------------------
/**
	The OnSize event occurs whenever the control changes its width or 
	height.

	@param AWidth New width of the control.
	@param AHeight New height of the control.
*/
//-------------------------------------------------------------------
void TControl::OnSize(int AWidth, int AHeight)
{
	UpdateControlRect();
	UpdateClipRect();
	UpdateGrids();

	RealignTopList();
	RealignBottomList();
	RealignLeftList();
	RealignRightList();
}

//-------------------------------------------------------------------
/**
	The OnMove event occurs whenever the control changes its position
	relative to the screen.

	@param X New horizontal position of the control.
	@param Y New vertical position of the control.
*/
//-------------------------------------------------------------------
void TControl::OnMove(int X, int Y)
{
	UpdateControlRect();
	UpdateClipRect();
	
	// Notify all the child controls
	if(Controls != NULL)
	{
		TControlsList::iterator iter;
		for(iter = Controls->begin(); 
		    iter != Controls->end(); 
			iter++)
		{
			TControl* Control = (TControl*)(*iter);	
			Control->CMMove(X, Y);
		}
	}
}

//-------------------------------------------------------------------
/**
	The OnEnable event occurs when the control is being enabled.
*/
//-------------------------------------------------------------------
void TControl::OnEnable(void)
{	
}

//-------------------------------------------------------------------
/**
	The OnDisable event occurs when the control is being disabled.
*/
//-------------------------------------------------------------------
void TControl::OnDisable(void)
{	
}

//-------------------------------------------------------------------
/**
	The OnShow event occurs when the control is being made visible.
*/
//-------------------------------------------------------------------
void TControl::OnShow(void)
{	
}

//-------------------------------------------------------------------
/**
	The OnHide event occurs when the control is being made invisible.
*/
//-------------------------------------------------------------------
void TControl::OnHide(void)
{	
}

//-------------------------------------------------------------------
/**
	The OnParentActivate event occurs when the parent of the control 
	is activated.
*/
//-------------------------------------------------------------------
void TControl::OnParentActivate(void)
{	
}

//-------------------------------------------------------------------
/**
	The OnParentDeactivate event occurs when the parent of the control 
	is deactivated.
*/
//-------------------------------------------------------------------
void TControl::OnParentDeactivate(void)
{	
}

//-------------------------------------------------------------------
/**
	The OnParentResize event occurs when the parent of the control 
	is resized.

  	@param AWidth New width of the parent control.
	@param AHeight New height of the parent control.
*/
//-------------------------------------------------------------------
void TControl::OnParentResize(int AWidth, int AHeight)
{
	// Check anchors. By default, we consider that any control could
	// change it's width and height to any value. Of course, this is
	// not always true. For example, an aqua like button has fixed
	// height. To correct the situation when the code below will 
	// attempt to change dimensions for controls with fixed size,
	// coders should add specific code to restrict the width and
	// height of their own controls. This is commonly done into 
	// the OnSize() member function.
	
	if(GetAnchor(akRight))
	{
		int Distance = AWidth - Parent->GetWidth();

		int MarginRight = Left + Width;
		if(MarginRight - Parent->GetWidth() != MarginRight - AWidth)
		{
			SetLeft(GetLeft() + Distance);
		}
	}
}

//-------------------------------------------------------------------
/**
*/
//-------------------------------------------------------------------
void TControl::ParseSkin(TiXmlElement* XmlElement)
{
	TiXmlElement* Element;
	const char *value = NULL;

	// Set the width of the control
	value = XmlElement->Attribute("Width");
	if(value != NULL)
		sscanf(value, "%d", &Width);

	// Set the height of the control
	value = XmlElement->Attribute("Height");
	if(value != NULL)
		sscanf(value, "%d", &Height);		

	// Set the color
	value = XmlElement->Attribute("Color");
	if(value != NULL)
		sscanf(value, "%x", &Color);

	// Set the caption color
	value = XmlElement->Attribute("CaptionColor");
	if(value != NULL)
		sscanf(value, "%x", &ColorCaption);

	// Set the caption color enabled
	value = XmlElement->Attribute("CaptionColorEnabled");
	if(value != NULL)
		sscanf(value, "%x", &ColorCaptionEnabled);

	// Set the caption color disabled
	value = XmlElement->Attribute("CaptionColorDisabled");
	if(value != NULL)
		sscanf(value, "%x", &ColorCaptionDisabled);

	// Set selection color of the control
	value = XmlElement->Attribute("SelectionColor");
	if(value != NULL)
		sscanf(value, "%x", &ColorSelection);

	// Set the mouse cursor
	value = XmlElement->Attribute("MouseCursor");
	if(value != NULL)
		MouseCursorName.assign(value);

	// Set border width
	value = XmlElement->Attribute("BorderWidth");
	if(value != NULL)
		sscanf(value, "%d", &BorderWidth);

	// Set border color
	value = XmlElement->Attribute("BorderColor");
	if(value != NULL)
		sscanf(value, "%x", &BorderColor);

	// Read the MarginsText attribute
	TRect MarginsTextRect;
	value = XmlElement->Attribute("MarginsText");
	if(value != NULL)
	{
		sscanf(value, "%d,%d,%d,%d", &MarginsTextRect.left, &MarginsTextRect.top, 
			&MarginsTextRect.right, &MarginsTextRect.bottom);
		SetTextMargins(MarginsTextRect);
	}

	// Read the Margins attribute
	TRect MarginsRect;
	value = XmlElement->Attribute("Margins");
	if(value != NULL)
	{
		sscanf(value, "%d,%d,%d,%d", &MarginsRect.left, &MarginsRect.top, 
			&MarginsRect.right, &MarginsRect.bottom);
		SetMargins(MarginsRect);
	}

	// Control cast shadows?
	value = XmlElement->Attribute("CastShadows");
	if(value != NULL)
	{
		if(!strcmp(value, "true"))
			CastShadows = true;
		else if(!strcmp(value, "false"))
			CastShadows = false;
	}

	// Read grids
	for(Element = XmlElement->FirstChildElement("TGrid");
		Element;
		Element = Element->NextSiblingElement("TGrid"))
	{
		// Create, parse and append a new grid
		TGrid* Grid = new TGrid;
		Grid->ParseSkin(Element);
		Grids[Grid->GetName()] = Grid;
	}
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

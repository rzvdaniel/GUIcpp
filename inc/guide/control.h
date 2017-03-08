#ifndef T_CONTROL_H
#define T_CONTROL_H
//-------------------------------------------------------------------
/**
	@class TControl
	@brief Base class for standard controls.

	This is the most beautiful thing.
*/
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TControl
#include "guide/ndefdllclass.h"

#ifndef T_TYPEDEF_H
#include "guide/typedef.h"
#endif

#ifndef T_MATHLIB_H
#include "guide/mathlib.h"
#endif

#ifndef T_GRAPHICS_H
#include "guide/graphics.h"
#endif

#ifndef T_MESSAGES_H
#include "guide/messages.h"
#endif

#ifndef T_COMPONENT_H
#include "guide/component.h"
#endif

#ifndef T_CANVAS_H
#include "guide/canvas.h"
#endif

#ifndef T_FONT_H
#include "guide/font.h"
#endif

#ifndef T_MOUSECURSOR_H
#include "guide/mousecursor.h"
#endif

#ifndef T_CALLBACK_H
#include "guide/callback.h"
#endif

#ifndef T_GRID_H
#include "guide/grid.h"
#endif

#include <set>
#include <stack>
#include <map>

//-------------------------------------------------------------------
// Be very carefull at the first value initialization for different
// operating systems! It is possible that the left mouse button (mbLeft)
// on Linux to be not 1, as it is for Windows. The same for MacOSX.
//-------------------------------------------------------------------

enum TMouseButton { mbLeft = 1, mbMiddle, mbRight };
enum TShiftStates { ssShift = 2, ssAlt, ssCtrl, ssLeft, ssRight, ssMiddle, ssDouble };
enum TAlign { alTop = 0, alBottom, alLeft, alRight, alClient, alNone };
enum TAnchorKind { akLeft, akTop, akRight, akBottom };

class TControl;

typedef stl::list<TControl*> TControlsList;
typedef stl::map<TString, TGrid*> TGridsList;
typedef stl::stack<TRect> TRectStack;
typedef stl::set< TShiftStates, stl::less<TShiftStates> > TShiftState;
typedef stl::set< TAnchorKind, stl::less<TAnchorKind> > TAnchors;

// Here should be defined all the events the user can play with
typedef CBFunctor0 TNotifyEvent;
typedef CBFunctor4<TMouseButton, TShiftState, int, int> TMouseDownEvent;
typedef CBFunctor4<TMouseButton, TShiftState, int, int> TMouseUpEvent;
typedef CBFunctor3<TShiftState, int, int> TMouseMoveEvent;

//-------------------------------------------------------------------
class TScreen;
class TSkin;
class TMenu;
class N_PUBLIC TControl : public TComponent 
{ 
	TControlsList* Controls;
	TControl* Parent;
	TMouseCursor* MouseCursor;
	TFont* Font;
	TMenu* PopupMenu;
	TGridsList Grids;
	TGrid* CurrentGrid;
	TString MouseCursorName;
	TString Text;
	TString	Caption;
	TRect Margins;
	TRect MarginsText;
	TRect ControlRect;
	TRect ClipRect;
	TRectStack ClipRectStack;

	TColor Color;
	TColor ColorCaption;
	TColor ColorCaptionDisabled;
	TColor ColorCaptionEnabled;
	TColor ColorSelection;
	TAlign Align;
	TAnchors Anchors;

	bool ParentFont;
	bool Visible;
	bool Captured;
	bool Enabled;
	bool Clicking;
	bool DoubleClicking;
	bool CastShadows;
	int	 Left;
	int	 Top;
	int	 Width;
	int	 Height;
	// Used to generate double click events
	long LastTime;
	TPoint LastPosition;

protected:
	float CaptionX;
	float CaptionY;
	float CaptionHeight;
	float CaptionWidth;
	TControlsList AlignedControls[5];

	TColor BorderColor;
	int BorderWidth;

public:
	TCanvas* Canvas;
	TScreen* Screen;
	TSkin* Skin;

	TNotifyEvent	FOnPaint;
	TNotifyEvent	FOnClick;
	TNotifyEvent	FOnTextChanged;
	TMouseDownEvent FOnMouseDown;
	TMouseUpEvent   FOnMouseUp;
	TMouseMoveEvent FOnMouseMove;

public:
	/// Constructor
	TControl();
	/// Destructor
	virtual ~TControl();
	
	/// Creates a new control.
	virtual void Create(TComponent* AOwner, const TRect& Rect);
	/// Copy properties of the passed object to this one.
	virtual void Assign(TObject* Object);
	/// Parses a xml skin element and adjust control's properties.
	virtual void ParseSkin(TiXmlElement* XmlElement);
	/// Applies skin properties to the control
	virtual void ApplySkin(TObject* Object);

	/// Retrieve the child control with the specified name.
	TControl* GetChild(TString AName) const;
	/// Retrieve the child control with the specified name.
	TControl* GetControl(TString AName);
	/// Returns the list of direct children this control contains.
	TControlsList* GetControls(void) const { return Controls; }	
	
	/// Change the parent of the control.
	void SetParent(TControl* AParent);
	/// Returns the control's parent.
	TControl* GetParent(void) const { return Parent; }

	/// Specify the popup menu associated with the control.
	void SetPopupMenu(TMenu* APopupMenu);
	/// Returns the popup menu associated with the control.
	TMenu* GetPopupMenu(void) const;
	
	/// Contains a text string that identifies the control to the user.
	virtual void SetCaption(const char* ACaption);
	/// Contains a text string that identifies the control to the user.
	virtual void SetCaption(TString ACaption);
	/// Returns the caption of the control.
	TString GetCaption(void) const { return Caption; }
	
	/// Contains a text string associated with the control.
	virtual void SetText(TString AText);
	/// Contains a text string associated with the control.
    TString GetText(void) const { return Text; }
	
	/// X, Y coordinate of the top left corner of the control
	void SetPosition(TPoint Value);
	/// X, Y coordinate of the top left corner of the control
	TPoint GetPosition(void) const { return TPoint(Left, Top); }

	/// X coordinate of the top left corner of the control
	void SetLeft(int Value);
	/// X coordinate of the top left corner of the control
	int	GetLeft(void) const { return Left; }
	
	/// Y coordinate of the top left corner of the control
	void SetTop(int Value);
	/// Y coordinate of the top left corner of the control
	int	GetTop(void) const { return Top; }

	/// Specifies the horizontal size of the control in pixels.
	void SetWidth(int Value);
	/// Specifies the horizontal size of the control in pixels.
	int	GetWidth(void) const { return Width; }

	/// Specifies the vertical size of the control in pixels.
	void SetHeight(int Value);
	/// Specifies the vertical size of the control in pixels.
	int	GetHeight(void) const { return Height; }

	/// Change the visibility of the control.
	void SetVisible(bool Value);
	/// Retrieve the visibility of the control.
	bool GetVisible(void) const	{ return Visible; }	
	
	/// Set mouse capture for this control.
	void SetCapture(void);
	/// Releases the mouse capture for this control.
	void ReleaseCapture(void);
	/// Tells if the control is capturing the mouse input.
	bool GetCaptured(void) const { return Captured; }

	/// Controls whether the control responds to mouse, keyboard, and timer events.
	void SetEnabled(bool Value);
	/// Tells whether the control responds to mouse, keyboard, and timer events
	bool GetEnabled(void) const { return Enabled; }	
	
	/// Sets the control's font to the parent one. 
	void SetParentFont(bool Value);
	/// Tells if the control is using the font of its parent.
	bool GetParentFont(void) const { return ParentFont; }
	
	/// Sets the alignment of the control within its parent.
	void SetAlign(TAlign Value);	
	/// Returns the alignment of the control.
	TAlign GetAlign(void) const { return Align; }

	/// Adds or removes an anchor from the control's list of anchors.
	void SetAnchor(TAnchorKind Anchor, bool Value = true);
	/// Retrieve control's anchor.
	bool GetAnchor(TAnchorKind Anchor) const;

	/// Set border width
	void SetBorderWidth(int AWidth);
	/// Set border color
	void SetBorderColor(TColor AColor);
	/// Get border width
	int GetBorderWidth() { return BorderWidth; }
	/// Get border color
	TColor GetBorderColor() { return BorderColor; }
	
	/// Tells if the control will cast shadows.
	void SetCastShadows(bool Value) { CastShadows = Value; }
	/// Tells if the control is able to cast shadows.
	bool GetCastShadows(void) const { return CastShadows; }
		
	/// Set the control's background color.
	void SetColor(TColor Value) { Color = Value; }
	/// Returns the control's background color.
	TColor GetColor(void) const	{ return Color; }

	/// Set the control's caption color.
	void SetCaptionColor(TColor Value) { ColorCaption = Value; }
	/// Returns the control's caption color.
	TColor GetCaptionColor(void) const	{ return ColorCaption; }
	
	/// Set the control's caption color when control is enabled.
	void SetCaptionColorEnabled(TColor Value) { ColorCaptionEnabled = Value; }
	/// Returns the control's caption color when control is enabled.
	TColor GetCaptionColorEnabled(void) const	{ return ColorCaptionEnabled; }
	
	/// Set the control's caption color when control is disabled.
	void SetCaptionColorDisabled(TColor Value) { ColorCaptionDisabled = Value; }
	/// Returns the control's caption color when control is disabled.
	TColor GetCaptionColorDisabled(void) const	{ return ColorCaptionDisabled; }

	/// Set the selection color.
	void SetSelectionColor(TColor Value) { ColorSelection = Value; }
	/// Get the selection color.
	TColor GetSelectionColor(void) const { return ColorSelection; }

	/// Change the current font of the control.
	void SetFont(TFont* AFont);
	/// Retrieve the current font of the control.
	TFont* GetFont(void) const { return Font; }
	//// Returns the font with the specified size, if any.
	TFont* GetFont(const char* Name, int Size);	

	/// Set mouse cursor for the control.
	void SetMouseCursor(TString Name);
	/// Set mouse cursor for the control.
	void SetMouseCursor(TMouseCursor* ACursor) { MouseCursor = ACursor; }
	/// Returns control's mouse cursor, if any. <code>NULL</code> if no mouse cursor is found.	
	TMouseCursor* GetMouseCursor(void) const { return MouseCursor; }
	/// Returns specified mouse cursor, if any.
	TMouseCursor* GetMouseCursor(const char* Name);
	/// Returns name of specified mouse cursor, if any.
	TString GetMouseCursorName(void) { return MouseCursorName; }

	/// Retrieve the topmost control at the specified position.
	virtual TControl* ControlFromPoint(const TPoint& Point);
	
	/// Returns the clipping rectangle of the control.
	TRect GetClipRect(void) const { return ClipRect; }
	/// Returns control's rect, in screen coordinates.
	TRect GetControlRect(void) const { return ControlRect; }
	
	/// Returns width of the caption
	float GetCaptionWidth() { return CaptionWidth; }
	/// Returns height of the caption
	float GetCaptionHeight() { return CaptionHeight; }
	
	/// Sets the Left, Top, Width and Height properties of the control at once.
	virtual void SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	virtual void SetBounds(const TRect &Rect);
	/// Returns the Left, Top, Width and Height properties of the control.
	void GetBounds(int& ALeft, int& ATop, int& AWidth, int& AHeight) const;
	/// Returns the Left, Top, Width and Height properties of the control, as a TRect structure.
	TRect GetBounds(void) const;
	/// Set the bounds of the control, relative to its parent.
	void SetBoundsRect(const TRect &Rect);
	/// Get the bounds of the control, relative to its parent.
	TRect GetBoundsRect(void) const;

	/// Margins
	void SetMargins(const TRect& Value);
	void SetMargins(int Left, int Top, int Right, int Bottom);
	const TRect& GetMargins(void);

	void SetTextMargins(const TRect& Value);
	void SetTextMargins(int Left, int Top, int Right, int Bottom);
	const TRect& GetTextMargins(void);

	/// Converts screen coordinates to control coordinates.
	TPoint ScreenToControl(TPoint Point);
	/// Converts screen coordinates to control coordinates.
	void ScreenToControl(int& X, int& Y);
	/// Converts control coordinates to screen coordinates.
	TPoint ControlToScreen(TPoint Point);
	/// Converts control coordinates to screen coordinates.
	void ControlToScreen(int& X, int& Y);
	
	/// Call SetZOrder to change the Z-order of the control.
	virtual void SetZOrder(bool TopMost);
	/// Place the control in front of all other controls within its parent control.
	void BringToFront(void);
	/// Make the control the bottommost one.
	void SendToBack(void);	

	/// Make the control visible.
	void Show(void);
	/// Hides the control.
	void Hide(void);
	/// Simulates a click mouse event for the control.
	void Click(void);

public:
	void PushClipRect(void);
	void PopClipRect(void);

protected:
	TGridsList GetGrids(void) const { return Grids; }
	TGrid* GetGrid(const char* AName);
	void SetGrids(TGridsList AGrids);
	void DestroyGrids(void);
	void SetCurrentGrid(TGrid* AGrid) { CurrentGrid = AGrid; }
	TGrid* GetCurrentGrid(void) const { return CurrentGrid; }
	/// Paint control borders
	virtual void PaintBorders(void);

private:
	void InsertControl(TControl* Control);
	void RemoveControl(TControl* Control);
	void DestroyControls(void);	
	
	void UpdateClipRect(void);
	void UpdateControlRect(void);
	void UpdateGrids(void); 

	TControl* GetLastAlignedControl(TAlign Value);
	TRect GetEmptyAlignedRect(void);

	void InsertAlignedControl(TAlign Value);
	void RemoveAlignedControl(TAlign Value);
	void AlignControl(TAlign Value);

	void RealignLeftList(void);
	void RealignRightList(void);
	void RealignTopList(void);
	void RealignBottomList(void);
	void RealignClientList(void);

	void AlignLeft(void);
	void AlignRight(void);
	void AlignTop(void);
	void AlignBottom(void);
	void AlignClient(void);
	void AlignNone(void);

protected:
	// Events
	virtual void OnPaint(void);
	virtual void OnClick(void);
	virtual void OnDoubleClick(void);
	virtual void OnMouseDown(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseUp(TMouseButton Button, const TShiftState& Shift, int X, int Y);
	virtual void OnMouseMove(const TShiftState& Shift, int X, int Y);	
	virtual void OnSize(int AWidth, int AHeight);
	virtual void OnMove(int X, int Y);
	virtual void OnShow(void);
	virtual void OnHide(void);
	virtual void OnCaptureChanged(void);
	virtual void OnTextChanged(void);
	virtual void OnFontChanged(void);
	virtual void OnParentFontChanged(void);
	virtual void OnEnable(void);
	virtual void OnDisable(void);
	virtual void OnParentResize(int AWidth, int AHeight);
	virtual void OnParentActivate(void);
	virtual void OnParentDeactivate(void);

public:
	// Event generators
	virtual void CMPaint(void);
	virtual void CMMouseClick(void);
	virtual void CMMouseDoubleClick(void);
	virtual void CMMouseDown(TMouseButton Button, int X, int Y);
	virtual void CMMouseUp(TMouseButton Button, int X, int Y);
	virtual void CMMouseMove(int X, int Y);
	virtual void CMCaptureChanged(void);
	virtual void CMSize(int AWidth, int AHeight);
	virtual void CMMove(int X, int Y);
	virtual void CMShow(void);
	virtual void CMHide(void);
	virtual void CMTextChanged(void);	
	virtual void CMFontChanged(void);	
	virtual void CMParentFontChanged(void);
	virtual void CMEnable(void);
	virtual void CMDisable(void);
	virtual void CMParentResize(int AWidth, int AHeight);
	virtual void CMParentActivate(void);
	virtual void CMParentDeactivate(void);

};

//-------------------------------------------------------------------
#endif


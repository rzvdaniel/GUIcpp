#define N_IMPLEMENTS TScrollingWinControl
//-------------------------------------------------------------------
//  scrollwinctrl.cpp
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/scrollwinctrl.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TScrollingWinControl()
//  15-May-2003   rzv   created
//-------------------------------------------------------------------
TScrollingWinControl::TScrollingWinControl()
{
	ScrollStyle = ssNone;
	HorzScrollBar = NULL;
	VertScrollBar = NULL;
	AutoScroll = true;
}

//-------------------------------------------------------------------
//  ~TScrollingWinControl()
//  15-May-2003   rzv   created
//-------------------------------------------------------------------
TScrollingWinControl::~TScrollingWinControl()
{	
}

//-------------------------------------------------------------------
//  Create()
//  07-Jun-2003   rzv   created
//-------------------------------------------------------------------
void TScrollingWinControl::Create(TComponent* AOwner, const TRect& Rect)
{	
	TWinControl::Create(AOwner, Rect);	
}

//-------------------------------------------------------------------
//  SetScrollStyle()
//  25-Sep-2003   rzv   created
//-------------------------------------------------------------------
void TScrollingWinControl::SetScrollStyle(TScrollStyle Value)
{
	if(ScrollStyle != Value)
	{
		ScrollStyle = Value;
		
		switch(ScrollStyle)
		{
			case ssNone:
			{
				if(HorzScrollBar != NULL)
				{
					delete HorzScrollBar;
					HorzScrollBar = NULL;
				}
				if(VertScrollBar != NULL)
				{
					delete VertScrollBar;
					VertScrollBar = NULL;
				}
				break;
			}
			case ssHorizontal:
			{
				if(HorzScrollBar == NULL)
				{
					HorzScrollBar = new TScrollBar;
					HorzScrollBar->Create(this, GetBounds(), sbHorizontal);
				}
				if(VertScrollBar != NULL)
				{
					delete VertScrollBar;
					VertScrollBar = NULL;
				}
				break;
			}
			case ssVertical:
			{
				if(VertScrollBar == NULL)
				{
					VertScrollBar = new TScrollBar;
					VertScrollBar->Create(this, GetBounds(), sbVertical);
				}
				if(HorzScrollBar != NULL)
				{
					delete HorzScrollBar;
					HorzScrollBar = NULL;
				}
				break;
			}
			case ssBoth:
			{
				if(HorzScrollBar == NULL)
				{
					HorzScrollBar = new TScrollBar;
					HorzScrollBar->Create(this, GetBounds(), sbHorizontal);	
				}
				if(VertScrollBar == NULL)
				{
					VertScrollBar = new TScrollBar;
					VertScrollBar->Create(this, GetBounds(), sbVertical);
				}
				break;
			}
		}
	}
}

//-------------------------------------------------------------------
//  OnKeyDown()
//  09-June-2003   rzv    created
//-------------------------------------------------------------------
void TScrollingWinControl::OnKeyDown(unsigned short &Key, const TShiftState& Shift)
{
	// Don't call the base class for now, because we don't want to 
	// pass the input to the child controls (like scroll bars)

	//TWinControl::OnKeyDown(Key, Shift);	
}

//-------------------------------------------------------------------
//  OnKeyUp()
//  09-June-2003   rzv    created
//-------------------------------------------------------------------
void TScrollingWinControl::OnKeyUp(unsigned short& Key, const TShiftState& Shift)
{
	// Don't call the base class for now, because we don't want to 
	// pass the input to the child controls (like scroll bars)
	
	//TWinControl::OnKeyUp(Key, Shift);	
}

//-------------------------------------------------------------------
//  OnKeyPress()
//  09-June-2003   rzv    created
//-------------------------------------------------------------------
void TScrollingWinControl::OnKeyPress(char &Key)
{
	// Don't call the base class for now, because we don't want to 
	// pass the input to the child controls (like scroll bars)

	//TWinControl::OnKeyPress(Key);	
}

//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------

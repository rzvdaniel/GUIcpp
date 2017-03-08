#ifndef T_MATHLIB_H
#define T_MATHLIB_H

#include "guide/ndefdllclass.h"

//-------------------------------------------------------------------
/**
	@class TPoint, TRect
*/
//--------------------------------------------------------------------

// TSmallPoint
struct N_PUBLIC TSmallPoint
{
	short x;
	short y;
};

// TFloatPoint
struct N_PUBLIC TFloatPoint 
{
	float x;
	float y;
};

// TPoint
class N_PUBLIC TPoint
{
public:
	int x;
	int y;

public:
	TPoint() {}
	TPoint(int initX, int initY) {
		x = initX; y = initY; 
	}
	void operator=(const TPoint& p) {
		x = p.x;
		y = p.y;
	}

};

// TRect
class N_PUBLIC TRect
{
public:
	int left;
    int top;
    int right;
    int bottom;
	
public:

	TRect() {
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	TRect(const TRect& r) {
		left = r.left;
		top = r.top;
		right = r.right;
		bottom = r.bottom;
	}

	TRect(int l, int t, int r, int b) {
		left = l; top = t; right = r; bottom = b;
	}

	void operator=(const TRect& r) {
		left = r.left;
		top = r.top;
		right = r.right;
		bottom = r.bottom;
	}

	bool operator!=(const TRect& r) {
		return (left != r.left) && (top != r.top) &&
				(right != r.right) && (bottom != r.bottom);
	}

	bool PtInRect(const TPoint& point) const;
	bool RcInRect(const TRect& rect) const;
	bool IntersectRect(const TRect& r1, const TRect& r2);
	void InflateRect(int x, int y);
	void DeflateRect(int x, int y);
};

//-------------------------------------------------------------------
//  PtInRect()
//  16-July-2002   rzv   created
//-------------------------------------------------------------------
inline bool TRect::PtInRect(const TPoint& point) const
{
	if(point.x >= this->left && point.x <= this->right &&
		point.y >= this->top && point.y <= this->bottom)
		return true;
	else
		return false;
}

//-------------------------------------------------------------------
//  RcInRect()
//  16-July-2002   rzv   created
//-------------------------------------------------------------------
inline bool TRect::RcInRect(const TRect& rect) const
{
	if(this->PtInRect(TPoint(rect.left,rect.top)) || 
		this->PtInRect(TPoint(rect.right,rect.top)) ||
	    this->PtInRect(TPoint(rect.right,rect.bottom)) ||
	    this->PtInRect(TPoint(rect.left,rect.bottom)))
	    return true;
	else
		return false;
}

//-------------------------------------------------------------------
//  IntersectRect()
//  16-July-2002   rzv   created
//-------------------------------------------------------------------
inline bool TRect::IntersectRect(const TRect& r1, const TRect& r2)
{
	if(r1.RcInRect(r2) || r2.RcInRect(r1))
	{
		if(r1.left >= r2.left) this->left = r1.left;
		else this->left = r2.left;
		if(r1.right >= r2.right) this->right = r2.right;
		else this->right = r1.right;
		if(r1.top >= r2.top) this->top = r1.top;
		else this->top = r2.top;
		if(r1.bottom >= r2.bottom) this->bottom = r2.bottom;
		else this->bottom = r1.bottom;

		return true;
	}
	else
	{
		this->top = 0;
		this->left = 0;
		this->bottom = 0;
		this->right = 0;

		return false;
	}
}

//-------------------------------------------------------------------
//  InflateRect()
//  16-July-2002   rzv   created
//-------------------------------------------------------------------
inline void TRect::InflateRect(int x, int y)
{
	this->left		-= x;
	this->top		-= y;
	this->right		+= x;
	this->bottom	+= y;
}

//-------------------------------------------------------------------
//  DeflateRect()
//  16-July-2002   rzv   created
//-------------------------------------------------------------------
inline void TRect::DeflateRect(int x, int y)
{
	this->left		+= x;
	this->top		+= y;
	this->right		-= x;
	this->bottom	-= y;
}

//-------------------------------------------------------------------
#endif

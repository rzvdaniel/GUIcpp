#ifndef T_GRAPHICS_H
#define T_GRAPHICS_H
//--------------------------------------------------------------------
//  Colors
//
//  (C) 2002 R.Predescu
//--------------------------------------------------------------------
typedef unsigned long	TColor;

#define rgba(r,g,b,a)	(((a) << 24)|((b) << 16)|((g) << 8)|(r))
#define rgb(r,g,b)		(((b) << 16)|((g) << 8)|(r))
#define GetAlpha(rgb)	((rgb) >> 24)
#define GetBlue(rgb)	(((rgb) >> 16) & 0xff)
#define GetGreen(rgb)	(((rgb) >> 8) & 0xff)
#define GetRed(rgb)		((rgb) & 0xff)

#define clBlack			0xFF000000
#define clMaroon		0xFF000080
#define clGreen			0xFF008000
#define clOlive			0xFF008080
#define clNavy			0xFF800000
#define clPurple        0xFF800080
#define clTeal			0xFF808000
#define clGray			0xFF808080
#define clSilver		0xFFC0C0C0
#define clRed			0xFF0000FF
#define clLime			0xFF00FF00
#define clYellow		0xFF00FFFF
#define clBlue			0xFFFF0000
#define clFuchsia		0xFFFF00FF
#define clAqua			0xFFFFFF00
#define clLtGray		0xFFC0C0C0
#define clDkGray		0xFF808080
#define clWhite			0xFFFFFFFF

//-------------------------------------------------------------------
#endif



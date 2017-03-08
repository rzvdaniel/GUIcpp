#ifndef T_TYPEDEF_H
#define T_TYPEDEF_H
//--------------------------------------------------------------------
//  Shortcut typedefs
//
//  (C) 2002 R.Predescu
//--------------------------------------------------------------------
#ifndef NULL
#define NULL (0L)
#endif
#define FAR             far
#define NEAR            near
#ifndef CONST
#define CONST           const
#endif

#define T_MAXPATH		512 
#define T_MAXNAMELEN	32  

typedef unsigned int	UINT;
typedef unsigned long	ULONG;
typedef unsigned short	USHORT;
typedef unsigned char	UCHAR;
typedef unsigned long	DWORD;
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef float			FLOAT;
typedef long			LONG;
typedef int				INT;
typedef WORD			ATOM;
typedef UINT			WPARAM;
typedef LONG			LPARAM;
typedef LONG			LRESULT;

#define T_MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define T_MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define T_LOWORD(l)           ((WORD)(l))
#define T_HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define T_LOBYTE(w)           ((BYTE)(w))
#define T_HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

#define T_MAKEWPARAM(l, h)    (WPARAM)T_MAKELONG(l, h)
#define T_MAKELPARAM(l, h)    (LPARAM)T_MAKELONG(l, h)
#define T_MAKELRESULT(l, h)   (LRESULT)T_MAKELONG(l, h)

//-------------------------------------------------------------------
#endif

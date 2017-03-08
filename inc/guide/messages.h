#ifndef T_MESSAGES_H
#define T_MESSAGES_H
//--------------------------------------------------------------------
//  Messages
//
//  (C) 2002 R.Predescu
//--------------------------------------------------------------------

#ifndef T_MATHLIB_H
#include "guide/mathlib.h"
#endif

//-------------------------------------------------------------------
struct TMessage  
{
	unsigned long	Msg;
	long			WParam;
	long			LParam;
};

struct TWMKey
{
	unsigned long	Msg;
	long		    CharCode;
	long			KeyData;
};

struct TWMMouse 
{
	unsigned long	Msg;
	long			Keys;
	union
	{
		TSmallPoint Pos;
		struct 
		{
			short   XPos;
			short   YPos;	
		};
	};
};

// Keycodes
enum TKey {
    T_KEY_NONE,

    T_KEY_LBUTTON,
    T_KEY_RBUTTON,
    T_KEY_MBUTTON,
    T_KEY_BACK,
    T_KEY_TAB,
	T_KEY_CLEAR,
    T_KEY_RETURN,
    T_KEY_SHIFT,
    T_KEY_CONTROL,
    T_KEY_MENU,
    T_KEY_PAUSE,
    T_KEY_CAPITAL,
    T_KEY_ESCAPE,
    T_KEY_SPACE,
    T_KEY_PRIOR,
    T_KEY_NEXT,
    T_KEY_END,
    T_KEY_HOME,
    T_KEY_LEFT,
    T_KEY_UP,
    T_KEY_RIGHT,
    T_KEY_DOWN,
    T_KEY_SELECT,
    T_KEY_PRINT,
    T_KEY_EXECUTE,
    T_KEY_SNAPSHOT,
    T_KEY_INSERT,
    T_KEY_DELETE,
    T_KEY_HELP,

    T_KEY_1,
    T_KEY_2,
    T_KEY_3,
    T_KEY_4,
    T_KEY_5,
    T_KEY_6,
    T_KEY_7,
    T_KEY_8,
    T_KEY_9,
    T_KEY_0,

    T_KEY_A,
    T_KEY_B,
    T_KEY_C,
    T_KEY_D,
    T_KEY_E,
    T_KEY_F,
    T_KEY_G,
    T_KEY_H,
    T_KEY_I,
    T_KEY_J,
    T_KEY_K,
    T_KEY_L,
    T_KEY_M,
    T_KEY_N,
    T_KEY_O,
    T_KEY_P,
    T_KEY_Q,
    T_KEY_R,
    T_KEY_S,
    T_KEY_T,
    T_KEY_U,
    T_KEY_V,
    T_KEY_W,
    T_KEY_X,
    T_KEY_Y,
    T_KEY_Z,

    T_KEY_LWIN,
    T_KEY_RWIN,
    T_KEY_APPS,

    T_KEY_NUMPAD0,
    T_KEY_NUMPAD1,
    T_KEY_NUMPAD2,
    T_KEY_NUMPAD3,
    T_KEY_NUMPAD4,
    T_KEY_NUMPAD5,
    T_KEY_NUMPAD6,
    T_KEY_NUMPAD7,
    T_KEY_NUMPAD8,
    T_KEY_NUMPAD9,

    T_KEY_MULTIPLY,
    T_KEY_ADD,
    T_KEY_SEPARATOR,
    T_KEY_SUBTRACT,
    T_KEY_DECIMAL,
    T_KEY_DIVIDE,
    T_KEY_F1,
    T_KEY_F2,
    T_KEY_F3,
    T_KEY_F4,
    T_KEY_F5,
    T_KEY_F6,
    T_KEY_F7,
    T_KEY_F8,
    T_KEY_F9,
    T_KEY_F10,
    T_KEY_F11,
    T_KEY_F12,
    T_KEY_F13,
    T_KEY_F14,
    T_KEY_F15,
    T_KEY_F16,
    T_KEY_F17,
    T_KEY_F18,
    T_KEY_F19,
    T_KEY_F20,
    T_KEY_F21,
    T_KEY_F22,
    T_KEY_F23,
    T_KEY_F24,

    T_KEY_NUMLOCK,
    T_KEY_SCROLL,
};

// Keys & Chars
#define CM_KEYDOWN                      0x0100
#define CM_KEYUP                        0x0101
#define CM_CHAR                         0x0102
#define CM_DEADCHAR                     0x0103
#define CM_SYSKEYDOWN                   0x0104
#define CM_SYSKEYUP                     0x0105
#define CM_SYSCHAR                      0x0106
#define CM_SYSDEADCHAR                  0x0107

// Mouse
#define CM_MOUSEMOVE                    0x0200
#define CM_MOUSEDOWN                    0x0201
#define CM_MOUSEUP                      0x0202
#define CM_MOUSECLICK					0x0203
#define CM_MOUSEDBLCLCK                 0x0204

//-------------------------------------------------------------------
#endif 




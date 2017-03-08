//-------------------------------------------------------------------
//  winkey.cpp
//
//  (C) 1999 A.Weissflog
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/nsystem.h"
#include "guide/messages.h"
#include "guide/osincludes.h"

#ifdef __WIN32__
TKey TranslateKey(int vkey)
{
    TKey tk;
    switch(vkey) {
        case VK_LBUTTON:    tk=T_KEY_LBUTTON; break;
        case VK_RBUTTON:    tk=T_KEY_RBUTTON; break;
        case VK_MBUTTON:    tk=T_KEY_MBUTTON; break;
        case VK_BACK:       tk=T_KEY_BACK; break;
        case VK_TAB:        tk=T_KEY_TAB; break;
        case VK_RETURN:     tk=T_KEY_RETURN; break;
        case VK_SHIFT:      tk=T_KEY_SHIFT; break;
        case VK_CONTROL:    tk=T_KEY_CONTROL; break;
        case VK_MENU:       tk=T_KEY_MENU; break;
        case VK_PAUSE:      tk=T_KEY_PAUSE; break;
        case VK_CAPITAL:    tk=T_KEY_CAPITAL; break;
        case VK_ESCAPE:     tk=T_KEY_ESCAPE; break;
        case VK_SPACE:      tk=T_KEY_SPACE; break;
        case VK_PRIOR:      tk=T_KEY_PRIOR; break;
        case VK_NEXT:       tk=T_KEY_NEXT; break;
        case VK_END:        tk=T_KEY_END; break;
        case VK_HOME:       tk=T_KEY_HOME; break;
        case VK_LEFT:       tk=T_KEY_LEFT; break;
        case VK_UP:         tk=T_KEY_UP; break;
        case VK_RIGHT:      tk=T_KEY_RIGHT; break;
        case VK_DOWN:       tk=T_KEY_DOWN; break;
        case VK_SELECT:     tk=T_KEY_SELECT; break;
        case VK_PRINT:      tk=T_KEY_PRINT; break;
        case VK_EXECUTE:    tk=T_KEY_EXECUTE; break;
        case VK_SNAPSHOT:   tk=T_KEY_SNAPSHOT; break;
        case VK_INSERT:     tk=T_KEY_INSERT; break;
        case VK_DELETE:     tk=T_KEY_DELETE; break;
        case VK_HELP:       tk=T_KEY_HELP; break;
        case '0':           tk=T_KEY_0; break;
        case '1':           tk=T_KEY_1; break;
        case '2':           tk=T_KEY_2; break;
        case '3':           tk=T_KEY_3; break;
        case '4':           tk=T_KEY_4; break;
        case '5':           tk=T_KEY_5; break;
        case '6':           tk=T_KEY_6; break;
        case '7':           tk=T_KEY_7; break;
        case '8':           tk=T_KEY_8; break;
        case '9':           tk=T_KEY_9; break;
        case 'A':           tk=T_KEY_A; break;
        case 'B':           tk=T_KEY_B; break;
        case 'C':           tk=T_KEY_C; break;
        case 'D':           tk=T_KEY_D; break;
        case 'E':           tk=T_KEY_E; break;
        case 'F':           tk=T_KEY_F; break;
        case 'G':           tk=T_KEY_G; break;
        case 'H':           tk=T_KEY_H; break;
        case 'I':           tk=T_KEY_I; break;
        case 'J':           tk=T_KEY_J; break;
        case 'K':           tk=T_KEY_K; break;
        case 'L':           tk=T_KEY_L; break;
        case 'M':           tk=T_KEY_M; break;
        case 'N':           tk=T_KEY_N; break;
        case 'O':           tk=T_KEY_O; break;
        case 'P':           tk=T_KEY_P; break;
        case 'Q':           tk=T_KEY_Q; break;
        case 'R':           tk=T_KEY_R; break;
        case 'S':           tk=T_KEY_S; break;
        case 'T':           tk=T_KEY_T; break;
        case 'U':           tk=T_KEY_U; break;
        case 'V':           tk=T_KEY_V; break;
        case 'W':           tk=T_KEY_W; break;
        case 'X':           tk=T_KEY_X; break;
        case 'Y':           tk=T_KEY_Y; break;
        case 'Z':           tk=T_KEY_Z; break;
        case VK_LWIN:       tk=T_KEY_LWIN; break;
        case VK_RWIN:       tk=T_KEY_RWIN; break;
        case VK_APPS:       tk=T_KEY_APPS; break;
        case VK_NUMPAD0:    tk=T_KEY_NUMPAD0; break;
        case VK_NUMPAD1:    tk=T_KEY_NUMPAD1; break;
        case VK_NUMPAD2:    tk=T_KEY_NUMPAD2; break;
        case VK_NUMPAD3:    tk=T_KEY_NUMPAD3; break;
        case VK_NUMPAD4:    tk=T_KEY_NUMPAD4; break;
        case VK_NUMPAD5:    tk=T_KEY_NUMPAD5; break;
        case VK_NUMPAD6:    tk=T_KEY_NUMPAD6; break;
        case VK_NUMPAD7:    tk=T_KEY_NUMPAD7; break;
        case VK_NUMPAD8:    tk=T_KEY_NUMPAD8; break;
        case VK_NUMPAD9:    tk=T_KEY_NUMPAD9; break;
        case VK_MULTIPLY:   tk=T_KEY_MULTIPLY; break;
        case VK_ADD:        tk=T_KEY_ADD; break;
        case VK_SEPARATOR:  tk=T_KEY_SEPARATOR; break;
        case VK_SUBTRACT:   tk=T_KEY_SUBTRACT; break;
        case VK_DECIMAL:    tk=T_KEY_DECIMAL; break;
        case VK_DIVIDE:     tk=T_KEY_DIVIDE; break;
        case VK_F1:         tk=T_KEY_F1; break;
        case VK_F2:         tk=T_KEY_F2; break;
        case VK_F3:         tk=T_KEY_F3; break;
        case VK_F4:         tk=T_KEY_F4; break;
        case VK_F5:         tk=T_KEY_F5; break;
        case VK_F6:         tk=T_KEY_F6; break;
        case VK_F7:         tk=T_KEY_F7; break;
        case VK_F8:         tk=T_KEY_F8; break;
        case VK_F9:         tk=T_KEY_F9; break;
        case VK_F10:        tk=T_KEY_F10; break;
        case VK_F11:        tk=T_KEY_F11; break;
        case VK_F12:        tk=T_KEY_F12; break;
        case VK_F13:        tk=T_KEY_F13; break;
        case VK_F14:        tk=T_KEY_F14; break;
        case VK_F15:        tk=T_KEY_F15; break;
        case VK_F16:        tk=T_KEY_F16; break;
        case VK_F17:        tk=T_KEY_F17; break;
        case VK_F18:        tk=T_KEY_F18; break;
        case VK_F19:        tk=T_KEY_F19; break;
        case VK_F20:        tk=T_KEY_F20; break;
        case VK_F21:        tk=T_KEY_F21; break;
        case VK_F22:        tk=T_KEY_F22; break;
        case VK_F23:        tk=T_KEY_F23; break;
        case VK_F24:        tk=T_KEY_F24; break;
        case VK_NUMLOCK:    tk=T_KEY_NUMLOCK; break;
        case VK_SCROLL:     tk=T_KEY_SCROLL; break;
        default:            tk=T_KEY_NONE; break;
    }
    return tk;
}
#endif
//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


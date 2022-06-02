//-------------------------------------------------------------------
//  sdlkey.cpp
//
//  (C) 1999 A.Weissflog
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "SDL.h"
#include "guide/nsystem.h"
#include "guide/messages.h"

TKey TranslateKey(int sdlkey)
{
    TKey tk;
    switch(sdlkey) 
	{
        case SDLK_BACKSPACE:		tk=T_KEY_BACK; break;
        case SDLK_TAB:				tk=T_KEY_TAB; break;
        case SDLK_CLEAR:			tk=T_KEY_CLEAR; break;
        case SDLK_RETURN:			tk=T_KEY_RETURN; break;
        case SDLK_PAUSE:			tk=T_KEY_PAUSE; break;
        case SDLK_SCROLLLOCK:		tk=T_KEY_SCROLL; break;
        case SDLK_PRINTSCREEN:		tk=T_KEY_PRINT; break;
        case SDLK_ESCAPE:			tk=T_KEY_ESCAPE; break;
        case SDLK_DELETE:			tk=T_KEY_DELETE; break;
        case SDLK_HOME:				tk=T_KEY_HOME; break;
        case SDLK_LEFT:				tk=T_KEY_LEFT; break;
        case SDLK_UP:				tk=T_KEY_UP; break;
        case SDLK_RIGHT:			tk=T_KEY_RIGHT; break;
        case SDLK_DOWN:				tk=T_KEY_DOWN; break;
        case SDLK_PAGEUP:			tk=T_KEY_PRIOR; break;
        case SDLK_PAGEDOWN:			tk=T_KEY_NEXT; break;
        case SDLK_END:				tk=T_KEY_END; break;
        case SDLK_SELECT:           tk=T_KEY_SELECT; break;
        case SDLK_EXECUTE:          tk=T_KEY_EXECUTE; break;
        case SDLK_INSERT:			tk=T_KEY_INSERT; break;
        case SDLK_MENU:				tk=T_KEY_MENU; break;
        case SDLK_HELP:				tk=T_KEY_HELP; break;
        case SDLK_NUMLOCKCLEAR:		tk=T_KEY_NUMLOCK; break;
        case SDLK_KP_MULTIPLY:		tk=T_KEY_MULTIPLY; break;
        case SDLK_KP_PLUS:			tk=T_KEY_ADD; break;
        case SDLK_SEPARATOR:        tk=T_KEY_SEPARATOR; break;
        case SDLK_KP_MINUS:			tk=T_KEY_SUBTRACT; break;
        case SDLK_KP_DECIMAL:       tk=T_KEY_DECIMAL; break;
        case SDLK_KP_DIVIDE:		tk=T_KEY_DIVIDE; break;
        case SDLK_KP_0:				tk=T_KEY_NUMPAD0; break;
        case SDLK_KP_1:				tk=T_KEY_NUMPAD1; break;
        case SDLK_KP_2:				tk=T_KEY_NUMPAD2; break;
        case SDLK_KP_3:				tk=T_KEY_NUMPAD3; break;
        case SDLK_KP_4:				tk=T_KEY_NUMPAD4; break;
        case SDLK_KP_5:				tk=T_KEY_NUMPAD5; break;
        case SDLK_KP_6:				tk=T_KEY_NUMPAD6; break;
        case SDLK_KP_7:				tk=T_KEY_NUMPAD7; break;
        case SDLK_KP_8:				tk=T_KEY_NUMPAD8; break;
        case SDLK_KP_9:				tk=T_KEY_NUMPAD9; break;
        case SDLK_F1:				tk=T_KEY_F1; break;
        case SDLK_F2:				tk=T_KEY_F2; break;
        case SDLK_F3:				tk=T_KEY_F3; break;
        case SDLK_F4:				tk=T_KEY_F4; break;
        case SDLK_F5:				tk=T_KEY_F5; break;
        case SDLK_F6:				tk=T_KEY_F6; break;
        case SDLK_F7:				tk=T_KEY_F7; break;
        case SDLK_F8:				tk=T_KEY_F8; break;
        case SDLK_F9:				tk=T_KEY_F9; break;
        case SDLK_F10:				tk=T_KEY_F10; break;
        case SDLK_F11:				tk=T_KEY_F11; break;
        case SDLK_F12:				tk=T_KEY_F12; break;
        case SDLK_F13:				tk=T_KEY_F13; break;
        case SDLK_F14:				tk=T_KEY_F14; break;
        case SDLK_F15:				tk=T_KEY_F15; break;
        case SDLK_LSHIFT:			tk=T_KEY_SHIFT; break;
        case SDLK_RSHIFT:			tk=T_KEY_SHIFT; break;
        case SDLK_LCTRL:			tk=T_KEY_CONTROL; break;
        case SDLK_RCTRL:			tk=T_KEY_CONTROL; break;
	
        default:					tk=T_KEY_NONE; break; 
    }
    return tk;
}
//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


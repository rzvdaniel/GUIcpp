//-------------------------------------------------------------------
//  winkey.cpp
//
//  (C) 1999 A.Weissflog
//  (C) 2003 R.Predescu
//-------------------------------------------------------------------
#include "guide/nsystem.h"
#include "guide/messages.h"
#include "sdl/SDL.h"
TKey TranslateKey(int sdlkey)
{
    TKey tk;
    switch(sdlkey) {
        case SDLK_BACKSPACE:		tk=T_KEY_BACK; break;
        case SDLK_TAB:				tk=T_KEY_TAB; break;
        case SDLK_CLEAR:			tk=T_KEY_RETURN; break;
        case SDLK_RETURN:			tk=T_KEY_RETURN; break;
        case SDLK_PAUSE:			tk=T_KEY_PAUSE; break;
        case SDLK_SCROLLOCK:		tk=T_KEY_SCROLL; break;
        case SDLK_PRINT:			tk=T_KEY_PRINT; break;
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
        //case SDLK_Select:         tk=T_KEY_SELECT; break;
        //case SDLK_Execute:        tk=T_KEY_EXECUTE; break;
        case SDLK_INSERT:			tk=T_KEY_INSERT; break;
        case SDLK_MENU:				tk=T_KEY_MENU; break;
        case SDLK_HELP:				tk=T_KEY_HELP; break;
        case SDLK_NUMLOCK:			tk=T_KEY_NUMLOCK; break;
        case SDLK_KP_MULTIPLY:		tk=T_KEY_MULTIPLY; break;
        case SDLK_KP_PLUS:			tk=T_KEY_ADD; break;
        //case SDLK_KP_Separator:   tk=T_KEY_SEPARATOR; break;
        case SDLK_KP_MINUS:			tk=T_KEY_SUBTRACT; break;
        //case SDLK_KP_Decimal:     tk=T_KEY_DECIMAL; break;
        case SDLK_KP_DIVIDE:		tk=T_KEY_DIVIDE; break;
        case SDLK_KP0:				tk=T_KEY_NUMPAD0; break;
        case SDLK_KP1:				tk=T_KEY_NUMPAD1; break;
        case SDLK_KP2:				tk=T_KEY_NUMPAD2; break;
        case SDLK_KP3:				tk=T_KEY_NUMPAD3; break;
        case SDLK_KP4:				tk=T_KEY_NUMPAD4; break;
        case SDLK_KP5:				tk=T_KEY_NUMPAD5; break;
        case SDLK_KP6:				tk=T_KEY_NUMPAD6; break;
        case SDLK_KP7:				tk=T_KEY_NUMPAD7; break;
        case SDLK_KP8:				tk=T_KEY_NUMPAD8; break;
        case SDLK_KP9:				tk=T_KEY_NUMPAD9; break;

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
        case SDLK_SPACE:			tk=T_KEY_SPACE; break;
        case SDLK_0:				tk=T_KEY_0; break;
        case SDLK_1:				tk=T_KEY_1; break;
        case SDLK_2:				tk=T_KEY_2; break;
        case SDLK_3:				tk=T_KEY_3; break;
        case SDLK_4:				tk=T_KEY_4; break;
        case SDLK_5:				tk=T_KEY_5; break;
        case SDLK_6:				tk=T_KEY_6; break;
        case SDLK_7:				tk=T_KEY_7; break;
        case SDLK_8:				tk=T_KEY_8; break;
        case SDLK_9:				tk=T_KEY_9; break;
	    //Skip uppercase letters
        case SDLK_a:				tk=T_KEY_A; break;
        case SDLK_b:				tk=T_KEY_B; break;
        case SDLK_c:				tk=T_KEY_C; break;
        case SDLK_d:				tk=T_KEY_D; break;
        case SDLK_e:				tk=T_KEY_E; break;
        case SDLK_f:				tk=T_KEY_F; break;
        case SDLK_g:				tk=T_KEY_G; break;
        case SDLK_h:				tk=T_KEY_H; break;
        case SDLK_i:				tk=T_KEY_I; break;
        case SDLK_j:				tk=T_KEY_J; break;
        case SDLK_k:				tk=T_KEY_K; break;
        case SDLK_l:				tk=T_KEY_L; break;
        case SDLK_m:				tk=T_KEY_M; break;
        case SDLK_n:				tk=T_KEY_N; break;
        case SDLK_o:				tk=T_KEY_O; break;
        case SDLK_p:				tk=T_KEY_P; break;
        case SDLK_q:				tk=T_KEY_Q; break;
        case SDLK_r:				tk=T_KEY_R; break;
        case SDLK_s:				tk=T_KEY_S; break;
        case SDLK_t:				tk=T_KEY_T; break;
        case SDLK_u:				tk=T_KEY_U; break;
        case SDLK_v:				tk=T_KEY_V; break;
        case SDLK_w:				tk=T_KEY_W; break;
        case SDLK_x:				tk=T_KEY_X; break;
        case SDLK_y:				tk=T_KEY_Y; break;
        case SDLK_z:				tk=T_KEY_Z; break;
        default:					tk=T_KEY_NONE; break; 
    }
    return tk;
}
//-------------------------------------------------------------------
//  EOF
//-------------------------------------------------------------------


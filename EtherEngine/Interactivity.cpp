#include "Interactivity.h"

ETHER_API getCursorPosition(lua_State * L)
{
	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, event.motion.x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, event.motion.y);
	lua_settable(L, -3);
	return 1;
}


ETHER_API getScrollValue(lua_State * L)
{
	lua_pushnumber(L, event.wheel.x);
	lua_pushnumber(L, event.wheel.y);
	return 2;
}


ETHER_API updateEvent(lua_State * L)
{
	if (SDL_PollEvent(&event))
	{
		lua_pushboolean(L, true);
	}
	else
	{
		lua_pushboolean(L, false);
	}
	return 1;
}


ETHER_API getEventType(lua_State * L)
{
	switch (event.type)
	{
	case SDL_QUIT:
		lua_pushnumber(L, EVENT_QUIT);
		break;
	case SDL_MOUSEMOTION:
		lua_pushnumber(L, EVENT_MOUSEMOTION);
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			lua_pushnumber(L, EVENT_MOUSEBTNDOWN_LEFT);
			break;
		case SDL_BUTTON_RIGHT:
			lua_pushnumber(L, EVENT_MOUSEBTNDOWN_RIGHT);
			break;
		case SDL_BUTTON_MIDDLE:
			lua_pushnumber(L, EVENT_MOUSEBTNDOWN_MIDDLE);
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			lua_pushnumber(L, EVENT_MOUSEBTNUP_LEFT);
			break;
		case SDL_BUTTON_RIGHT:
			lua_pushnumber(L, EVENT_MOUSEBTNUP_RIGHT);
			break;
		case SDL_BUTTON_MIDDLE:
			lua_pushnumber(L, EVENT_MOUSEBTNUP_MIDDLE);
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEWHEEL:
		lua_pushnumber(L, EVENT_MOUSESCROLL);
		break;
	case SDL_WINDOWEVENT:
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			lua_pushnumber(L, EVENT_WINDOW_SHOW);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			lua_pushnumber(L, EVENT_WINDOW_HIDE);
			break;
		case SDL_WINDOWEVENT_MOVED:
			lua_pushnumber(L, EVENT_WINDOW_MOVE);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			lua_pushnumber(L, EVENT_WINDOW_RESIZE);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			lua_pushnumber(L, EVENT_WINDOW_MINSIZE);
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			lua_pushnumber(L, EVENT_WINDOW_MAXSIZE);
			break;
		case SDL_WINDOWEVENT_ENTER:
			lua_pushnumber(L, EVENT_WINDOW_ENTER);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			lua_pushnumber(L, EVENT_WINDOW_LEAVE);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			lua_pushnumber(L, EVENT_WINDOW_FOCUS);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			lua_pushnumber(L, EVENT_WINDOW_LOST);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			lua_pushnumber(L, EVENT_WINDOW_CLOSE);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			lua_pushnumber(L, EVENT_WINDOW_EXPOSED);
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_0:
		case SDLK_KP_0:
			lua_pushnumber(L, EVENT_KEYDOWN_0);
			break;
		case SDLK_KP_00:
			lua_pushnumber(L, EVENT_KEYDOWN_00);
			break;
		case SDLK_KP_000:
			lua_pushnumber(L, EVENT_KEYDOWN_000);
			break;
		case SDLK_1:
		case SDLK_KP_1:
			lua_pushnumber(L, EVENT_KEYDOWN_1);
			break;
		case SDLK_2:
		case SDLK_KP_2:
			lua_pushnumber(L, EVENT_KEYDOWN_2);
			break;
		case SDLK_3:
		case SDLK_KP_3:
			lua_pushnumber(L, EVENT_KEYDOWN_3);
			break;
		case SDLK_4:
		case SDLK_KP_4:
			lua_pushnumber(L, EVENT_KEYDOWN_4);
			break;
		case SDLK_5:
		case SDLK_KP_5:
			lua_pushnumber(L, EVENT_KEYDOWN_5);
			break;
		case SDLK_6:
		case SDLK_KP_6:
			lua_pushnumber(L, EVENT_KEYDOWN_6);
			break;
		case SDLK_7:
		case SDLK_KP_7:
			lua_pushnumber(L, EVENT_KEYDOWN_7);
			break;
		case SDLK_8:
		case SDLK_KP_8:
			lua_pushnumber(L, EVENT_KEYDOWN_8);
			break;
		case SDLK_9:
		case SDLK_KP_9:
			lua_pushnumber(L, EVENT_KEYDOWN_9);
			break;
		case SDLK_F1:
			lua_pushnumber(L, EVENT_KEYDOWN_F1);
			break;
		case SDLK_F2:
			lua_pushnumber(L, EVENT_KEYDOWN_F2);
			break;
		case SDLK_F3:
			lua_pushnumber(L, EVENT_KEYDOWN_F3);
			break;
		case SDLK_F4:
			lua_pushnumber(L, EVENT_KEYDOWN_F4);
			break;
		case SDLK_F5:
			lua_pushnumber(L, EVENT_KEYDOWN_F5);
			break;
		case SDLK_F6:
			lua_pushnumber(L, EVENT_KEYDOWN_F6);
			break;
		case SDLK_F7:
			lua_pushnumber(L, EVENT_KEYDOWN_F7);
			break;
		case SDLK_F8:
			lua_pushnumber(L, EVENT_KEYDOWN_F8);
			break;
		case SDLK_F9:
			lua_pushnumber(L, EVENT_KEYDOWN_F9);
			break;
		case SDLK_F10:
			lua_pushnumber(L, EVENT_KEYDOWN_F10);
			break;
		case SDLK_F11:
			lua_pushnumber(L, EVENT_KEYDOWN_F11);
			break;
		case SDLK_F12:
			lua_pushnumber(L, EVENT_KEYDOWN_F12);
			break;
		case SDLK_F13:
			lua_pushnumber(L, EVENT_KEYDOWN_F13);
			break;
		case SDLK_F14:
			lua_pushnumber(L, EVENT_KEYDOWN_F14);
			break;
		case SDLK_F15:
			lua_pushnumber(L, EVENT_KEYDOWN_F15);
			break;
		case SDLK_F16:
			lua_pushnumber(L, EVENT_KEYDOWN_F16);
			break;
		case SDLK_F17:
			lua_pushnumber(L, EVENT_KEYDOWN_F17);
			break;
		case SDLK_F18:
			lua_pushnumber(L, EVENT_KEYDOWN_F18);
			break;
		case SDLK_F19:
			lua_pushnumber(L, EVENT_KEYDOWN_F19);
			break;
		case SDLK_F20:
			lua_pushnumber(L, EVENT_KEYDOWN_F20);
			break;
		case SDLK_F21:
			lua_pushnumber(L, EVENT_KEYDOWN_F21);
			break;
		case SDLK_F22:
			lua_pushnumber(L, EVENT_KEYDOWN_F22);
			break;
		case SDLK_F23:
			lua_pushnumber(L, EVENT_KEYDOWN_F23);
			break;
		case SDLK_F24:
			lua_pushnumber(L, EVENT_KEYDOWN_F24);
			break;
		case SDLK_a:
		case SDLK_KP_A:
			lua_pushnumber(L, EVENT_KEYDOWN_A);
			break;
		case SDLK_b:
		case SDLK_KP_B:
			lua_pushnumber(L, EVENT_KEYDOWN_B);
			break;
		case SDLK_c:
		case SDLK_KP_C:
			lua_pushnumber(L, EVENT_KEYDOWN_C);
			break;
		case SDLK_d:
		case SDLK_KP_D:
			lua_pushnumber(L, EVENT_KEYDOWN_D);
			break;
		case SDLK_e:
		case SDLK_KP_E:
			lua_pushnumber(L, EVENT_KEYDOWN_E);
			break;
		case SDLK_f:
		case SDLK_KP_F:
			lua_pushnumber(L, EVENT_KEYDOWN_F);
			break;
		case SDLK_g:
			lua_pushnumber(L, EVENT_KEYDOWN_G);
			break;
		case SDLK_h:
			lua_pushnumber(L, EVENT_KEYDOWN_H);
			break;
		case SDLK_i:
			lua_pushnumber(L, EVENT_KEYDOWN_I);
			break;
		case SDLK_j:
			lua_pushnumber(L, EVENT_KEYDOWN_J);
			break;
		case SDLK_k:
			lua_pushnumber(L, EVENT_KEYDOWN_K);
			break;
		case SDLK_l:
			lua_pushnumber(L, EVENT_KEYDOWN_L);
			break;
		case SDLK_m:
			lua_pushnumber(L, EVENT_KEYDOWN_M);
			break;
		case SDLK_n:
			lua_pushnumber(L, EVENT_KEYDOWN_N);
			break;
		case SDLK_o:
			lua_pushnumber(L, EVENT_KEYDOWN_O);
			break;
		case SDLK_p:
			lua_pushnumber(L, EVENT_KEYDOWN_P);
			break;
		case SDLK_q:
			lua_pushnumber(L, EVENT_KEYDOWN_Q);
			break;
		case SDLK_r:
			lua_pushnumber(L, EVENT_KEYDOWN_R);
			break;
		case SDLK_s:
			lua_pushnumber(L, EVENT_KEYDOWN_S);
			break;
		case SDLK_t:
			lua_pushnumber(L, EVENT_KEYDOWN_T);
			break;
		case SDLK_u:
			lua_pushnumber(L, EVENT_KEYDOWN_U);
			break;
		case SDLK_v:
			lua_pushnumber(L, EVENT_KEYDOWN_V);
			break;
		case SDLK_w:
			lua_pushnumber(L, EVENT_KEYDOWN_W);
			break;
		case SDLK_x:
			lua_pushnumber(L, EVENT_KEYDOWN_X);
			break;
		case SDLK_y:
			lua_pushnumber(L, EVENT_KEYDOWN_Y);
			break;
		case SDLK_z:
			lua_pushnumber(L, EVENT_KEYDOWN_Z);
			break;
		case SDLK_ESCAPE:
			lua_pushnumber(L, EVENT_KEYDOWN_ESC);
			break;
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			lua_pushnumber(L, EVENT_KEYDOWN_ENTER);
			break;
		case SDLK_BACKSPACE:
		case SDLK_KP_BACKSPACE:
			lua_pushnumber(L, EVENT_KEYDOWN_BACKSPACE);
			break;
		case SDLK_UP:
			lua_pushnumber(L, EVENT_KEYDOWN_UP);
			break;
		case SDLK_DOWN:
			lua_pushnumber(L, EVENT_KEYDOWN_DOWN);
			break;
		case SDLK_LEFT:
			lua_pushnumber(L, EVENT_KEYDOWN_LEFT);
			break;
		case SDLK_RIGHT:
			lua_pushnumber(L, EVENT_KEYDOWN_RIGHT);
			break;
		case SDLK_INSERT:
			lua_pushnumber(L, EVENT_KEYDOWN_INSERT);
			break;
		case SDLK_DELETE:
			lua_pushnumber(L, EVENT_KEYDOWN_DELETE);
			break;
		case SDLK_HOME:
			lua_pushnumber(L, EVENT_KEYDOWN_HOME);
			break;
		case SDLK_END:
			lua_pushnumber(L, EVENT_KEYDOWN_END);
			break;
		case SDLK_PAGEUP:
			lua_pushnumber(L, EVENT_KEYDOWN_PAGEUP);
			break;
		case SDLK_PAGEDOWN:
			lua_pushnumber(L, EVENT_KEYDOWN_PAGEDOWN);
			break;
		case SDLK_LCTRL:
			lua_pushnumber(L, EVENT_KEYDOWN_LEFTCTRL);
			break;
		case SDLK_LGUI:
			lua_pushnumber(L, EVENT_KEYDOWN_LEFTGUI);
			break;
		case SDLK_LALT:
			lua_pushnumber(L, EVENT_KEYDOWN_LEFTALT);
			break;
		case SDLK_LSHIFT:
			lua_pushnumber(L, EVENT_KEYDOWN_LEFTSHIFT);
			break;
		case SDLK_RCTRL:
			lua_pushnumber(L, EVENT_KEYDOWN_RIGHTCTRL);
			break;
		case SDLK_RGUI:
			lua_pushnumber(L, EVENT_KEYDOWN_RIGHTGUI);
			break;
		case SDLK_RALT:
			lua_pushnumber(L, EVENT_KEYDOWN_RIGHTALT);
			break;
		case SDLK_RSHIFT:
			lua_pushnumber(L, EVENT_KEYDOWN_RIGHTSHIFT);
			break;
		case SDLK_SPACE:
			lua_pushnumber(L, EVENT_KEYDOWN_SPACE);
			break;
		case SDLK_TAB:
		case SDLK_KP_TAB:
			lua_pushnumber(L, EVENT_KEYDOWN_TAB);
			break;
		case SDLK_CAPSLOCK:
			lua_pushnumber(L, EVENT_KEYDOWN_CAPSLOCK);
			break;
		case SDLK_NUMLOCKCLEAR:
			lua_pushnumber(L, EVENT_KEYDOWN_NUMLOCK);
			break;
		case SDLK_PRINTSCREEN:
			lua_pushnumber(L, EVENT_KEYDOWN_PRINTSCREEN);
			break;
		case SDLK_SCROLLLOCK:
			lua_pushnumber(L, EVENT_KEYDOWN_SCROLLLOCK);
			break;
		case SDLK_PAUSE:
			lua_pushnumber(L, EVENT_KEYDOWN_PAUSE);
			break;
		case SDLK_AUDIOMUTE:
			lua_pushnumber(L, EVENT_KEYDOWN_AUDIOMUTE);
			break;
		case SDLK_AUDIOPREV:
			lua_pushnumber(L, EVENT_KEYDOWN_AUDIOPREV);
			break;
		case SDLK_AUDIONEXT:
			lua_pushnumber(L, EVENT_KEYDOWN_AUDIONEXT);
			break;
		case SDLK_AUDIOPLAY:
			lua_pushnumber(L, EVENT_KEYDOWN_AUDIOPLAY);
			break;
		case SDLK_AUDIOSTOP:
			lua_pushnumber(L, EVENT_KEYDOWN_AUDIOSTOP);
			break;
		case SDLK_VOLUMEUP:
			lua_pushnumber(L, EVENT_KEYDOWN_VOLUMEUP);
			break;
		case SDLK_VOLUMEDOWN:
			lua_pushnumber(L, EVENT_KEYDOWN_VOLUMEDOWN);
			break;
		case SDLK_BRIGHTNESSUP:
			lua_pushnumber(L, EVENT_KEYDOWN_BRIGHTNESSUP);
			break;
		case SDLK_BRIGHTNESSDOWN:
			lua_pushnumber(L, EVENT_KEYDOWN_BRIGHTNESSDOWN);
			break;
		case SDLK_BACKQUOTE:
			lua_pushnumber(L, EVENT_KEYDOWN_BACKQUOTE);
			break;
		case SDLK_EXCLAIM:
		case SDLK_KP_EXCLAM:
			lua_pushnumber(L, EVENT_KEYDOWN_EXCLAM);
			break;
		case SDLK_AT:
		case SDLK_KP_AT:
			lua_pushnumber(L, EVENT_KEYDOWN_AT);
			break;
		case SDLK_HASH:
		case SDLK_KP_HASH:
			lua_pushnumber(L, EVENT_KEYDOWN_HASH);
			break;
		case SDLK_DOLLAR:
			lua_pushnumber(L, EVENT_KEYDOWN_DOOLAR);
			break;
		case SDLK_CARET:
		case SDLK_KP_POWER:
			lua_pushnumber(L, EVENT_KEYDOWN_CARET);
			break;
		case SDLK_AMPERSAND:
		case SDLK_KP_AMPERSAND:
			lua_pushnumber(L, EVENT_KEYDOWN_AMPERSAND);
			break;
		case SDLK_KP_DBLAMPERSAND:
			lua_pushnumber(L, EVENT_KEYDOWN_DBLAMPERSAND);
			break;
		case SDLK_ASTERISK:
		case SDLK_KP_MULTIPLY:
			lua_pushnumber(L, EVENT_KEYDOWN_ASTERISK);
			break;
		case SDLK_LEFTPAREN:
		case SDLK_KP_LEFTPAREN:
			lua_pushnumber(L, EVENT_KEYDOWN_LEFTPAREN);
			break;
		case SDLK_RIGHTPAREN:
		case SDLK_KP_RIGHTPAREN:
			lua_pushnumber(L, EVENT_KEYDOWN_RIGHTPAREN);
			break;
		case SDLK_MINUS:
		case SDLK_KP_MINUS:
			lua_pushnumber(L, EVENT_KEYDOWN_MINUS);
			break;
		case SDLK_UNDERSCORE:
			lua_pushnumber(L, EVENT_KEYDOWN_UNDERSCORE);
			break;
		case SDLK_PLUS:
		case SDLK_KP_PLUS:
			lua_pushnumber(L, EVENT_KEYDOWN_PLUS);
			break;
		case SDLK_EQUALS:
		case SDLK_KP_EQUALS:
			lua_pushnumber(L, EVENT_KEYDOWN_EQUALS);
			break;
		case SDLK_LEFTBRACKET:
			lua_pushnumber(L, EVENT_KEYDOWN_LEFTBRACKET);
			break;
		case SDLK_RIGHTBRACKET:
			lua_pushnumber(L, EVENT_KEYDOWN_RIGHTBRACKET);
			break;
		case SDLK_KP_LEFTBRACE:
			lua_pushnumber(L, EVENT_KEYDOWN_LEFTBRACE);
			break;
		case SDLK_KP_RIGHTBRACE:
			lua_pushnumber(L, EVENT_KEYDOWN_RIGHTBRACE);
			break;
		case SDLK_COLON:
			lua_pushnumber(L, EVENT_KEYDOWN_COLON);
			break;
		case SDLK_SEMICOLON:
			lua_pushnumber(L, EVENT_KEYDOWN_SEMICOLON);
			break;
		case SDLK_BACKSLASH:
			lua_pushnumber(L, EVENT_KEYDOWN_BACKSLASH);
			break;
		case SDLK_QUOTE:
			lua_pushnumber(L, EVENT_KEYDOWN_QUOTE);
			break;
		case SDLK_QUOTEDBL:
			lua_pushnumber(L, EVENT_KEYDOWN_QUOTEDBL);
			break;
		case SDLK_LESS:
			lua_pushnumber(L, EVENT_KEYDOWN_LESS);
			break;
		case SDLK_GREATER:
			lua_pushnumber(L, EVENT_KEYDOWN_GREATER);
			break;
		case SDLK_COMMA:
			lua_pushnumber(L, EVENT_KEYDOWN_COMMA);
			break;
		case SDLK_PERIOD:
			lua_pushnumber(L, EVENT_KEYDOWN_PERIOD);
			break;
		case SDLK_QUESTION:
			lua_pushnumber(L, EVENT_KEYDOWN_QUESTION);
			break;
		case SDLK_SLASH:
			lua_pushnumber(L, EVENT_KEYDOWN_SLASH);
			break;
		case SDLK_KP_VERTICALBAR:
			lua_pushnumber(L, EVENT_KEYDOWN_VERTICALBAR);
			break;
		case SDLK_KP_DBLVERTICALBAR:
			lua_pushnumber(L, EVENT_KEYDOWN_DBLVERTICALBAR);
			break;
		case SDLK_WWW:
			lua_pushnumber(L, EVENT_KEYDOWN_WWW);
			break;
		case SDLK_MAIL:
			lua_pushnumber(L, EVENT_KEYDOWN_EMAIL);
			break;
		default:
			lua_pushnil(L);
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_0:
		case SDLK_KP_0:
			lua_pushnumber(L, EVENT_KEYUP_0);
			break;
		case SDLK_KP_00:
			lua_pushnumber(L, EVENT_KEYUP_00);
			break;
		case SDLK_KP_000:
			lua_pushnumber(L, EVENT_KEYUP_000);
			break;
		case SDLK_1:
		case SDLK_KP_1:
			lua_pushnumber(L, EVENT_KEYUP_1);
			break;
		case SDLK_2:
		case SDLK_KP_2:
			lua_pushnumber(L, EVENT_KEYUP_2);
			break;
		case SDLK_3:
		case SDLK_KP_3:
			lua_pushnumber(L, EVENT_KEYUP_3);
			break;
		case SDLK_4:
		case SDLK_KP_4:
			lua_pushnumber(L, EVENT_KEYUP_4);
			break;
		case SDLK_5:
		case SDLK_KP_5:
			lua_pushnumber(L, EVENT_KEYUP_5);
			break;
		case SDLK_6:
		case SDLK_KP_6:
			lua_pushnumber(L, EVENT_KEYUP_6);
			break;
		case SDLK_7:
		case SDLK_KP_7:
			lua_pushnumber(L, EVENT_KEYUP_7);
			break;
		case SDLK_8:
		case SDLK_KP_8:
			lua_pushnumber(L, EVENT_KEYUP_8);
			break;
		case SDLK_9:
		case SDLK_KP_9:
			lua_pushnumber(L, EVENT_KEYUP_9);
			break;
		case SDLK_F1:
			lua_pushnumber(L, EVENT_KEYUP_F1);
			break;
		case SDLK_F2:
			lua_pushnumber(L, EVENT_KEYUP_F2);
			break;
		case SDLK_F3:
			lua_pushnumber(L, EVENT_KEYUP_F3);
			break;
		case SDLK_F4:
			lua_pushnumber(L, EVENT_KEYUP_F4);
			break;
		case SDLK_F5:
			lua_pushnumber(L, EVENT_KEYUP_F5);
			break;
		case SDLK_F6:
			lua_pushnumber(L, EVENT_KEYUP_F6);
			break;
		case SDLK_F7:
			lua_pushnumber(L, EVENT_KEYUP_F7);
			break;
		case SDLK_F8:
			lua_pushnumber(L, EVENT_KEYUP_F8);
			break;
		case SDLK_F9:
			lua_pushnumber(L, EVENT_KEYUP_F9);
			break;
		case SDLK_F10:
			lua_pushnumber(L, EVENT_KEYUP_F10);
			break;
		case SDLK_F11:
			lua_pushnumber(L, EVENT_KEYUP_F11);
			break;
		case SDLK_F12:
			lua_pushnumber(L, EVENT_KEYUP_F12);
			break;
		case SDLK_F13:
			lua_pushnumber(L, EVENT_KEYUP_F13);
			break;
		case SDLK_F14:
			lua_pushnumber(L, EVENT_KEYUP_F14);
			break;
		case SDLK_F15:
			lua_pushnumber(L, EVENT_KEYUP_F15);
			break;
		case SDLK_F16:
			lua_pushnumber(L, EVENT_KEYUP_F16);
			break;
		case SDLK_F17:
			lua_pushnumber(L, EVENT_KEYUP_F17);
			break;
		case SDLK_F18:
			lua_pushnumber(L, EVENT_KEYUP_F18);
			break;
		case SDLK_F19:
			lua_pushnumber(L, EVENT_KEYUP_F19);
			break;
		case SDLK_F20:
			lua_pushnumber(L, EVENT_KEYUP_F20);
			break;
		case SDLK_F21:
			lua_pushnumber(L, EVENT_KEYUP_F21);
			break;
		case SDLK_F22:
			lua_pushnumber(L, EVENT_KEYUP_F22);
			break;
		case SDLK_F23:
			lua_pushnumber(L, EVENT_KEYUP_F23);
			break;
		case SDLK_F24:
			lua_pushnumber(L, EVENT_KEYUP_F24);
			break;
		case SDLK_a:
		case SDLK_KP_A:
			lua_pushnumber(L, EVENT_KEYUP_A);
			break;
		case SDLK_b:
		case SDLK_KP_B:
			lua_pushnumber(L, EVENT_KEYUP_B);
			break;
		case SDLK_c:
		case SDLK_KP_C:
			lua_pushnumber(L, EVENT_KEYUP_C);
			break;
		case SDLK_d:
		case SDLK_KP_D:
			lua_pushnumber(L, EVENT_KEYUP_D);
			break;
		case SDLK_e:
		case SDLK_KP_E:
			lua_pushnumber(L, EVENT_KEYUP_E);
			break;
		case SDLK_f:
		case SDLK_KP_F:
			lua_pushnumber(L, EVENT_KEYUP_F);
			break;
		case SDLK_g:
			lua_pushnumber(L, EVENT_KEYUP_G);
			break;
		case SDLK_h:
			lua_pushnumber(L, EVENT_KEYUP_H);
			break;
		case SDLK_i:
			lua_pushnumber(L, EVENT_KEYUP_I);
			break;
		case SDLK_j:
			lua_pushnumber(L, EVENT_KEYUP_J);
			break;
		case SDLK_k:
			lua_pushnumber(L, EVENT_KEYUP_K);
			break;
		case SDLK_l:
			lua_pushnumber(L, EVENT_KEYUP_L);
			break;
		case SDLK_m:
			lua_pushnumber(L, EVENT_KEYUP_M);
			break;
		case SDLK_n:
			lua_pushnumber(L, EVENT_KEYUP_N);
			break;
		case SDLK_o:
			lua_pushnumber(L, EVENT_KEYUP_O);
			break;
		case SDLK_p:
			lua_pushnumber(L, EVENT_KEYUP_P);
			break;
		case SDLK_q:
			lua_pushnumber(L, EVENT_KEYUP_Q);
			break;
		case SDLK_r:
			lua_pushnumber(L, EVENT_KEYUP_R);
			break;
		case SDLK_s:
			lua_pushnumber(L, EVENT_KEYUP_S);
			break;
		case SDLK_t:
			lua_pushnumber(L, EVENT_KEYUP_T);
			break;
		case SDLK_u:
			lua_pushnumber(L, EVENT_KEYUP_U);
			break;
		case SDLK_v:
			lua_pushnumber(L, EVENT_KEYUP_V);
			break;
		case SDLK_w:
			lua_pushnumber(L, EVENT_KEYUP_W);
			break;
		case SDLK_x:
			lua_pushnumber(L, EVENT_KEYUP_X);
			break;
		case SDLK_y:
			lua_pushnumber(L, EVENT_KEYUP_Y);
			break;
		case SDLK_z:
			lua_pushnumber(L, EVENT_KEYUP_Z);
			break;
		case SDLK_ESCAPE:
			lua_pushnumber(L, EVENT_KEYUP_ESC);
			break;
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			lua_pushnumber(L, EVENT_KEYUP_ENTER);
			break;
		case SDLK_BACKSPACE:
		case SDLK_KP_BACKSPACE:
			lua_pushnumber(L, EVENT_KEYUP_BACKSPACE);
			break;
		case SDLK_UP:
			lua_pushnumber(L, EVENT_KEYUP_UP);
			break;
		case SDLK_DOWN:
			lua_pushnumber(L, EVENT_KEYUP_DOWN);
			break;
		case SDLK_LEFT:
			lua_pushnumber(L, EVENT_KEYUP_LEFT);
			break;
		case SDLK_RIGHT:
			lua_pushnumber(L, EVENT_KEYUP_RIGHT);
			break;
		case SDLK_INSERT:
			lua_pushnumber(L, EVENT_KEYUP_INSERT);
			break;
		case SDLK_DELETE:
			lua_pushnumber(L, EVENT_KEYUP_DELETE);
			break;
		case SDLK_HOME:
			lua_pushnumber(L, EVENT_KEYUP_HOME);
			break;
		case SDLK_END:
			lua_pushnumber(L, EVENT_KEYUP_END);
			break;
		case SDLK_PAGEUP:
			lua_pushnumber(L, EVENT_KEYUP_PAGEUP);
			break;
		case SDLK_PAGEDOWN:
			lua_pushnumber(L, EVENT_KEYUP_PAGEDOWN);
			break;
		case SDLK_LCTRL:
			lua_pushnumber(L, EVENT_KEYUP_LEFTCTRL);
			break;
		case SDLK_LGUI:
			lua_pushnumber(L, EVENT_KEYUP_LEFTGUI);
			break;
		case SDLK_LALT:
			lua_pushnumber(L, EVENT_KEYUP_LEFTALT);
			break;
		case SDLK_LSHIFT:
			lua_pushnumber(L, EVENT_KEYUP_LEFTSHIFT);
			break;
		case SDLK_RCTRL:
			lua_pushnumber(L, EVENT_KEYUP_RIGHTCTRL);
			break;
		case SDLK_RGUI:
			lua_pushnumber(L, EVENT_KEYUP_RIGHTGUI);
			break;
		case SDLK_RALT:
			lua_pushnumber(L, EVENT_KEYUP_RIGHTALT);
			break;
		case SDLK_RSHIFT:
			lua_pushnumber(L, EVENT_KEYUP_RIGHTSHIFT);
			break;
		case SDLK_SPACE:
			lua_pushnumber(L, EVENT_KEYUP_SPACE);
			break;
		case SDLK_TAB:
		case SDLK_KP_TAB:
			lua_pushnumber(L, EVENT_KEYUP_TAB);
			break;
		case SDLK_CAPSLOCK:
			lua_pushnumber(L, EVENT_KEYUP_CAPSLOCK);
			break;
		case SDLK_NUMLOCKCLEAR:
			lua_pushnumber(L, EVENT_KEYUP_NUMLOCK);
			break;
		case SDLK_PRINTSCREEN:
			lua_pushnumber(L, EVENT_KEYUP_PRINTSCREEN);
			break;
		case SDLK_SCROLLLOCK:
			lua_pushnumber(L, EVENT_KEYUP_SCROLLLOCK);
			break;
		case SDLK_PAUSE:
			lua_pushnumber(L, EVENT_KEYUP_PAUSE);
			break;
		case SDLK_AUDIOMUTE:
			lua_pushnumber(L, EVENT_KEYUP_AUDIOMUTE);
			break;
		case SDLK_AUDIOPREV:
			lua_pushnumber(L, EVENT_KEYUP_AUDIOPREV);
			break;
		case SDLK_AUDIONEXT:
			lua_pushnumber(L, EVENT_KEYUP_AUDIONEXT);
			break;
		case SDLK_AUDIOPLAY:
			lua_pushnumber(L, EVENT_KEYUP_AUDIOPLAY);
			break;
		case SDLK_AUDIOSTOP:
			lua_pushnumber(L, EVENT_KEYUP_AUDIOSTOP);
			break;
		case SDLK_VOLUMEUP:
			lua_pushnumber(L, EVENT_KEYUP_VOLUMEUP);
			break;
		case SDLK_VOLUMEDOWN:
			lua_pushnumber(L, EVENT_KEYUP_VOLUMEDOWN);
			break;
		case SDLK_BRIGHTNESSUP:
			lua_pushnumber(L, EVENT_KEYUP_BRIGHTNESSUP);
			break;
		case SDLK_BRIGHTNESSDOWN:
			lua_pushnumber(L, EVENT_KEYUP_BRIGHTNESSDOWN);
			break;
		case SDLK_BACKQUOTE:
			lua_pushnumber(L, EVENT_KEYUP_BACKQUOTE);
			break;
		case SDLK_EXCLAIM:
		case SDLK_KP_EXCLAM:
			lua_pushnumber(L, EVENT_KEYUP_EXCLAM);
			break;
		case SDLK_AT:
		case SDLK_KP_AT:
			lua_pushnumber(L, EVENT_KEYUP_AT);
			break;
		case SDLK_HASH:
		case SDLK_KP_HASH:
			lua_pushnumber(L, EVENT_KEYUP_HASH);
			break;
		case SDLK_DOLLAR:
			lua_pushnumber(L, EVENT_KEYUP_DOOLAR);
			break;
		case SDLK_CARET:
		case SDLK_KP_POWER:
			lua_pushnumber(L, EVENT_KEYUP_CARET);
			break;
		case SDLK_AMPERSAND:
		case SDLK_KP_AMPERSAND:
			lua_pushnumber(L, EVENT_KEYUP_AMPERSAND);
			break;
		case SDLK_KP_DBLAMPERSAND:
			lua_pushnumber(L, EVENT_KEYUP_DBLAMPERSAND);
			break;
		case SDLK_ASTERISK:
		case SDLK_KP_MULTIPLY:
			lua_pushnumber(L, EVENT_KEYUP_ASTERISK);
			break;
		case SDLK_LEFTPAREN:
		case SDLK_KP_LEFTPAREN:
			lua_pushnumber(L, EVENT_KEYUP_LEFTPAREN);
			break;
		case SDLK_RIGHTPAREN:
		case SDLK_KP_RIGHTPAREN:
			lua_pushnumber(L, EVENT_KEYUP_RIGHTPAREN);
			break;
		case SDLK_MINUS:
		case SDLK_KP_MINUS:
			lua_pushnumber(L, EVENT_KEYUP_MINUS);
			break;
		case SDLK_UNDERSCORE:
			lua_pushnumber(L, EVENT_KEYUP_UNDERSCORE);
			break;
		case SDLK_PLUS:
		case SDLK_KP_PLUS:
			lua_pushnumber(L, EVENT_KEYUP_PLUS);
			break;
		case SDLK_EQUALS:
		case SDLK_KP_EQUALS:
			lua_pushnumber(L, EVENT_KEYUP_EQUALS);
			break;
		case SDLK_LEFTBRACKET:
			lua_pushnumber(L, EVENT_KEYUP_LEFTBRACKET);
			break;
		case SDLK_RIGHTBRACKET:
			lua_pushnumber(L, EVENT_KEYUP_RIGHTBRACKET);
			break;
		case SDLK_KP_LEFTBRACE:
			lua_pushnumber(L, EVENT_KEYUP_LEFTBRACE);
			break;
		case SDLK_KP_RIGHTBRACE:
			lua_pushnumber(L, EVENT_KEYUP_RIGHTBRACE);
			break;
		case SDLK_COLON:
			lua_pushnumber(L, EVENT_KEYUP_COLON);
			break;
		case SDLK_SEMICOLON:
			lua_pushnumber(L, EVENT_KEYUP_SEMICOLON);
			break;
		case SDLK_BACKSLASH:
			lua_pushnumber(L, EVENT_KEYUP_BACKSLASH);
			break;
		case SDLK_QUOTE:
			lua_pushnumber(L, EVENT_KEYUP_QUOTE);
			break;
		case SDLK_QUOTEDBL:
			lua_pushnumber(L, EVENT_KEYUP_QUOTEDBL);
			break;
		case SDLK_LESS:
			lua_pushnumber(L, EVENT_KEYUP_LESS);
			break;
		case SDLK_GREATER:
			lua_pushnumber(L, EVENT_KEYUP_GREATER);
			break;
		case SDLK_COMMA:
			lua_pushnumber(L, EVENT_KEYUP_COMMA);
			break;
		case SDLK_PERIOD:
			lua_pushnumber(L, EVENT_KEYUP_PERIOD);
			break;
		case SDLK_QUESTION:
			lua_pushnumber(L, EVENT_KEYUP_QUESTION);
			break;
		case SDLK_SLASH:
			lua_pushnumber(L, EVENT_KEYUP_SLASH);
			break;
		case SDLK_KP_VERTICALBAR:
			lua_pushnumber(L, EVENT_KEYUP_VERTICALBAR);
			break;
		case SDLK_KP_DBLVERTICALBAR:
			lua_pushnumber(L, EVENT_KEYUP_DBLVERTICALBAR);
			break;
		case SDLK_WWW:
			lua_pushnumber(L, EVENT_KEYUP_WWW);
			break;
		case SDLK_MAIL:
			lua_pushnumber(L, EVENT_KEYUP_EMAIL);
			break;
		default:
			lua_pushnil(L);
			break;
		}
		break;
	default:
		break;
	}

	return 1;
}
#ifndef _UTIL_H_
#define _UTIL_H_

#include <lua.hpp>
#include <SDL.h>

SDL_Point GetPointParam(lua_State* L, int index, const char* funName);

SDL_Rect GetRectParam(lua_State* L, int index, const char* funName);

SDL_Color GetColorParam(lua_State* L, int index, const char* funName);

#endif // !_UTIL_H_


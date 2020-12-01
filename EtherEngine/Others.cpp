#include "Others.h"


extern "C" int getBasePath(lua_State * L)
{
	lua_pushstring(L, SDL_GetBasePath());

	return 1;
}


extern "C" int setClipboardText(lua_State * L)
{
	const char* text = luaL_checkstring(L, 1);
	SDL_SetClipboardText(text);

	return 0;
}


extern "C" int getClipboardText(lua_State * L)
{
	lua_pushstring(L, SDL_GetClipboardText());

	return 1;
}


extern "C" int getPlatform(lua_State * L)
{
	lua_pushstring(L, SDL_GetPlatform());

	return 1;
}


extern "C" int getSystemRAM(lua_State * L)
{
	lua_pushnumber(L, SDL_GetSystemRAM());

	return 1;
}

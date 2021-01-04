#include "OS.h"


ETHER_API getBasePath(lua_State * L)
{
	lua_pushstring(L, SDL_GetBasePath());

	return 1;
}


ETHER_API setClipboardText(lua_State * L)
{
	const char* text = luaL_checkstring(L, 1);
	SDL_SetClipboardText(text);

	return 0;
}


ETHER_API getClipboardText(lua_State * L)
{
	lua_pushstring(L, SDL_GetClipboardText());

	return 1;
}


ETHER_API getPlatform(lua_State * L)
{
	lua_pushstring(L, SDL_GetPlatform());

	return 1;
}


ETHER_API getSystemRAM(lua_State * L)
{
	lua_pushnumber(L, SDL_GetSystemRAM());

	return 1;
}

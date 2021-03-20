#include "Utils.h"

int GetPointParam(lua_State* L, int index, SDL_Point& point)
{

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index)) return -1;
	else
	{
		lua_getfield(L, index, "x");
		if (!lua_isnumber(L, -1)) return -1;
		point.x = lua_tonumber(L, -1);
		lua_getfield(L, index, "y");
		if (!lua_isnumber(L, -1)) return -1;
		point.y = lua_tonumber(L, -1);
	}

#else

	lua_getfield(L, index, "x");
	point.x = lua_tonumber(L, -1);
	lua_getfield(L, index, "y");
	point.y = lua_tonumber(L, -1);

#endif

	return 0;
}


int GetRectParam(lua_State* L, int index, SDL_Rect& rect)
{

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index)) return -1;
	else
	{
		lua_getfield(L, index, "x");
		if (!lua_isnumber(L, -1)) return -1;
		rect.x = lua_tonumber(L, -1);
		lua_getfield(L, index, "y");
		if (!lua_isnumber(L, -1)) return -1;
		rect.y = lua_tonumber(L, -1);
		lua_getfield(L, index, "w");
		if (!lua_isnumber(L, -1)) return -1;
		rect.w = lua_tonumber(L, -1);
		lua_getfield(L, index, "h");
		if (!lua_isnumber(L, -1)) return -1;
		rect.h = lua_tonumber(L, -1);
	}

#else

	lua_getfield(L, index, "x");
	rect.x = lua_tonumber(L, -1);
	lua_getfield(L, index, "y");
	rect.y = lua_tonumber(L, -1);
	lua_getfield(L, index, "w");
	rect.w = lua_tonumber(L, -1);
	lua_getfield(L, index, "h");
	rect.h = lua_tonumber(L, -1);

#endif

	return 0;
}


int GetColorParam(lua_State* L, int index, SDL_Color& color)
{

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index)) return -1;
	else
	{
		lua_getfield(L, index, "r");
		if (!lua_isnumber(L, -1)) return -1;
		color.r = lua_tonumber(L, -1);
		lua_getfield(L, index, "g");
		if (!lua_isnumber(L, -1)) return -1;
		color.g = lua_tonumber(L, -1);
		lua_getfield(L, index, "b");
		if (!lua_isnumber(L, -1)) return -1;
		color.b = lua_tonumber(L, -1);
		lua_getfield(L, index, "a");
		if (!lua_isnumber(L, -1)) return -1;
		color.a = lua_tonumber(L, -1);
	}

#else

	lua_getfield(L, index, "r");
	color.r = lua_tonumber(L, -1);
	lua_getfield(L, index, "g");
	color.g = lua_tonumber(L, -1);
	lua_getfield(L, index, "b");
	color.b = lua_tonumber(L, -1);
	lua_getfield(L, index, "a");
	color.a = lua_tonumber(L, -1);

#endif 

	return 0;
}
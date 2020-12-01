#include "Time.h"


extern "C" int pause(lua_State * L)
{
	system("pause");

	return 0;
}


extern "C" int sleep(lua_State * L)
{
	int delay = luaL_checknumber(L, 1);
	SDL_Delay(delay);

	return 0;
}


extern "C" int getInitTime(lua_State * L)
{
	lua_pushnumber(L, SDL_GetTicks());

	return 1;
}


extern "C" int getAccurateCount(lua_State * L)
{
	lua_pushnumber(L, SDL_GetPerformanceCounter());

	return 1;
}


extern "C" int getCounterFrequency(lua_State * L)
{
	lua_pushnumber(L, SDL_GetPerformanceFrequency());

	return 1;
}
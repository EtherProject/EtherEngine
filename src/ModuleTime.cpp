#include "ModuleTime.h"


ETHER_API pause(lua_State * L)
{
	system("pause");

	return 0;
}


ETHER_API sleep(lua_State * L)
{
	SDL_Delay(luaL_checknumber(L, 1));

	return 0;
}


ETHER_API dynamicSleep(lua_State* L)
{
	int expected_delay = luaL_checknumber(L, 1);
	int duration = luaL_checknumber(L, 2);
	if (duration < expected_delay)
	{
		SDL_Delay(expected_delay - duration);
	}

	return 0;
}


ETHER_API getInitTime(lua_State * L)
{
	lua_pushnumber(L, SDL_GetTicks());

	return 1;
}


ETHER_API getAccurateCount(lua_State * L)
{
	lua_pushnumber(L, SDL_GetPerformanceCounter());

	return 1;
}


ETHER_API getCounterFrequency(lua_State * L)
{
	lua_pushnumber(L, SDL_GetPerformanceFrequency());

	return 1;
}


ModuleTime::ModuleTime(lua_State* L, string name) : Module(L, name)
{
	_vCMethods = {
		{ "Pause", pause },
		{ "Sleep", sleep },
		{ "DynamicSleep", dynamicSleep },
		{ "GetInitTime", getInitTime },
		{ "GetAccurateCount", getAccurateCount },
		{ "GetCounterFrequency", getCounterFrequency },
	};
}
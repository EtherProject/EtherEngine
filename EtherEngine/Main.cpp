#include "Main.h"

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	luaL_openlibs(pL);

	_PushArgs(pL, argc, argv);

	lua_pushcfunction(pL, usingMoudle);
	lua_setglobal(pL, "UsingMoudle");
	lua_pushcfunction(pL, getVersion);
	lua_setglobal(pL, "GetVersion");

	if (luaL_dofile(pL, (string(SDL_GetBasePath()) + "Main.lua").c_str()))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Scripts Run Failed", lua_tostring(pL, -1), NULL);
	}

	_HandleQuit();

	return 0;
}


void _PushArgs(lua_State* l, int argc, char** argv)
{
	lua_pushnumber(l, argc);
	lua_setglobal(l, "_argc");

	lua_newtable(l);
	for (int i = 1; i < argc + 1; i++)
	{
		lua_pushnumber(l, i);
		lua_pushstring(l, argv[i - 1]);
		lua_settable(l, -3);
	}
	lua_setglobal(l, "_argv");
}


void _HandleQuit()
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	if (window)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}
}
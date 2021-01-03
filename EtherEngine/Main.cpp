#include "Main.h"

int main(int argc, char** argv)
{
	_HandleInit();

	lua_State* l = luaL_newstate();
	luaL_openlibs(l);

	_PushArgs(l, argc, argv);

	_RegisteEtherLib(l);

	if (luaL_dofile(l, "Main.lua"))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Scripts Run Failed", lua_tostring(l, -1), NULL);
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


void _HandleInit()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
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


void _RegisteEtherLib(lua_State* l)
{
	for (luaL_Reg method : cMethods)
	{
		lua_pushcfunction(l, method.func);
		lua_setglobal(l, method.name);
	}

	for (Macro macro : macros)
	{
		lua_pushnumber(l, macro.value);
		lua_setglobal(l, macro.name);
	}
}
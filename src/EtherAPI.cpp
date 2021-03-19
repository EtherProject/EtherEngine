#include "EtherAPI.h"

SDL_Event event;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
lua_State* pL = luaL_newstate();

MoudleWindow* moudleWindow;
MoudleGraphic* moudleGraphic;
MoudleAlgorithm* moudleAlgorithm;
MoudleInteractivity* moudleInteractivity;
MoudleMedia* moudleMedia;
MoudleNetwork* moudleNetwork;
MoudleOS* moudleOS;
MoudleTime* moudleTime;
MoudleString* moudleString;
MoudleJSON* moudleJSON;

ETHER_API usingMoudle(lua_State* L)
{
	string moudleName = luaL_checkstring(L, 1);
	if (moudleName == MOUDLENAME_ALL)
	{
		if (!moudleWindow)
		{
			moudleWindow = new MoudleWindow(L, MOUDLENAME_WINDOW);
			moudleWindow->OpenMoudle();
		}
		if (!moudleGraphic)
		{
			moudleGraphic = new MoudleGraphic(L, MOUDLENAME_GRAPHIC);
			moudleGraphic->OpenMoudle();
		}
		if (!moudleAlgorithm)
		{
			moudleAlgorithm = new MoudleAlgorithm(L, MOUDLENAME_ALGORITHM);
			moudleAlgorithm->OpenMoudle();
		}
		if (!moudleInteractivity)
		{
			moudleInteractivity = new MoudleInteractivity(L, MOUDLENAME_INTERACTIVITY);
			moudleInteractivity->OpenMoudle();
		}
		if (!moudleMedia)
		{
			moudleMedia = new MoudleMedia(L, MOUDLENAME_MEDIA);
			moudleMedia->OpenMoudle();
		}
		if (!moudleNetwork)
		{
			moudleNetwork = new MoudleNetwork(L, MOUDLENAME_NETWORK);
			moudleNetwork->OpenMoudle();
		}
		if (!moudleOS)
		{
			moudleOS = new MoudleOS(L, MOUDLENAME_OS);
			moudleOS->OpenMoudle();
		}
		if (!moudleTime)
		{
			moudleTime = new MoudleTime(L, MOUDLENAME_TIME);
			moudleTime->OpenMoudle();
		}
		if (!moudleString)
		{
			moudleString = new MoudleString(L, MOUDLENAME_STRING);
			moudleString->OpenMoudle();
		}
		if (!moudleJSON)
		{
			moudleJSON = new MoudleJSON(L, MOUDLENAME_JSON);
			moudleJSON->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_WINDOW)
	{
		if (!moudleWindow)
		{
			moudleWindow = new MoudleWindow(L, moudleName);
			moudleWindow->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_GRAPHIC)
	{
		if (!moudleGraphic)
		{
			moudleGraphic = new MoudleGraphic(L, moudleName);
			moudleGraphic->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_ALGORITHM)
	{
		if (!moudleAlgorithm)
		{
			moudleAlgorithm = new MoudleAlgorithm(L, moudleName);
			moudleAlgorithm->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_INTERACTIVITY)
	{
		if (!moudleInteractivity)
		{
			moudleInteractivity = new MoudleInteractivity(L, moudleName);
			moudleInteractivity->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_MEDIA)
	{
		if (!moudleMedia)
		{
			moudleMedia = new MoudleMedia(L, moudleName);
			moudleMedia->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_NETWORK)
	{
		if (!moudleNetwork)
		{
			moudleNetwork = new MoudleNetwork(L, moudleName);
			moudleNetwork->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_OS)
	{
		if (!moudleOS)
		{
			moudleOS = new MoudleOS(L, moudleName);
			moudleOS->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_TIME)
	{
		if (!moudleTime)
		{
			moudleTime = new MoudleTime(L, moudleName);
			moudleTime->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_STRING)
	{
		if (!moudleString)
		{
			moudleString = new MoudleString(L, moudleName);
			moudleString->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_JSON)
	{
		if (!moudleJSON)
		{
			moudleJSON = new MoudleJSON(L, MOUDLENAME_JSON);
			moudleJSON->OpenMoudle();
		}
	}
	else
		luaL_error(L, "moudle '%s' not found", moudleName);

	return 0;
}


ETHER_API getVersion(lua_State* L)
{
	lua_pushstring(L, _VERSION_);

	return 1;
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	luaL_openlibs(pL);

	_PushArgs(pL, argc, argv);

	lua_pushcfunction(pL, usingMoudle);
	lua_setglobal(pL, "UsingMoudle");
	lua_pushcfunction(pL, getVersion);
	lua_setglobal(pL, "GetVersion");

	if (luaL_dofile(pL, "Main.lua"))
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
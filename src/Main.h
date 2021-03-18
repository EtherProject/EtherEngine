#ifndef _MAIN_H_
#define _MAIN_H_

#include "Macros.h"
#include "Window.h"
#include "Graphic.h"
#include "Media.h"
#include "Interactivity.h"
#include "Time.h"
#include "OS.h"
#include "Algorithm.h"
#include "Network.h"
#include "String.h"

#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#ifndef _ETHER_DEBUG_
#ifdef __WINDOWS__
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
#else

#endif
#endif

#ifdef _WINDOWS_

#pragma comment(lib, "Setupapi.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")

#endif


#define MOUDLENAME_ALL "All"
#define MOUDLENAME_ALGORITHM "Algorithm"
#define MOUDLENAME_GRAPHIC "Graphic"
#define MOUDLENAME_INTERACTIVITY "Interactivity"
#define MOUDLENAME_MEDIA "Media"
#define MOUDLENAME_NETWORK "Network"
#define MOUDLENAME_OS "OS"
#define MOUDLENAME_TIME "Time"
#define MOUDLENAME_WINDOW "Window"
#define MOUDLENAME_STRING "String"

SDL_Event event;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void _PushArgs(lua_State* l, int argc, char** argv);
void _HandleQuit();

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

ETHER_API usingMoudle(lua_State* L)
{
	string moudleName = luaL_checkstring(L, 1);
	if (moudleName == MOUDLENAME_ALL)
	{
		if (!moudleWindow)
		{
			moudleWindow = new MoudleWindow(L);
			moudleWindow->OpenMoudle();
		}
		if (!moudleGraphic)
		{
			moudleGraphic = new MoudleGraphic(L);
			moudleGraphic->OpenMoudle();
		}
		if (!moudleAlgorithm)
		{
			moudleAlgorithm = new MoudleAlgorithm(L);
			moudleAlgorithm->OpenMoudle();
		}
		if (!moudleInteractivity)
		{
			moudleInteractivity = new MoudleInteractivity(L);
			moudleInteractivity->OpenMoudle();
		}
		if (!moudleMedia)
		{
			moudleMedia = new MoudleMedia(L);
			moudleMedia->OpenMoudle();
		}
		if (!moudleNetwork)
		{
			moudleNetwork = new MoudleNetwork(L);
			moudleNetwork->OpenMoudle();
		}
		if (!moudleOS)
		{
			moudleOS = new MoudleOS(L);
			moudleOS->OpenMoudle();
		}
		if (!moudleTime)
		{
			moudleTime = new MoudleTime(L);
			moudleTime->OpenMoudle();
		}
		if (!moudleString)
		{
			moudleString = new MoudleString(L);
			moudleString->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_WINDOW)
	{
		if (!moudleWindow)
		{
			moudleWindow = new MoudleWindow(L);
			moudleWindow->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_GRAPHIC)
	{
		if (!moudleGraphic)
		{
			moudleGraphic = new MoudleGraphic(L);
			moudleGraphic->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_ALGORITHM)
	{
		if (!moudleAlgorithm)
		{
			moudleAlgorithm = new MoudleAlgorithm(L);
			moudleAlgorithm->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_INTERACTIVITY)
	{
		if (!moudleInteractivity)
		{
			moudleInteractivity = new MoudleInteractivity(L);
			moudleInteractivity->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_MEDIA)
	{
		if (!moudleMedia)
		{
			moudleMedia = new MoudleMedia(L);
			moudleMedia->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_NETWORK)
	{
		if (!moudleNetwork)
		{
			moudleNetwork = new MoudleNetwork(L);
			moudleNetwork->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_OS)
	{
		if (!moudleOS)
		{
			moudleOS = new MoudleOS(L);
			moudleOS->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_TIME)
	{
		if (!moudleTime)
		{
			moudleTime = new MoudleTime(L);
			moudleTime->OpenMoudle();
		}
	}
	else if (moudleName == MOUDLENAME_STRING)
	{
		if (!moudleString)
		{
			moudleString = new MoudleString(L);
			moudleString->OpenMoudle();
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

#endif // !_MAIN_H_
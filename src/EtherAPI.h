#ifndef _MAIN_H_
#define _MAIN_H_

#include "Macros.h"
#include "MoudleWindow.h"
#include "MoudleGraphic.h"
#include "MoudleMedia.h"
#include "MoudleInteractivity.h"
#include "MoudleTime.h"
#include "MoudleOS.h"
#include "MoudleAlgorithm.h"
#include "MoudleNetwork.h"
#include "MoudleString.h"
#include "MoudleJSON.h"

#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#ifndef _ETHER_DEBUG_
#ifdef __WINDOWS__
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
#else
/* 以图形应用程序模式编译 */
#endif
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
#define MOUDLENAME_JSON "JSON"

void _PushArgs(lua_State* l, int argc, char** argv);

void _HandleQuit();

ETHER_API usingMoudle(lua_State* L);

ETHER_API getVersion(lua_State* L);

#endif // !_MAIN_H_
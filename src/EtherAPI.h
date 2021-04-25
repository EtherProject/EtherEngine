#ifndef _MAIN_H_
#define _MAIN_H_

#include "Macros.h"
#include "ModuleWindow.h"
#include "ModuleGraphic.h"
#include "ModuleMedia.h"
#include "ModuleInteractivity.h"
#include "ModuleTime.h"
#include "ModuleOS.h"
#include "ModuleAlgorithm.h"
#include "ModuleNetwork.h"
#include "ModuleString.h"
#include "ModuleJSON.h"

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

#define MODULENAME_ALL "All"
#define MODULENAME_ALGORITHM "Algorithm"
#define MODULENAME_GRAPHIC "Graphic"
#define MODULENAME_INTERACTIVITY "Interactivity"
#define MODULENAME_MEDIA "Media"
#define MODULENAME_NETWORK "Network"
#define MODULENAME_OS "OS"
#define MODULENAME_TIME "Time"
#define MODULENAME_WINDOW "Window"
#define MODULENAME_STRING "String"
#define MODULENAME_JSON "JSON"

#ifndef __WINDOWS__
extern char** environ;
#endif

void _PushArgs(lua_State* l, int argc, char** argv, char** envp);

void _HandleQuit();

ETHER_API usingModule(lua_State* L);

ETHER_API getVersion(lua_State* L);

#endif // !_MAIN_H_
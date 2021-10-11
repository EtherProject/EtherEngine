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
#include "ModuleCompress.h"
#include "ModuleXML.h"

#include "lua.hpp"
#include <cjson/cJSON.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <unordered_map>

#ifndef _ETHER_DEBUG_
#ifdef __WINDOWS__
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
#else
/* ��ͼ��Ӧ�ó���ģʽ���� */
#endif
#endif

#define MODULENAME_ALGORITHM		"Algorithm"
#define MODULENAME_GRAPHIC			"Graphic"
#define MODULENAME_INTERACTIVITY	"Interactivity"
#define MODULENAME_MEDIA			"Media"
#define MODULENAME_NETWORK			"Network"
#define MODULENAME_OS				"OS"
#define MODULENAME_TIME				"Time"
#define MODULENAME_WINDOW			"Window"
#define MODULENAME_STRING			"String"
#define MODULENAME_JSON				"JSON"
#define MODULENAME_COMPRESS			"Compress"
#define MODULENAME_XML				"XML"

#define DEFAULTNAME_ENTRY			"Main.lua"

#define CONFIGSUCCESS				0
#define CONFIGERROR_LOADING			-1
#define CONFIGERROR_PARSING			-2

#ifndef __WINDOWS__
extern char** environ;
#endif

int _LoadConfig();

void _PushArgs(lua_State* L, int argc, char** argv, char** envp);

void _HandleQuit();

ETHER_API usingModule(lua_State* L);

ETHER_API getVersion(lua_State* L);

#endif // !_MAIN_H_
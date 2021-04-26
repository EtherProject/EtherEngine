#include "EtherAPI.h"

string strNameEntry = DEFAULTNAME_ENTRY;
vector<string> vStrPathList, vStrCPathList, vStrCmdList;

SDL_Event event;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

lua_State* pL = luaL_newstate();

ModuleWindow* moduleWindow;
ModuleGraphic* moduleGraphic;
ModuleAlgorithm* moduleAlgorithm;
ModuleInteractivity* moduleInteractivity;
ModuleMedia* moduleMedia;
ModuleNetwork* moduleNetwork;
ModuleOS* moduleOS;
ModuleTime* moduleTime;
ModuleString* moduleString;
ModuleJSON* moduleJSON;

ETHER_API usingModule(lua_State* L)
{
	string moduleName = luaL_checkstring(L, 1);
	if (moduleName == MODULENAME_ALL)
	{
		if (!moduleWindow)
		{
			moduleWindow = new ModuleWindow(L, MODULENAME_WINDOW);
			moduleWindow->OpenModule();
		}
		if (!moduleGraphic)
		{
			moduleGraphic = new ModuleGraphic(L, MODULENAME_GRAPHIC);
			moduleGraphic->OpenModule();
		}
		if (!moduleAlgorithm)
		{
			moduleAlgorithm = new ModuleAlgorithm(L, MODULENAME_ALGORITHM);
			moduleAlgorithm->OpenModule();
		}
		if (!moduleInteractivity)
		{
			moduleInteractivity = new ModuleInteractivity(L, MODULENAME_INTERACTIVITY);
			moduleInteractivity->OpenModule();
		}
		if (!moduleMedia)
		{
			moduleMedia = new ModuleMedia(L, MODULENAME_MEDIA);
			moduleMedia->OpenModule();
		}
		if (!moduleNetwork)
		{
			moduleNetwork = new ModuleNetwork(L, MODULENAME_NETWORK);
			moduleNetwork->OpenModule();
		}
		if (!moduleOS)
		{
			moduleOS = new ModuleOS(L, MODULENAME_OS);
			moduleOS->OpenModule();
		}
		if (!moduleTime)
		{
			moduleTime = new ModuleTime(L, MODULENAME_TIME);
			moduleTime->OpenModule();
		}
		if (!moduleString)
		{
			moduleString = new ModuleString(L, MODULENAME_STRING);
			moduleString->OpenModule();
		}
		if (!moduleJSON)
		{
			moduleJSON = new ModuleJSON(L, MODULENAME_JSON);
			moduleJSON->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_WINDOW)
	{
		if (!moduleWindow)
		{
			moduleWindow = new ModuleWindow(L, moduleName);
			moduleWindow->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_GRAPHIC)
	{
		if (!moduleGraphic)
		{
			moduleGraphic = new ModuleGraphic(L, moduleName);
			moduleGraphic->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_ALGORITHM)
	{
		if (!moduleAlgorithm)
		{
			moduleAlgorithm = new ModuleAlgorithm(L, moduleName);
			moduleAlgorithm->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_INTERACTIVITY)
	{
		if (!moduleInteractivity)
		{
			moduleInteractivity = new ModuleInteractivity(L, moduleName);
			moduleInteractivity->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_MEDIA)
	{
		if (!moduleMedia)
		{
			moduleMedia = new ModuleMedia(L, moduleName);
			moduleMedia->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_NETWORK)
	{
		if (!moduleNetwork)
		{
			moduleNetwork = new ModuleNetwork(L, moduleName);
			moduleNetwork->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_OS)
	{
		if (!moduleOS)
		{
			moduleOS = new ModuleOS(L, moduleName);
			moduleOS->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_TIME)
	{
		if (!moduleTime)
		{
			moduleTime = new ModuleTime(L, moduleName);
			moduleTime->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_STRING)
	{
		if (!moduleString)
		{
			moduleString = new ModuleString(L, moduleName);
			moduleString->OpenModule();
		}
	}
	else if (moduleName == MODULENAME_JSON)
	{
		if (!moduleJSON)
		{
			moduleJSON = new ModuleJSON(L, MODULENAME_JSON);
			moduleJSON->OpenModule();
		}
	}
	else
		luaL_error(L, "module '%s' not found", moduleName);

	return 0;
}

ETHER_API getVersion(lua_State* L)
{
	lua_pushstring(L, _VERSION_);

	return 1;
}

int main(int argc, char** argv)
{
	luaL_openlibs(pL);

#ifdef _ETHER_DEBUG_
	switch (_LoadConfig())
	{
	case CONFIGERROR_LOADING:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Load Configuration Failed", "Failed to load configuration file.\nProgram will run with the default configuration.\nDisable _ETHER_DEBUG_ to hide this warning.", nullptr);
		break;
	case CONFIGERROR_PARSING:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Parse Configuration Failed", "Failed to parse configuration file.\nProgram will run with the default configuration.\nDisable _ETHER_DEBUG_ to hide this warning.", nullptr);
		break;
	default:
		break;
	}
#else
	_LoadConfig();
#endif	

	SDL_Init(SDL_INIT_EVERYTHING);

	_PushArgs(pL, argc, argv, environ);

	lua_pushcfunction(pL, usingModule);
	lua_setglobal(pL, "UsingModule");
	lua_pushcfunction(pL, getVersion);
	lua_setglobal(pL, "GetVersion");

	if (luaL_dofile(pL, strNameEntry.c_str()))
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Scripts Run Failed", lua_tostring(pL, -1), nullptr);

	_HandleQuit();

	return 0;
}


int _LoadConfig()
{
	ifstream fin("config.json");
	if (!fin.good()) 
		return CONFIGERROR_LOADING;

	stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();

	cJSON* pJSONRoot = cJSON_Parse(ssContent.str().c_str());
	ssContent.clear();
	if (!(pJSONRoot && pJSONRoot->type == cJSON_Object))
	{
		cJSON_Delete(pJSONRoot);
		return CONFIGERROR_PARSING;
	}

	cJSON* pJSONEntry, * pJSONPackage, * pJSONPath, * pJSONCPath, * pJSONCommand;
	if ((pJSONEntry = cJSON_GetObjectItem(pJSONRoot, "entry")) && pJSONEntry->type == cJSON_String)
		strNameEntry = pJSONEntry->valuestring;
	else
	{
		cJSON_Delete(pJSONRoot);
		return CONFIGERROR_PARSING;
	}

	if ((pJSONPackage = cJSON_GetObjectItem(pJSONRoot, "package")) && pJSONPackage->type == cJSON_Object)
	{
		if ((pJSONPath = cJSON_GetObjectItem(pJSONPackage, "path")) && pJSONPath->type == cJSON_Array)
			for (int i = 0; i < cJSON_GetArraySize(pJSONPath); i++)
			{
				cJSON* item = cJSON_GetArrayItem(pJSONPath, i);
				if (item && item->type == cJSON_String)
					vStrPathList.push_back(item->valuestring);
				else
				{
					cJSON_Delete(pJSONRoot);
					return CONFIGERROR_PARSING;
				}
			}
		if ((pJSONCPath = cJSON_GetObjectItem(pJSONPackage, "cpath")) && pJSONCPath->type == cJSON_Array)
			for (int i = 0; i < cJSON_GetArraySize(pJSONCPath); i++)
			{
				cJSON* item = cJSON_GetArrayItem(pJSONCPath, i);
				if (item && item->type == cJSON_String)
					vStrCPathList.push_back(item->valuestring);
				else
				{
					cJSON_Delete(pJSONRoot);
					return CONFIGERROR_PARSING;
				}
			}
	}
	else
	{
		cJSON_Delete(pJSONRoot);
		return CONFIGERROR_PARSING;
	}

	if ((pJSONCommand = cJSON_GetObjectItem(pJSONRoot, "command")) && pJSONCommand->type == cJSON_Array)
		for (int i = 0; i < cJSON_GetArraySize(pJSONCommand); i++)
		{
			cJSON* item = cJSON_GetArrayItem(pJSONCommand, i);
			if (item && item->type == cJSON_String)
				vStrCmdList.push_back(item->valuestring);
			else
			{
				cJSON_Delete(pJSONRoot);
				return CONFIGERROR_PARSING;
			}
		}
	else
	{
		cJSON_Delete(pJSONRoot);
		return CONFIGERROR_PARSING;
	}

	lua_getglobal(pL, "package");

	lua_getfield(pL, -1, "path");
	string strPath = lua_tostring(pL, -1);
	for (string path : vStrPathList)
		strPath.append(";" + path);
	vector<string>().swap(vStrPathList);
	lua_pushstring(pL, strPath.c_str());
	lua_setfield(pL, -3, "path");
	lua_pop(pL, 1);

	lua_getfield(pL, -1, "cpath");
	string strCPath = lua_tostring(pL, -1);
	for (string cpath : vStrCPathList)
		strCPath.append(";" + cpath);
	lua_pushstring(pL, strCPath.c_str());
	lua_setfield(pL, -3, "cpath");
	lua_pop(pL, 2);

	return CONFIGSUCCESS;
}


void _PushArgs(lua_State* l, int argc, char** argv, char** envp)
{
	lua_pushnumber(l, vStrCmdList.size() + argc);
	lua_setglobal(l, "_argc");

	lua_newtable(l);
	for (int i = 1; i < vStrCmdList.size() + 1; i++)
	{
		lua_pushnumber(l, i);
		lua_pushstring(l, vStrCmdList[i - 1].c_str());
		lua_settable(l, -3);
	}
	for (int i = vStrCmdList.size() + 1; i < vStrCmdList.size() + argc + 1; i++)
	{
		lua_pushnumber(l, i);
		lua_pushstring(l, argv[i - vStrCmdList.size() - 1]);
		lua_settable(l, -3);
	}
	lua_setglobal(l, "_argv");

	lua_newtable(l);
	for (int i = 1; envp[i - 1]; i++)
	{
		string strEnvp = envp[i - 1];
		size_t stIndexEq = strEnvp.find_first_of('=');
		lua_pushstring(l, strEnvp.substr(0, stIndexEq).c_str());
		lua_pushstring(l, strEnvp.substr(stIndexEq + 1).c_str());
		lua_settable(l, -3);
	}
	lua_setglobal(l, "_envp");
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